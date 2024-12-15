#include "string.hpp"

/*!
    \addtogroup String_module
    @{
*/

#include <cstring>

/*!
    \brief Стандартный конструктор
    \details Создаёт объект класса String, содержащий пустую строку.
*/
String::String()
{
    data[0] = '\0';
    size = 1;
}

/*!
    \brief Конструктор на основе cstring
    \details Создаёт объект класса String, содержащий копию строки str.

    \param[in] str указатель на строку фомата cstring.
*/
String::String(const char *str)
{
    *this = str;
}

/*!
    \brief Конструктор копирования
    \details Создаёт объект класса String, содержащий копию строки объекта other.

    \param[in] other ссылка на объект String, который нужно скопировать.
*/
String::String(const String &other) : Vector<char>(other)
{
}

/*!
    \brief Конструктор перемещения
    \details Создаёт объект класса String, перемещаяя содержимое объекта other.

    \param[in] other ссылка на объект String, содержимое которого нужно переместить.
*/
String::String(String &&other) : Vector<char>(std::move(other))
{
}

/*!
    \brief Деструктор
    \details Уничтожает объект, освобождая выделенную память.
*/
String::~String()
{
}

/*!
    \brief Изменение размера массива
    \details Расширяет массив, делая его размер равному new_size.

    \param[in] new_size новый размер массива.
*/
void String::resize(size_t new_size)
{
    Vector<char>::resize(new_size);
    size = new_size;
}

/*!
    \brief Геттер длины строки
    \details Возвращает длину строки, не включая детерминирующий ноль.

    \return Длина строки.
*/
size_t String::get_length() const noexcept
{
    return size - 1;
}

/*!
    \brief Геттер константной строки формата cstring
    \details Возвращает константную строку формата сstring.

    \return Константную строку формата сstring.
*/
const char *String::get_cstring() const noexcept
{
    return data;
}

/*!
    \brief Оператор +
    \details Перегрузка оператора +. Конкатинация строк. Склеивает два объекта String в один.

    \param[in] other ссылка на объект String, который нужно конкатенировать.

    \return Результат в формате объекта String.
*/
String String::operator+(const String &other) const
{
    String result = *this;
    result.resize(result.get_size() + other.size - 1);
    result.insert(result.end() - 1, other.cbegin(), other.cend());
    return result;
}

/*!
    \brief Оператор +=
    \details Перегрузка оператора +=. Конкатинация строк. Приклеивает строку other к текущей строке.

    \param[in] other ссылка на объект String, который нужно конкатенировать.

    \return Ссылку на текущий объект.
*/
String &String::operator+=(const String &other)
{
    size_t old_len = get_length();
    resize(size + other.size - 1);
    std::copy(other.cbegin(), other.cend(), begin() + old_len);
    return *this;
}

/*!
    \brief Оператор вывода
    \details Перегрузка оператора <<. Выводит строку str.

    \param[in] out ссылка на поток вывода.
    \param[in] str ссылка на объект String, которую нужно вывести.

    \return Ссылку на поток вывода out.
*/
std::ostream &operator<<(std::ostream &out, const String &str)
{
    return out << str.get_cstring();
}

/*!
    \brief Оператор копирования
    \details Создаёт объект класса String, содержащий копию строки объекта other.

    \param[in] other ссылка на объект String, который нужно скопировать.

    \return Ссылку на текущий объект.
*/
String &String::operator=(const String &other) noexcept
{
    resize(other.size);
    std::copy(other.cbegin(), other.cend(), begin());
    return *this;
}

/*!
    \brief Оператор присваения cstring
    \details Создаёт объект класса String, содержащий копи. строки формата cstring.

    \param[in] str указатель на строку формата cstring.

    \return Ссылку на текущий объект.
*/
String &String::operator=(const char *str)
{
    size_t len = strlen(str);
    resize(len + 1);
    std::copy(str, str + len + 1, begin());
    return *this;
}

/*! @} */