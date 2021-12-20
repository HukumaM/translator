#include <iostream>
#include <cstring>

#include "postfix.hpp"

#include "lexer.hpp"

auto main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) -> int
{
    if (argc < 2)
    {
        std::cerr << "Usage:\t"
                  << argv[0] << " [--translator]\n\t"
                  << argv[0] << " [--lexer]\n";
    }
    else if (!std::strcmp(argv[1], "--translator"))
    {
        std::cout << "Translator of arithmetic expressions into postfix notation."
                  << std::flush;

        translator::postfix parse;

        try
        {
            std::cout << "\n< " << std::flush;
            parse.translate();
        }
        catch (translator::translation_error &error)
        {
            std::cerr << '\n'
                      << error.what() << ": the expression must consist of single"
                      << "\ndigits and binary operators plus('+') and minus('-')."
                      << std::endl;
        }
        std::cout << std::endl;
    }
    else if (!std::strcmp(argv[1], "--lexer"))
    {
        translator::lexer lex(std::cin);

        do
        {
            std::shared_ptr<translator::token> token = lex.scan();
            std::cout << "[" << token->get() << "]\n";
        } while (!std::cin.eof());
    }
}
