#pragma once

#include "token.hpp"

namespace translator
{
    class floating_token final : public token
    {
    public:
        double value;

    public:
        floating_token(double _value)
            : token(TAG::FLOATING), value(_value) {}

        std::string get() override
        {
            std::stringstream stream;
            stream << tag << ", " << value;
            return stream.str();
        }
    };
}
