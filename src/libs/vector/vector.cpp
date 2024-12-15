#include "vector.hpp"

/*!
    \addtogroup Vector_module
    @{
*/

#include <algorithm>

#include "./iterator/iterator.cpp"

/*!
    \brief Стандартный конструктор
    \details Создаёт объект класса Vector с пустым массивом.
*/
template <typename T> Vector<T>::Vector()
{
    data = new T[1];
    capacity = 1;
}

/*!
    \brief Конструктор с размером массива
    \details Создаёт объект класса Vector с массивом из size элементов.
*/
template <typename T> Vector<T>::Vector(const size_t capacity) : capacity(capacity), size(capacity)
{
    data = new T[capacity];
}

/*!
    \brief Конструктор с размером массива и стандартным значением
    \details Создаёт объект класса Vector с массивом из size default_value элементов.
*/
template <typename T> Vector<T>::Vector(const size_t size, T default_value) : size(size)
{
    data = new T[size * 2];
    if (data == nullptr)
        throw std::bad_alloc();
    capacity = size * 2;
    std::fill(data, data + size, default_value);
}

/*!
    \brief Конструктор со списком инициализации
    \details Создаёт объект класса Vector на основе вектора инициализации.
*/
template <typename T> Vector<T>::Vector(const std::initializer_list<T> list)
{
    size = list.size();
    data = new T[size];
    capacity = size;
    std::copy(list.begin(), list.end(), data);
}

/*!
    \brief Конструктор копирования
    \details Создаёт объект класса Vector с копией массива объекта input_vector.
*/
template <typename T> Vector<T>::Vector(const Vector<T> &input_vector)
{
    *this = input_vector;
}

/*!
    \brief Конструктор перемещение
    \details Создаёт объект класса Vector и перемещает в него массив объекта other.
*/
template <typename T> Vector<T>::Vector(Vector<T> &&input_vector)
{
    *this = std::move(input_vector);
}

/*!
    \brief Деструктор
    \details Уничтожает объект Vector и освобождает память.
*/
template <typename T> Vector<T>::~Vector() noexcept
{
    delete[] data;
}

/*!
    \brief Добавить элемент в конец
    \details При необходимости расширяет вектор и добавляет в его конец значение value.
*/
template <typename T> void Vector<T>::push_back(const T &value)
{
    if (size == capacity)
        resize(capacity * 2);
    data[size++] = value;
}

/*!
    \brief Добавить элемент в начало
    \details При необходимости расширяет вектор и добавляет в его начало значение value.
*/
template <typename T> void Vector<T>::push_front(const T &value)
{
    if (size == capacity)
        resize(capacity * 2);
    std::copy_backward(data, data + size, data + size + 1);
    data[0] = value;
}

/*!
    \brief Удалить элемент из конца
    \details Удаляет последний элемент вектора.
*/
template <typename T> void Vector<T>::pop_back()
{
    --size;
}

/*!
    \brief Удалить элемент из начала
    \details Удаляет первый элемент вектора.
*/
template <typename T> void Vector<T>::pop_front()
{
    std::copy(data + 1, data + size, data);
    --size;
}

/*!
    \brief Вставка элемента в позицию
    \details Вставляет значение value в позицию position.

    \param[in] position итератор позиции.
    \param[in] value значение для вставки.

    \return Итератор на вставленный элемент.

    \throw std::invalid_argument если position выходит за границы вектора.
*/
template <typename T> typename Vector<T>::iterator Vector<T>::insert(iterator position, const T &value)
{
    if (position > end() || position < begin())
        throw std::invalid_argument("Invalid position");
    size_t pos_index = position - begin();
    if (size == capacity)
        resize(capacity * 2);
    std::copy_backward(data + pos_index, data + size, data + size + 1);
    Vector<T>::iterator new_pos = iterator(data + pos_index);
    *new_pos = value;
    ++size;
    return new_pos;
}

/*!
    \brief Вставка группы элементов в позицию
    \details Вставляет значение в диапазоне от итератора first до итератора last в позицию на которую указывает итератор
   position.

    \param[in] position итератор позиции вставки.
    \param[in] first итератор начала диапазона для вставки.
    \param[in] last итератор конца диапазона для вставки.

    \return Итератор на начала диапазона вставленных элементов.

    \throw std::invalid_argument если position выходит за границы вектора, или first > last.
*/
template <typename T> typename Vector<T>::iterator Vector<T>::insert(iterator position, iterator first, iterator last)
{
    if (first > last || position > end() || position < begin())
        throw std::invalid_argument("Invalid range");
    size_t dist = last - first;
    size_t pos_index = position - begin();
    while (capacity - size < dist)
        resize(capacity * 2);
    std::copy_backward(data + pos_index, data + size, data + size + dist);
    std::copy(first, last, data + pos_index);
    size += dist;
    return iterator(data + pos_index);
}

/*!
    \brief Вырезать элемент из позиции
    \details Вырезает элемент из позиции position и возвращает итератор на новую позицию.

    \param[in] position итератор позиции.

    \return Итератор на новую позицию.

    \throw std::invalid_argument если position выходит за границы вектора.
*/
template <typename T> typename Vector<T>::iterator Vector<T>::erase(iterator position)
{
    if (position > end() || position < begin())
        throw std::invalid_argument("Invalid position");
    std::copy(position + 1, end(), position);
    --size;
    return iterator(position);
}

/*!
    \brief Вырезать отрезок
    \details Вырезает все элементы из диапазона от итератора first до итератора last и возвращает итератор на новую
   позици.

    \param[in] first итератор начала отрезка.
    \param[in] last итератор конца отрезка.

    \return Итератор на новую позицию.

    \throw std::invalid_argument если first > last, или first < begin() или last > end().
*/
template <typename T> typename Vector<T>::iterator Vector<T>::erase(iterator first, iterator last)
{
    if (first > last || first < begin() || last > end())
        throw std::invalid_argument("Invalid range");
    size_t dist = last - first;
    std::copy(last, end(), first);
    size -= dist;
    return iterator(first);
}

/*!
    \brief Увеличивает размер массива
    \details Увеличивает размер массива до рамера new_size если new_size > size.

    \param[in] new_size новый размер массива.

    \throw std::runtime_error если new_size < size.
*/
template <typename T> void Vector<T>::resize(const size_t new_size)
{
    if (new_size < size)
        throw std::runtime_error("Cannot resize to a smaller size");
    T *new_data = new T[new_size];
    std::copy(data, data + size, new_data);
    capacity = new_size;
    delete[] data;
    data = new_data;
}

/*!
    \brief Проверка на пустоту вектора
    \details Проверяет содержит ли вектор элементы.

    \return True, если вектор пуст, иначе False.
*/
template <typename T> bool Vector<T>::is_empty() const noexcept
{
    return size == 0;
}

/*!
    \brief Геттер размера вектора
    \details Возвращает кол-во заполненых элементов массива.

    \return Кол-во заполненных элементов вектора.
*/
template <typename T> size_t Vector<T>::get_size() const noexcept
{
    return size;
}

/*!
    \brief Оператор []
    \details Перегрузка оператора [] для доступа к элементу вектора по индексу.

    \param[in] index индекс элемента вектора.

    \return Ссылку на элемент вектора.
*/
template <typename T> T &Vector<T>::operator[](const size_t index)
{
    if (index >= size)
        throw std::out_of_range("Index out of range!");
    return data[index];
}

/*!
    \brief Оператор []
    \details Перегрузка оператора [] для доступа к элементу вектора по индексу.

    \param[in] index индекс элемента вектора.

    \return Значение элемента вектора.
*/
template <typename T> T Vector<T>::operator[](const size_t index) const
{
    if (index >= size)
        throw std::out_of_range("Index out of range!");
    return data[index];
}

/*!
    \brief Оператор копирования
    \details Перегрузка оператора = для копирования полей вектора.

    \param[in] other вектор для копирования.

    \return Ссылку на текущий объект.
*/
template <typename T> Vector<T> &Vector<T>::operator=(const Vector<T> &other)
{
    if (this == &other)
        return *this;
    delete[] data;
    size = other.size;
    capacity = other.capacity;
    data = new T[capacity];
    if (data == nullptr)
        throw std::bad_alloc();
    std::copy(other.cbegin(), other.cend(), data);
    return *this;
}

/*!
    \brief Оператор перемещения
    \details Перегрузка оператора = для перемещения полей вектора.

    \param[in] other вектор для перемещения.

    \return Ссылку на текущий объект.
*/
template <typename T> Vector<T> &Vector<T>::operator=(Vector<T> &&other)
{
    if (this == &other)
        return *this;
    delete[] data;
    data = other.data;
    size = other.size;
    capacity = other.capacity;
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
    return *this;
}

/*!
    \brief Геттер итератора на начало вектора
    \details Возвращает итератор на начало вектора.

    \return Итератор на начало вектора.
*/
template <typename T> typename Vector<T>::iterator Vector<T>::begin() noexcept
{
    return iterator(data);
}

/*!
    \brief Геттер итератора на конец вектора
    \details Возвращает итератор на конец вектора.

    \return Итератор на конец вектора.
*/
template <typename T> typename Vector<T>::iterator Vector<T>::end() noexcept
{
    return iterator(data + size);
}

/*!
    \brief Геттер константного итератора на начало вектора
    \details Возвращает константный итератор на начало вектора.

    \return Константный итератор на начало вектора.
*/
template <typename T> typename Vector<T>::iterator Vector<T>::cbegin() const noexcept
{
    return iterator(data);
}

/*!
    \brief Геттер константного итератора на конец вектора
    \details Возвращает константный итератор на конец вектора.

    \return Константный итератор на конец вектора.
*/
template <typename T> typename Vector<T>::iterator Vector<T>::cend() const noexcept
{
    return iterator(data + size);
}

/*! @} */