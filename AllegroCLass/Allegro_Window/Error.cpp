
#include "Error.h"


void Error::Test_Entity(bool test, const std::string& description)
{
    try
    {
        if (test)
            return;
        else
            throw std::invalid_argument("Error in : ");

    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << description << std::endl;
        exit(EXIT_FAILURE);
    }
}