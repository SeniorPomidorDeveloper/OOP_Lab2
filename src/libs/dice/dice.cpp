#include "dice.hpp"

/*!
    \addtogroup Dice_module
    @{
*/

#include <limits>
#include <numeric>

/*!
    \brief Стандартный конструктор
    \details Создаёт объект класса Dice, не чем не заполняя его.
*/
Dice::Dice() noexcept
{
}

/*!
    \brief Конструктор копирования
    \details Создаёт объект класса Dice, повторябщий объект other.

    \param[in] other ссылка на другой объект класса Dice.
*/
Dice::Dice(const Dice &other)
{
    *this = other;
}

/*!
    \brief Конструктор перемещения
    \details Переносит содержимое из other в текущий объект.

    \param[in] other перемещающая ссылка на другой объект класса Dice.
*/
Dice::Dice(Dice &&other)
{
    *this = std::move(other);
}

/*!
    \brief Конструктор с кол-вом костей
    \details Создаёт объект класса Dice и заполнет size костями со случайным значением.

    \param[in] size кол-во костей.
*/
Dice::Dice(const size_t size)
{
    arr = Vector<OneDice>(size);
}

/*!
    \brief Конструктор со значениями костей
    \details Создаёт объект класса Dice и заполняет его костями со значениями из input_vector.

    \param[in] input_vector ссылка на вектор содержащий значения костей.
*/
Dice::Dice(const Vector<NumPoints> &input_vector)
{
    arr = Vector<OneDice>(input_vector.get_size());
    Vector<NumPoints>::iterator iter = input_vector.cbegin();
    std::for_each(arr.begin(), arr.end(),
                  [&iter](OneDice &dice)
                  {
                      dice.set_value(*iter);
                      ++iter;
                  });
}

/*!
    \brief Геттер размера
    \details Возвращает размер вектора костей.

    \return Размер вектора костей.
*/
size_t Dice::get_size() const noexcept
{
    return arr.get_size();
}

/*!
    \brief Геттер AsciiArt
    \details Возвращает значения костей в виде объекта AsciiArt.

    \return Размер вектора костей.
*/
AsciiArt Dice::get_AsciiArt() const noexcept
{
    if (get_size() == 0)
        return AsciiArt();
    return std::accumulate(arr.cbegin() + 1, arr.cend(), (*(arr.cbegin())).get_value_AsciiArt(),
                           [](AsciiArt &a, const OneDice &b) { return a + b.get_value_AsciiArt(); });
}

/*!
    \brief Проверка на содержание кости с определённым значением
    \details Проверяет находтся в текущем объекте кость со значением value.

    \param[in] value значение кости.

    \return True если текущий объект имеет кость со значением value. Иначе False.

    \throw std::invalid_argument - если value не может являться значением кости.
*/
bool Dice::has_NumPoints(const NumPoints value) const
{
    if (!check_NumPoints(value))
        throw std::invalid_argument("Uncorrect argument value!");
    return std::find_if(arr.cbegin(), arr.cend(),
                        [&value](const OneDice &dice) { return dice.get_value() == value; }) != arr.cend();
}

/*!
    \brief Сумма значений костей
    \details Суммируте значения костей.

    \return Сумму значений костей.
*/
NumPoints Dice::sum() const noexcept
{
    return std::accumulate(arr.cbegin(), arr.cend(), 0,
                           [](const NumPoints &a, const OneDice &b) { return a + b.get_value(); });
}

/*!
    \brief Оператор копирования
    \details Копирует содержимое из other в текущий объект.

    \param[in] other ссылка на другой объект класса Dice.

    \return Ссылку на текущий объект.
*/
Dice &Dice::operator=(const Dice &other)
{
    arr = other.arr;
    return *this;
}

/*!
    \brief Оператор перемещения
    \details Переносит содержимое из other в текущий объект.

    \param[in] other ссылка на другой объект класса Dice.

    \return Ссылку на текущий объект.
*/
Dice &Dice::operator=(Dice &&other)
{
    arr = std::move(other.arr);
    return *this;
}

/*!
    \brief Оператор ()
    \details Перегрузка оператора (). Бросает все кости.
*/
void Dice::operator()() noexcept
{
    std::for_each(arr.begin(), arr.end(), [](OneDice &dice) { dice.to_change_value(); });
}

/*!
    \brief Оператор ()
    \details Перегрузка оператора (). Бросает кость с индексом index.

    \param[in] index индекс кости.

    \return Новое значение кости с индексом index.

    \throw std::out_of_range - если index выходит за границы вектора.
*/
NumPoints Dice::operator()(const size_t index)
{
    if (index >= arr.get_size())
        throw std::out_of_range("Index out of range");
    return arr[index].to_change_value();
}

/*!
    \brief Оператор +=
    \details Перегрузка оператора +=. Добавляет кость other в текущий объект.

    \param[in] other ссылка на другой объект класса OneDice.

    \return Ссылку на текущий объект.
*/
Dice &Dice::operator+=(const OneDice &other)
{
    arr.push_back(other);
    return *this;
}

/*!
    \brief Оператор -=
    \details Перегрузка оператора -=. Удаляет все кости с определённым значением value из текущего объекта

    \param[in] value значение кости.

    \return Ссылку на текущий объект.

    \throw std::invalid_argument - если value не может являться значением кости.
*/
Dice &Dice::operator-=(const NumPoints value)
{
    if (!check_NumPoints(value))
        throw std::invalid_argument("Invalid argument value!");
    for (Vector<OneDice>::iterator iter = arr.begin(); iter != arr.end(); ++iter)
    {
        if ((*iter).get_value() == value)
        {
            arr.erase(iter);
            --iter;
        }
    }
    return *this;
}

/*!
    \brief Оператор []
    \details Перегрузка оператора []. Возвращет ссылку на кость с индексом index.

    \param[in] index индекс кости.

    \return Ссылку на кость с индексом index.

    \throw std::out_of_range - если index выходит за границы вектора.
*/
OneDice &Dice::operator[](size_t index)
{
    if (index >= arr.get_size())
        throw std::out_of_range("Index out of range");
    return arr[index];
}

/*!
    \brief Оператор ввода
    \details Перегрузка оператора >>. Заполняет поля объекта dice значениями из потока ввода in.

    \param[in] in ссылка потока ввода.
    \param[out] dice ссылка на объект Dice.

    \return Ссылку на поток ввода in.

    \throw std::invalid_argument - если в потоке ввода неверно определённое число или значение кости.
*/
std::istream &operator>>(std::istream &in, Dice &dice)
{
    dice = Dice();
    size_t count;
    in >> count;
    for (size_t i = 0; i < count; ++i)
    {
        NumPoints value;
        in >> value;
        if (in.fail())
        {
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::invalid_argument("Invalid input value!");
        }
        dice.arr.push_back(OneDice(value));
    }
    return in;
}

/*!
    \brief Оператор вывода
    \details Перегрузка оператора <<. Выводит объект класса Dice в поток вывода out.

    \param[in] out ссылка потока ввода.
    \param[in] dice ссылка на объект Dice.

    \return Ссылку на поток вывода out.
*/
std::ostream &operator<<(std::ostream &out, const Dice &dice) noexcept
{
    out << "{";
    std::for_each(dice.arr.cbegin(), dice.arr.cend() - 1,
                  [&out](const OneDice &item) { out << item.get_value() << ", "; });
    if (!dice.arr.is_empty())
        out << (*(dice.arr.cend() - 1)).get_value();
    out << "}";
    return out;
}

/*! @} */