/*!
    \defgroup AsciiArt_module Модуль asciiArt
*/
#ifndef ASCII_ART_HPP
#define ASCII_ART_HPP

#include "../string/string.hpp"
#include <iostream>

/*!
    \addtogroup AsciiArt_module
    @{
*/

typedef Vector<String> Symbols; ///< Символы для ASCII-изображения

/*!
    \brief Класс для работы с ASCII-изображением
    \details Объект AsciiArt хранит ASCII-изображение в виде строки.
*/
class AsciiArt
{
    private:
        Symbols art;

    public:
        AsciiArt();
        AsciiArt(const Symbols &ascii_art);

        void set_art(const Symbols &ascii_art);

        void add_line(const char *line);

        friend std::ostream &operator<<(std::ostream &out, const AsciiArt &right_art);
        AsciiArt operator+(const AsciiArt &right_art);
};

/*! @} */

#endif // ASCII_ART_HPP