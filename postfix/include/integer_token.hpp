#pragma once

#include "token.hpp"

namespace translator
{
    class integer_token final : public token
    {
    public:
        int value;

    public:
        integer_token(int _value)
            : token(TAG::INTEGER), value(_value) {}

        std::string get() override
        {
            std::stringstream stream;
            stream << tag << ", " << value;
            return stream.str();
        }
    };
}
