/*!
    \defgroup OneDice_submodule Игральная кость
    \ingroup Dice_module
*/
#ifndef ONE_DICE_HPP
#define ONE_DICE_HPP

/*!
    \addtogroup OneDice_submodule
    @{
*/

#include "../../asciiArt/asciiArt.hpp"
#include "./odds/odds.hpp"

typedef unsigned short int NumPoints; ///< Количество очков выпавшего значения

bool check_NumPoints(const NumPoints num);
NumPoints random_odds(const Odds &input_odds);

/*!
    \brief Класс для работы с одной игральной костью
    \details Объект OneDice хранит выпавшее значение кости, вероятности выпадения каждого значения.

    \sa Odds, AsciiArt
*/
class OneDice
{
    private:
        Odds odds;
        NumPoints value = 0;

    public:
        OneDice(const Odds &input_odds = Odds());
        OneDice(const NumPoints input_value, const Odds &input_odds = Odds());
        OneDice(const OneDice &other);
        OneDice(OneDice &&other);

        void set_odds(const Odds &input_odds);
        void set_value(const NumPoints value);

        NumPoints get_value() const;
        AsciiArt get_value_AsciiArt() const;
        Odds get_odds() const;

        NumPoints to_change_value();

        bool operator==(const OneDice &other) const;

        void input(std::istream &input);
        void output(std::ostream &output) const;

        OneDice &operator=(const OneDice &other);
        OneDice &operator=(OneDice &&other);

        friend std::istream &operator>>(std::istream &input, OneDice &dice);
        friend std::ostream &operator<<(std::ostream &output, const OneDice &dice);
};

/*! @} */
#endif // ONE_DICE_HPP