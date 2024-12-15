#include "iterator.hpp"

/*!
    \addtogroup Vector_iterator_submodule
    @{
*/

#include <iostream>

/*!
    \brief Стандартный конструктор
    \details Создаёт итератор, содержащий указатель на элемент вектора.

    \param[in] p указатель на элемент вектора.
*/
template <typename T> Vector_iterator<T>::Vector_iterator(T *p) : p(p)
{
}

/*!
    \brief Конструктор копирования
    \details Создаёт итератор, содержащий копию указателя из итератора other.

    \param[in] it ссылка на итератор, из которого нужно создать копию.
*/
template <typename T> Vector_iterator<T>::Vector_iterator(const Vector_iterator &it)
{
    p = it.p;
}

/*!
    \brief Оператор +
    \details Перегрузка оператора +. Создаёт итератор по указателю p + num.

    \param[in] num ссылка на шаг.

    \return Итератор, содержащий новый указатель.
*/
template <typename T> Vector_iterator<T> Vector_iterator<T>::operator+(const size_t &num) const noexcept
{
    return Vector_iterator<T>(p + num);
}

/*!
    \brief Оператор -
    \details Перегрузка оператора -. Создаёт итератор по указателю p - num.

    \param[in] num ссылка на шаг.

    \return Итератор, содержащий новый указатель.
*/
template <typename T> Vector_iterator<T> Vector_iterator<T>::operator-(const size_t &num) const noexcept
{
    return Vector_iterator<T>(p - num);
}

/*!
    \brief Оператор -
    \details Перегрузка оператора -. Находит расстояние между двумя итераторами.

    \param[in] other ссылка на другой итератор.

    \return Расстояние между двумя векторами.

    \throw std::invalid_argument - other > текущего итератора.
*/
template <typename T> size_t Vector_iterator<T>::operator-(const Vector_iterator &other) const
{
    if (*this < other)
        throw std::invalid_argument("Cannot subtract iterators from different vectors");
    return p - other.p;
}

/*!
    \brief Оператор !=
    \details Перегрузка оператора !=. Сравнивает уазатели двух итераторов.

    \param[in] other ссылка на другой итератор.

    \return True если итераторы не указывают на один элемент. Иначе False.
*/
template <typename T> bool Vector_iterator<T>::operator!=(const Vector_iterator &other) const noexcept
{
    return p != other.p;
}

/*!
    \brief Оператор ==
    \details Перегрузка оператора ==. Сравнивает уазатели двух итераторов.

    \param[in] other ссылка на другой итератор.

    \return True если итераторы указывают на один элемент. Иначе False.
*/
template <typename T> bool Vector_iterator<T>::operator==(const Vector_iterator &other) const noexcept
{
    return p == other.p;
}

/*!
    \brief Оператор >
    \details Перегрузка оператора >. Сравнивает уазатели двух итераторов.

    \param[in] other ссылка на другой итератор.

    \return True если указатель текущего итератора больше значения указателя итератора other. Иначе False.
*/
template <typename T> bool Vector_iterator<T>::operator>(const Vector_iterator &other) const noexcept
{
    return p > other.p;
}

/*!
    \brief Оператор <
    \details Перегрузка оператора <. Сравнивает уазатели двух итераторов.

    \param[in] other ссылка на другой итератор.

    \return True если указатель текущего итератора меньше значения указателя итератора other. Иначе False.
*/
template <typename T> bool Vector_iterator<T>::operator<(const Vector_iterator &other) const noexcept
{
    return p < other.p;
}

/*!
    \brief Оператор разименования
    \details Перегрузка оператора *. Возвращает ссылку на значение на которое указывает указатель текущего итератора.

    \return Ссылка на элемент на который укащывает текущий объект.
*/
template <typename T> T &Vector_iterator<T>::operator*() const noexcept
{
    return *p;
}

/*!
    \brief Оператор инкриментации
    \details Перегрузка оператора ++. Перемещает указатель текущего итератора на следующий элемент.

    \return Ссылка на текущий объект.
*/
template <typename T> Vector_iterator<T> &Vector_iterator<T>::operator++() noexcept
{
    ++p;
    return *this;
}

/*!
    \brief Оператор дикриментцаии
    \details Перегрузка оператора --. Перемещает указатель текущего итератора на предидущий элемент.

    \return Ссылка на текущий объект.
*/
template <typename T> Vector_iterator<T> &Vector_iterator<T>::operator--() noexcept
{
    --p;
    return *this;
}

/*! @} */