#pragma once

#include "token.hpp"

namespace translator
{
    static const std::string relation_operators{"<=!>"};
    class relation_token final : public token
    {
    public:
        const std::string lexeme;

    public:
        relation_token(const std::string &sequence)
            : token(TAG::RELATION), lexeme(sequence) {}

        std::string get() override
        {
            std::stringstream stream;
            stream << tag << ", " << lexeme;
            return stream.str();
        }
    };
}
