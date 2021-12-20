#pragma once

#include <string>
#include <sstream>

#include "tag.hpp"

namespace translator
{
    class token
    {
    public:
        int tag;

    public:
        token(int token_tag)
            : tag(token_tag) {}

        virtual std::string get()
        {
            std::stringstream stream;
            stream << static_cast<char>(tag);
            return stream.str();
        }
    };
}
