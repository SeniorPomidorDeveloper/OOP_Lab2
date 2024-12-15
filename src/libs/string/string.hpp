/*!
    \defgroup String_module Модуль String
    \brief Строки
    \details Этот модуль реализует работу со строками.
*/
#ifndef STRING_HPP
#define STRING_HPP

/*!
    \addtogroup String_module
    @{
*/

#include "../vector/paths.hpp"
#include <iostream>

/*!
    \brief Класс для работы со строками
    \details Объект хранит динамический массив типа char с длинной size. Массив оканчивается '\0'.
*/
class String : public Vector<char>
{
    public:
        String();
        String(const char *str);
        String(const String &other);
        String(String &&other);
        ~String();

        void resize(size_t new_size);

        size_t get_length() const noexcept;
        const char *get_cstring() const noexcept;

        String operator+(const String &other) const;
        String &operator+=(const String &other);
        friend std::ostream &operator<<(std::ostream &out, const String &str);
        String &operator=(const String &other) noexcept;
        String &operator=(const char *str);
};

/*! @} */

#endif // STRING_HPP