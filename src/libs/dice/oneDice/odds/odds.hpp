/*! 
    \defgroup Odds_submodule Вероятности выпадения
    \ingroup OneDice_submodule
*/
#ifndef ODDS_HPP
#define ODDS_HPP

/*!
    \addtogroup Odds_submodule
    @{
*/

#include <cstddef>
#include <iostream>

typedef unsigned Chance; ///< Шанс выпадения для каждого значения

/*!
    \brief Класс для хранения вероятностей выпадения
    \details Объект Odds хранит указатель на массив вероятностей выпадения.
*/
class Odds
{
    private:
        Chance odds[6];
        void set_odds(const Chance *odds_arr);
        
    public:
        Odds();
        Odds(const Chance *odds_arr);
        Odds(const Odds& other);
        Odds(Odds&& other);

        Chance get_odds(const size_t index) const;

        Chance &operator [] (const size_t index);
        Odds& operator=(const Odds& other);
        Odds& operator=(Odds&& other);
        friend std::istream &operator >> (std::istream &input, Odds& odds);
        friend std::ostream &operator << (std::ostream &output, const Odds& odds);
};

/*! @} */

#endif // ODDS_HPP