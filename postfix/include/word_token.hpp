#pragma once

#include "token.hpp"

namespace translator
{
    class word_token final : public token
    {
    public:
        const std::string lexeme;

    public:
        word_token(const std::string &sequence, TAG token_tag)
            : token(token_tag), lexeme(sequence) {}

        std::string get() override
        {
            std::stringstream stream;
            stream << tag << ", " << lexeme;
            return stream.str();
        }
    };
}
