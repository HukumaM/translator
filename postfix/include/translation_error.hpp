#pragma once

#include <stdexcept>

namespace translator
{
    using namespace std::literals::string_literals;
    class translation_error final : public std::exception
    {
    private:
        const std::string message;

    public:
        translation_error() : message("file translation is broken"){};
        virtual ~translation_error() {}

    public:
        explicit translation_error(const std::string &description)
            : message(description) {}
        explicit translation_error(const char *description)
            : message(description) {}

    public:
        translation_error(const translation_error &) = default;
        translation_error &operator=(const translation_error &) = default;
        translation_error(translation_error &&) = default;
        translation_error &operator=(translation_error &&) = default;

    public:
        const char *what() const noexcept
        {
            return message.c_str();
        }
    };
}
