#include "program.hpp"

#include <functional>
#include <limits>

typedef unsigned short int OptionType;

NumPoints input_NumPoints()
{
    NumPoints value;
    std::cout << "Enter NumPoints: ";
    std::cin >> value;
    if (std::cin.fail() || !check_NumPoints(value))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error("Invalid input value!");
    }
    return value;
}

OneDice input_OneDice()
{
    OneDice dice;
    std::cout << "Enter OneDice: ";
    std::cin >> dice;
    return dice;
}

void add_OneDice(Dice &dice)
{
    dice += input_OneDice();
}

void remove_OneDice(Dice &dice)
{
    dice -= input_NumPoints();
}

void update_OneDice(Dice &dice)
{
    size_t index;
    do
    {
        try
        {
            std::cout << "Enter index: ";
            std::cin >> index;
            dice(index);
            break;
        }
        catch (const std::out_of_range &error)
        {
            std::cerr << error.what() << std::endl;
        }
    } while (true);
}

void update_Dice(Dice &dice)
{
    dice();
}

void sum_Dice(Dice &dice)
{
    std::cout << "Sum: " << dice.sum() << std::endl;
}

OptionType program_menu(OptionType max_value)
{
    std::cout << "1. Add OneDice" << std::endl;
    std::cout << "2. Remove OneDice" << std::endl;
    std::cout << "3. Update OneDice" << std::endl;
    std::cout << "4. Update Dice" << std::endl;
    std::cout << "5. Sum" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Enter option: ";
    OptionType option;
    std::cin >> option;
    if (std::cin.fail() || option > max_value)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error("Unknown option");
    }
    return option;
}

void program(Dice &dice)
{
    std::function<void(Dice &)> functions[] = {add_OneDice, remove_OneDice, update_OneDice, update_Dice, sum_Dice};
    OptionType option, max_value = sizeof(functions) / sizeof(functions[0]);
    do
    {
        std::cout << dice.get_AsciiArt() << std::endl;
        try
        {
            option = program_menu(max_value);
        }
        catch (const std::runtime_error &error)
        {
            std::cerr << error.what() << std::endl;
            continue;
        }
        if (option != 0)
        {
            functions[option - 1](dice);
        }
    } while (option != 0);
}

Dice standart_init()
{
    return Dice();
}

Dice size_init()
{
    size_t size;
    std::cout << "Size: ";
    std::cin >> size;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error("Invalid input size!");
    }
    return Dice(size);
}

Dice Vector_init()
{
    size_t size;
    Vector<NumPoints> values;
    std::cout << "Enter size dice: ";
    std::cin >> size;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error("Invalid input size!");
    }
    std::cout << "Enter values dice:" << std::endl;
    for (size_t i = 0; i < size; ++i)
    {
        values.push_back(input_NumPoints());
    }
    return Dice(values);
}

OptionType init_menu(const OptionType max_value)
{
    std::cout << "1. Standart initialization" << std::endl;
    std::cout << "2. Size initialization" << std::endl;
    std::cout << "3. Vector initialization" << std::endl;
    std::cout << "Choose initialization: ";
    OptionType option;
    std::cin >> option;
    if (std::cin.fail() || option > max_value || option == 0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error("Unknown option");
    }
    return option;
}

void program_init()
{
    Dice dice;
    std::function<Dice()> functions[] = {standart_init, size_init, Vector_init};
    OptionType option, max_value = sizeof(functions) / sizeof(functions[0]);
    do
    {
        try
        {
            option = init_menu(max_value);
        }
        catch (const std::runtime_error &error)
        {
            std::cerr << error.what() << std::endl;
            continue;
        }
        dice = std::move(functions[option - 1]());
        option = max_value;
    } while (option != max_value);
    program(dice);
}