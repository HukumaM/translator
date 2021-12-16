#pragma once

#include <stdexcept>

namespace translator
{
    class translation_error final : public std::exception
    {
    };
}
