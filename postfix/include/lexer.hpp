#pragma once

#include <map>
#include <memory>
#include <iostream>

#include "integer_token.hpp"
#include "floating_token.hpp"

#include "word_token.hpp"
#include "relation_token.hpp"

#include "translation_error.hpp"

namespace translator
{
    class lexer final
    {
    private:
        using char_type = char;

        std::size_t line{1UL};
        char_type peek{' '};

        std::map<std::string, word_token> words;

        void reserve(word_token word)
        {
            words.emplace(word.lexeme, word);
        }

        std::basic_istream<char> &stream;

    public:
        lexer(std::basic_istream<char> &_stream)
            : stream(_stream)
        {
            reserve(word_token("true", TAG::TRUE));
            reserve(word_token("false", TAG::FALSE));
            //  reserve(relation_token("&&", TAG::AND));
            //  reserve(relation_token("||", TAG::OR));
            //  reserve(relation_token("^", TAG::XOR));
            //  reserve(relation_token("!", TAG::NOT));
            //  reserve(relation_token("~", TAG::COMPL));
            //  reserve(relation_token("|", TAG::BITOR));
            //  reserve(relation_token("&", TAG::BITAND));
            //  reserve(relation_token("&=", TAG::AND_EQ));
            //  reserve(relation_token("|=", TAG::OR_EQ));
            //  reserve(relation_token("^=", TAG::XOR_EQ));
            //  reserve(relation_token("!=", TAG::NOT_EQ));
        }

        std::shared_ptr<token> scan()
        {
            //  Lexical analyzer extension to remove spaces and tabs
            for (;; peek = stream.get())
            {
                if (peek == ' ' || peek == '\t')
                    continue;
                //  Сounting the number of lines read
                else if (peek == '\n')
                    ++line;
                else
                    break;
            }

            //  2.6.1
            //  Lexical analyzer extension to remove comments
            if (peek == '/')
            {
                peek = stream.get();
                //  The comment starts with the characters / / and
                //  includes all characters up to the end of this line
                if (peek == '/')
                {
                    while (stream.get())
                    {
                        if (peek == '\n')
                            break;
                    }
                    ++line;
                }

                //  The comment starts with a sequence of characters / *
                //  and includes all characters up to the sequence * /
                else if (peek == '*')
                {
                    auto behind{' '};
                    peek = stream.get();
                    while ((behind = peek), (peek = stream.get()))
                    {
                        if (peek == '\n')
                            ++line;
                        if (behind == '*' && peek == '/')
                            break;
                    }
                }
                else
                {
                    throw translation_error("comment error");
                }
            }

            //  2.6.2
            //  Extension of the lexical analyzer for recognition
            //  of relation operators
            if (relation_operators.find(peek) != std::string::npos)
            {
                std::string buffer(1UL, peek);
                peek = stream.get();
                if (peek == '=')
                    buffer.push_back(peek);
                return std::make_shared<relation_token>(buffer);
            }

            //  Number recognition
            if (std::isdigit(peek) || peek == '.')
            {
                auto integer_value{0};
                if (std::isdigit(peek))
                {
                    do
                    {
                        integer_value = integer_value * 10 + (peek - '0');
                        peek = stream.get();
                    } while (std::isdigit(peek));
                    if (peek != '.')
                        return std::make_shared<integer_token>(integer_value);
                }

                //  Extension of the lexical analyzer for recognition of
                //  floating-point numbers [2., 3.14, .5]
                auto float_point_value{static_cast<double>(integer_value)};
                auto delimiter{10.0};

                while ((peek = stream.get()) && std::isdigit(peek))
                {
                    float_point_value += (peek - '0') / delimiter;
                    delimiter *= 10.0;
                }
                return std::make_shared<floating_token>(float_point_value);
            }

            //  Word recognition
            if (std::isalpha(peek))
            {
                std::string buffer;
                do
                {
                    buffer.push_back(peek);
                    peek = stream.get();
                } while (std::isalnum(peek));

                auto word{words.find(buffer)};
                if (word == words.end())
                {
                    words.emplace(buffer, word_token(buffer, TAG::IDENTIFIER));
                }
                return std::make_shared<word_token>(buffer, TAG::IDENTIFIER);
            }

            auto symbol(peek);
            peek = ' ';
            return std::make_shared<token>(symbol);
        }
    };

    //template <typename CharT, typename Traits = std::char_traits<CharT>>
    //lexer<CharT, Traits>(std::basic_istream<CharT, Traits>& ) -> lexer<CharT, Traits>;
}
