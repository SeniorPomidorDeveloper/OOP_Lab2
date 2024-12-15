#include "asciiArt.hpp"

/*!
    \addtogroup AsciiArt_module
    @{
*/

#include <algorithm>
#include <cstring>
#include <functional>

/*!
    \brief Проверка строки на совместимость
    \details Функция проверяет размер вставляемой строки.

    \param[in] line ссылка на строку.
    \param[in] len предполагаемая длина строки.

    \return True если значение длина line и значение len совпадают. Иначе False.
*/
bool check_line(const String &line, const size_t len)
{
    if (line.get_length() != len)
        return false;
    return true;
}

/*!
    \brief Проверка матрицы ascii
    \details Функция проверяет матрицу ascii на правильность.

    \param[in] ascii_art ссылка на мастрицу ascii.

    \return True если длины всех строк матрицы одинаковы. Иначе False.
*/
bool check_Symbols(const Symbols &ascii_art)
{
    if (ascii_art.get_size() == 0)
        return false;
    std::function<bool(const String &)> check_line_func =
        std::bind(check_line, std::placeholders::_1, ascii_art[0].get_length());
    return std::any_of(ascii_art.cbegin(), ascii_art.cend(), check_line_func);
}

/*!
    \brief Ссетер ascii матрицы
    \details Функция устанавливает значение ascii матрицы.

    \param[in] ascii_art ссылка на мастрицу ascii.

    \throws std::invalid_argument - если ascii_art не является матрицей ascii.
*/
void AsciiArt::set_art(const Symbols &ascii_art)
{
    if (!check_Symbols(ascii_art))
        throw std::invalid_argument("Invalid ASCII art!");
    art = ascii_art;
}

/*!
    \brief Стандартный конструктор
    \details Создаёт объект класса AsciiArt, не чем не заполняя его.
*/
AsciiArt::AsciiArt()
{
}

/*!
    \brief Конструктор
    \details Создает объект AsciiArt с указанным ASCII-изображением.

    \param[in] ascii_art cтрока с ASCII-изображением кости.
*/
AsciiArt::AsciiArt(const Symbols &ascii_art)
{
    set_art(ascii_art);
}

/*!
    \brief Добавление новой строки
    \details Добавляет новую строку в ascii матрицу.

    \param[in] line указатель на строку.

    \throws std::invalid_argument - если длина line не совпадает с длиной ascii матрицы.
*/
void AsciiArt::add_line(const char *line)
{
    if (art.get_size() > 0)
    {
        size_t len = art[0].get_length();
        if (!check_line(line, len))
            throw std::invalid_argument("Invalid line!");
    }
    art.push_back(String(line));
}

/*!
    \brief Оператор <<
    \details Перегрузка оператора << для выводв в выходной поток.

    \param[in] out файл выходного потока.
    \param[in] right_art ссылка на обьект класса AsciiArt.

    \return Возвращает ссылку на выходной поток.
*/
std::ostream &operator<<(std::ostream &out, const AsciiArt &right_art)
{
    if (right_art.art.get_size() > 0)
    {
        std::for_each(right_art.art.cbegin(), right_art.art.cend() - 1,
                      [&out](const String &line) { out << line << std::endl; });
        out << right_art.art[right_art.art.get_size() - 1];
    }
    return out;
}

/*!
    \brief Оператор +
    \details Перегрузка оператора + для склеивания двух артов.

    \param[in] right_art ссылка на другой объект класса AsciiArt.

    \return Возвращает ссылку на новый объект класса AsciiArt.

    \throws std::invalid_argument - если высоты двух артов не совпадают.
*/
AsciiArt AsciiArt::operator+(const AsciiArt &right_art)
{
    if (art.get_size() != right_art.art.get_size())
        throw std::invalid_argument("Different sizes of ASCII art!");
    AsciiArt result(art);
    Symbols::iterator iter = right_art.art.cbegin();
    std::for_each(result.art.begin(), result.art.end(),
                  [&iter](String &line)
                  {
                      line += *iter;
                      ++iter;
                  });
    return result;
}

/*! @} */