#include "odds.hpp"

/*!
    \addtogroup Odds_submodule
    @{
*/

#include <algorithm>
#include <stdexcept>
#include <limits>

/*!
    \brief Сеттер шансов кости
    \details Копирует массив шансов кости в объект Odds.

    \param[in] odds_arr указатель на массив шансов кости.

    \throw std::invalid_argument - если значение в массиве < 0 или сумма значений массива > 1.
*/
void Odds::set_odds(const Chance *odds_arr)
{
    // check_odds(odds_arr);
    std::copy(odds_arr, odds_arr + 6, odds);
}

/*!
    \brief Конструктор по умолчанию
    \details Создаёт объект Odds с стандартными шансами кости (1/6 для каждой грани).
*/
Odds::Odds()
{
    Chance standart_odds[6];
    Chance value = 1;
    std::fill(standart_odds, standart_odds + 6, value);
    set_odds(standart_odds);
}

/*!
    \brief Конструктор
    \details Создаёт объект Odds с пользовательскими шансами кости.

    \param[in] odds_arr указатель на массив шансов кости.

    \throw std::invalid_argument - если значение в массиве < 0 или сумма значений массива > 1.
*/
Odds::Odds(const Chance *odds_arr)
{
    set_odds(odds_arr);
}

/*!
    \brief Конструктор копирования
    \details Копирование обьектов класса Odds.

    \param[in] other ссылка на объект Odds, который нужно скопировать.
*/
Odds::Odds(const Odds& other)
{
    *this = other;
}

/*!
    \brief Конструктор перемещения
    \details Перемещения полей объекта other в текущий объект.

    \param[in] other ссылка на объект Odds.
*/
Odds::Odds(Odds&& other)
{
    *this = std::move(other.odds);
}

/*!
    \brief Геттер шансов кости
    \details Возвращает шанс грани кости в объекте класса Odds.

    \param[in] index индекс грани кости.
    
    \return Возвращает шанс грани.

    \еthrow std::out_of_range - если index >= 6.
*/
Chance Odds::get_odds(const size_t index) const
{
    if (index >= 6) throw std::out_of_range("Index out of range!");
    return odds[index];
}

/*!
    \brief Оператор []
    \details Перегрузка оператора [] для доступа к элементу массива шансов кости.

    \param[in] index номер грани кости.

    \return ссылка на шанс выпадения грани кости.
    
    \throw std::out_of_range - если index >= 6.
*/
Chance &Odds::operator [] (const size_t index)
{
    if (index >= 6) throw std::out_of_range("Index out of range!");
    return odds[index];
}

/*!
    \brief Оператор копирования
    \details Перегрузка оператора = для копирования шансов кости.

    \param[in] other ссылка на объект класса Odds.

    \return ссылка текущий обьект Odds.
*/
Odds& Odds::operator=(const Odds& other)
{
    if (this != &other)
    {
        std::copy(other.odds, other.odds + 6, odds);
    }
    return *this;
}

/*!
    \brief Оператор перемещения
    \details Перегрузка оператора = для перемещения шансов кости.

    \param[in] other ссылка на объект класса Odds.

    \return ссылка текущий обьект Odds.
*/
Odds& Odds::operator=(Odds&& other)
{
    *this = other;
    return *this;
}

/*!
    \brief Оператор >>
    \details Перегрузка оператора << для вводв в входной поток.

    \param[in] input файл входного потока.
    \param[out] odds ссылка на обьект класса Odds.
    
    \return Возвращает ссылку на входной поток.

    \throw std::invalid_argument - если введенное значение не является числом.
*/
std::istream &operator >> (std::istream &input, Odds& odds)
{
    Chance odds_arr[6];
    for (size_t i = 0; i < 6; ++i)
    {
        input >> odds_arr[i];
        if (input.fail())
        {
            input.clear();
            input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::invalid_argument("Invalid input value!");
        }
    }
    odds.set_odds(odds_arr);
    return input;
}

/*!
    \brief Оператор <<
    \details Перегрузка оператора << для выводв в выходной поток.

    \param[in] output файл выходного потока.
    \param[in] odds ссылка на обьект класса Odds.
    
    \return Возвращает ссылку на выходной поток.
*/
std::ostream &operator << (std::ostream &output, const Odds& odds)
{
    output << "{";
    for (size_t i = 0; i < 6; ++i)
    {
        output << odds.get_odds(i);
        if (i < 5) output << ", ";
    }
    output << "}";
    return output;
}

/*! @} */