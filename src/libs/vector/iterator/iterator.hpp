/*!
    \defgroup Vector_iterator_submodule Итераторы вектора
    \ingroup Vector_module
    \brief Итераторы вектора
*/
#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

/*!
    \addtogroup Vector_iterator_submodule
    @{
*/

#include <cstddef>
#include <iterator>

template <typename T> class Vector;

/*!
    \brief Шаблон класса итератора вектора
    \details Объект этого класса хранит указатель на элемент массива вектора. Реализует итеративную работу с вектором.
*/
template <typename T> class Vector_iterator
{
    private:
        T *p;

    public:
        friend class Vector<T>;
        using difference_type = std::ptrdiff_t;
        using value_type = std::remove_cv_t<T>;
        using pointer = T *;
        using const_pointer = const T *;
        using reference = T &;
        using iterator_category = std::random_access_iterator_tag;

        Vector_iterator(T *p);
        Vector_iterator(const Vector_iterator &it);

        Vector_iterator<T> operator+(const size_t &num) const noexcept;
        Vector_iterator<T> operator-(const size_t &num) const noexcept;

        size_t operator-(const Vector_iterator &other) const;
        bool operator!=(const Vector_iterator &other) const noexcept;
        bool operator==(const Vector_iterator &other) const noexcept;
        bool operator>(const Vector_iterator &other) const noexcept;
        bool operator<(const Vector_iterator &other) const noexcept;

        T &operator*() const noexcept;

        Vector_iterator &operator++() noexcept;
        Vector_iterator &operator--() noexcept;
};

/*! @} */

#endif // VECTOR_ITERATOR_HPP