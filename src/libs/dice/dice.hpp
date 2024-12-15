/*!
    \defgroup Dice_module Модуль dice
    \brief Игральные кости
    \details Этот модуль реализует работу с игральными костями. При использование кости может выпасть 1 из 6 значений.
*/
#ifndef DICE_HPP
#define DICE_HPP

/*!
    \addtogroup Dice_module
    @{
*/

#include "./oneDice/oneDice.hpp"

/*!
    \brief Класс для работы с группой костей
    \details Объект Dice хранит vector объектов класса OneDice.
*/
class Dice
{
    private:
        Vector<OneDice> arr;

    public:
        Dice() noexcept;
        Dice(const Dice &other);
        Dice(Dice &&other);

        Dice(const size_t size);
        Dice(const Vector<NumPoints> &input_vector);

        size_t get_size() const noexcept;
        AsciiArt get_AsciiArt() const noexcept;

        bool has_NumPoints(const NumPoints value) const;

        NumPoints sum() const noexcept;

        Dice &operator=(const Dice &other);
        Dice &operator=(Dice &&other);

        void operator()() noexcept;
        NumPoints operator()(const size_t index);
        Dice &operator+=(const OneDice &other);
        Dice &operator-=(const NumPoints value);
        OneDice &operator[](size_t index);

        friend std::istream &operator>>(std::istream &in, Dice &dice);
        friend std::ostream &operator<<(std::ostream &out, const Dice &dice) noexcept;
};

/*! @} */

#endif