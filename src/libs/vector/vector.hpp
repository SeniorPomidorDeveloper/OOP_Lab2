/*!
    \defgroup Vector_module Вектор
    \brief Вектор
    \details Эта библиотека позволяет работать с динамическим массивом элементов любого типа.
*/
#ifndef VECTOR_HPP
#define VECTOR_HPP

/*!
    \addtogroup Vector_module
    @{
*/

#include "./iterator/iterator.hpp"

/*!
    \brief Шаблон класса вектора
    \details Объект этого класса хранит динамический массив элементов любого типа.
*/
template <typename T> class Vector
{
    protected:
        T *data = nullptr;
        size_t size = 0;
        size_t capacity = 0;

    public:
        typedef Vector_iterator<T> iterator; //< Итератор вектора

        Vector();
        Vector(const size_t capacity);
        Vector(const size_t size, T default_value);
        Vector(const std::initializer_list<T> list);
        Vector(const Vector<T> &input_vector);
        Vector(Vector<T> &&input_vector);

        ~Vector() noexcept;

        void push_back(const T &value);
        void push_front(const T &value);
        void pop_back();
        void pop_front();

        iterator insert(iterator position, const T &value);
        iterator insert(iterator position, iterator first, iterator last);
        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);

        void resize(const size_t new_size);
        bool is_empty() const noexcept;

        size_t get_size() const noexcept;

        T &operator[](const size_t index);
        T operator[](const size_t index) const;
        Vector &operator=(const Vector<T> &other);
        Vector &operator=(Vector<T> &&other);

        iterator begin() noexcept;
        iterator end() noexcept;

        iterator cbegin() const noexcept;
        iterator cend() const noexcept;
};

/*! @} */

#endif // VECTOR_HPP