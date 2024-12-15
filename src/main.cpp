#include "program.hpp"

int main()
{
    srand(time(NULL));
    try
    {
        program_init();
    }
    catch (const std::exception &error)
    {
        std::cerr << error.what() << std::endl;
    }
    return 0;
}
