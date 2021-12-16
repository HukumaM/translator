#pragma once

#include <cctype>
#include <iosfwd>

#include "translation_error.hpp"

namespace translator
{
    class postfix final
    {
    private:
        using int_type = decltype(std::cin.get());
        int_type lookahead;

    public:
        void translate()
        {
            get_terminal();
            expression();
        }

    private:
        void expression()
        {
            term();
            while (true)
            {
                if (lookahead == '+')
                {
                    match('+');
                    term();
                    std::cout << '+' << std::flush;
                }
                else if (lookahead == '-')
                {
                    match('-');
                    term();
                    std::cout << '-' << std::flush;
                }
                else if (lookahead == '\n')
                {
                    return;
                }
                else
                {
                    throw translation_error("syntax error");
                }
            }
        }

        void term()
        {
            if (std::isdigit(lookahead))
            {
                std::cout << static_cast<char>(lookahead) << std::flush;
                match(lookahead);
            }
            else
            {
                throw translation_error("syntax error");
            }
        }

        void match(int_type terminal)
        {
            if (lookahead == terminal)
            {
                get_terminal();
            }
            else
            {
                throw translation_error("syntax error");
            }
        }

        void get_terminal()
        {
            lookahead = std::cin.get();
        }
    };
}
