#include "oneDice.hpp"

/*!
    \addtogroup OneDice_submodule
    @{
*/

#include <algorithm>
#include <cstring>
#include <limits>
#include <random>

/*!
    \brief Проверка выпавшего числа кости
    \details Функция проверяет правильность выпавшего числа кости.

    \param[in] num значение кости.

    \return True если значение 1 <= num <= 6. Иначе False.
*/
bool check_NumPoints(const NumPoints num)
{
    return num >= 1 && num <= 6;
}

/*!
    \brief Генератор AsciiArt
    \details Функция выбирает AscciArt в виде строки в зависимости от значения аргумента num.

    \param[in] num значение кости.

    \return Строка с ASCII-изображением.

    \throw std::invalid_argument - если num == 0 или num > 6.
*/
AsciiArt NumPoints_to_AsciiArt(const NumPoints num)
{
    if (!check_NumPoints(num))
        throw std::invalid_argument("Invalid argument num!");
    const char *arts[6][8] = {{"   ________ ", "  /       /|", " /       / |", "/_______/  |", "|       |  /",
                               "|   o   | / ", "|       |/  ", "L_______/   "},
                              {"   ________ ", "  /       /|", " /       / |", "/_______/  |", "|  o    |  /",
                               "|       | / ", "|    o  |/  ", "L_______/   "},
                              {"   ________ ", "  /       /|", " /       / |", "/_______/  |", "|  o    |  /",
                               "|   o   | / ", "|    o  |/  ", "L_______/   "},
                              {"   ________ ", "  /       /|", " /       / |", "/_______/  |", "|  o o  |  /",
                               "|       | / ", "|  o o  |/  ", "L_______/   "},
                              {"   ________ ", "  /       /|", " /       / |", "/_______/  |", "|  o o  |  /",
                               "|   o   | / ", "|  o o  |/  ", "L_______/   "},
                              {"   ________ ", "  /       /|", " /       / |", "/_______/  |", "|  o o  |  /",
                               "|  o o  | / ", "|  o o  |/  ", "L_______/   "}};

    AsciiArt result;
    for (const char *line : arts[num - 1])
        result.add_line(line);

    return result;
}

/*!
    \brief Поиск значения кости с учётом шанса
    \details Функция ищет значение кости в зависимости от рандомного числа и максимальных значений выпадения.

    \param[in] prefix указатель на массив максимальных значений случайного числа для каждой грани.
    \param[in] random_num случайное число.

    \return Случайная грань кости.
*/
NumPoints find_value(const Chance *prefix, const NumPoints random_num)
{
    NumPoints mid;
    NumPoints left = 0, right = 5;
    while (left < right)
    {
        mid = left + ((right - left) >> 1);
        if (random_num > prefix[mid])
            left = mid + 1;
        else
            right = mid;
    }
    return left + 1;
}

/*!
    \brief Генератор случайной грани кости
    \details Функция генерирует случайную грань кости в соответствии с заданными шансами.

    \param[in] input_odds ссылка на шансы выпадения граней.

    \return Случайная грань кости.
*/
NumPoints random_odds(const Odds &input_odds)
{
    Chance prefix[6];
    prefix[0] = input_odds.get_odds(0);
    for (size_t i = 1; i < 6; ++i)
        prefix[i] = prefix[i - 1] + input_odds.get_odds(i);
    NumPoints random_num = (rand() % prefix[5]) + 1;
    return find_value(prefix, random_num);
}

/*!
    \brief Сеттер шансов кости
    \details Помещает шансы кости в объект класса OneDice.

    \param[in] input_odds ссылка на объект Odds, содержащий шансы кости.
*/
void OneDice::set_odds(const Odds &input_odds)
{
    odds = input_odds;
}

/*!
    \brief Сеттер значения кости
    \details Меняет значение кости.

    \param[in] input_value значение кости.

    \throw std::invalid_argument - если значение кости < 1 или > 6.
*/
void OneDice::set_value(const NumPoints input_value)
{
    if (!check_NumPoints(input_value))
        throw std::invalid_argument("Invalid value!");
    value = input_value;
}

/*!
    \brief Конструктор с пользовательским шансами
    \details Создаёт класс OneDice шансы выпадения каждого числа в котором передаются по ссылке input_odds. Значение
   сразу генерируется.

    \param[in] input_odds ссылка на объект Odds, содержащий шансы кости.
*/
OneDice::OneDice(const Odds &input_odds)
{
    set_odds(input_odds);
    to_change_value();
}

/*!
    \brief Конструктор с пользовательским шансами и выпавшим значением
    \details Создаёт класс OneDice шансы выпадения каждого числа в котором передаются по ссылке input_odds. Значение
   сразу генерируется.

    \param[in] input_odds ссылка на объект Odds, содержащий шансы кости.
*/
OneDice::OneDice(const NumPoints input_value, const Odds &input_odds)
{
    set_odds(input_odds);
    set_value(input_value);
}

/*!
    \brief Конструктор копирования
    \details Создаёт объект класса OneDice повтаряющий объект other.

    \param[in] other ссылка на другой объект OneDice.
*/
OneDice::OneDice(const OneDice &other)
{
    *this = other;
}

/*!
    \brief Конструктор перемещения
    \details Перемещает содержимое объекта other в текущий.

    \param[in] other ссылка на другой объект OneDice.
*/
OneDice::OneDice(OneDice &&other)
{
    *this = std::move(other);
}

/*!
    \brief Геттер значения кости
    \details Возвращает текущее значение кости.

    \return Текущее значение кости.
*/
NumPoints OneDice::get_value() const
{
    return value;
}

/*!
    \brief Геттер ASCII-изображения значения кости
    \details Возвращает Ascii-изображение текущего значения кости.

    \return AsciiArt с текущим значением кости.
*/
AsciiArt OneDice::get_value_AsciiArt() const
{
    return NumPoints_to_AsciiArt(value);
}

/*!
    \brief Геттер шансов кости
    \details Возвращает копию текущих шансов кости.

    \return Копия текущих шансов кости.
*/
Odds OneDice::get_odds() const
{
    return Odds(odds);
}

/*!
    \brief Конструктор с пользовательским шансами и
    \details Создаёт класс OneDice шансы выпадения каждого числа в котором передаются по ссылке input_odds. Значение
   сразу генерируется.

    \param[in] input_odds ссылка на объект Odds, содержащий шансы кости.
*/
NumPoints OneDice::to_change_value()
{
    value = random_odds(odds);
    return value;
}

/*!
    \brief Оператор ==
    \details Перегрузка оператора == для сравнения двух объектов OneDice. Сравнивается их выпавшее значение.

    \param[in] other ссылка на другой объект OneDise.

    \return true - если выпавшее значение обоих объектов совпадает, иначе false.
*/
bool OneDice::operator==(const OneDice &other) const
{
    return value == other.value;
}

/*!
    \brief Ввод
    \details Вводит поля обьекта OneDice из потока ввода.

    \param[in] input ссылка на поток ввода.

    \throw std::invalid_argument - если введенное значение кости < 1 или > 6.
*/
void OneDice::input(std::istream &input)
{
    NumPoints input_value;
    input >> input_value >> odds;
    if (input.fail())
    {
        input.clear();
        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Invalid input value!");
    }
    set_value(input_value);
}

/*!
    \brief Вывод
    \details Выводит поля обьекта OneDice в поток вывода.

    \param[in] out ссылка на поток вывода.
*/
void OneDice::output(std::ostream &out) const
{
    out << "{value: " << value << "; odds: " << odds << "}";
}

/*!
    \brief Оператор копирования
    \details Создаёт объект класса OneDice повтаряющий объект other.

    \param[in] other ссылка на другой объект OneDice.

    \return Ссылка на текущий объект.
*/
OneDice &OneDice::operator=(const OneDice &other)
{
    if (this == &other)
        return *this;
    value = other.value;
    odds = other.odds;
    return *this;
}

/*!
    \brief Оператор перемещения
    \details Перемещает содержимое объекта other в текущий.

    \param[in] other ссылка на другой объект OneDice.

    \return Ссылка на текущий объект.
*/
OneDice &OneDice::operator=(OneDice &&other)
{
    value = std::move(other.value);
    odds = std::move(other.odds);
    other.value = 0;
    return *this;
}

/*!
    \brief Оператор >>
    \details Перегрузка оператора >> для ввода полей обьекта OneDice из потока ввода.

    \param[in] input ссылка на поток ввода.
    \param[out] dice ссылка на объект класса OneDice.

    \return Ссылка на поток ввода.
*/
std::istream &operator>>(std::istream &input, OneDice &dice)
{
    dice.input(input);
    return input;
}

/*!
    \brief Оператор <<
    \details Перегрузка оператора << для вывода полей обьекта OneDice в поток вывода.

    \param[in] output ссылка на поток вывода.
    \param[in] dice ссылка на объект класса OneDice.

    \return Ссылка на поток вывода.
*/
std::ostream &operator<<(std::ostream &output, const OneDice &dice)
{
    dice.output(output);
    return output;
}

/*! @} */