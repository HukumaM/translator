#include <iostream>

#include "postfix.hpp"

auto main(int argc, char *argv[]) -> int
{
    using namespace translator;
    std::cout << "Translator of arithmetic expressions into postfix notation."
              << std::flush;
    postfix parse;
    try
    {
        std::cout << "\n< " << std::flush;
        parse.translate();
    }
    catch (translation_error &error)
    {
        std::cerr << '\n'
                  << error.what() << ": the expression must consist of single"
                  << "\ndigits and binary operators plus('+') and minus('-')."
                  << std::endl;
    }
    std::cout << std::endl;
}
