#pragma once

#include <list>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace disp
{
    class format_string
    {
        std::vector<std::string> constants_;
        std::vector<std::pair<bool, char>> variables_;

    public:

        format_string();

        explicit format_string(std::string const& base);

        std::string operator()(std::unordered_map<char, int> const& value_map) const;
    };

    class flag
    {
        std::variant<bool*, std::string*> const value_pointer_;

        std::vector<std::variant<char, std::string>> const labels_;

    public:

        flag(
            std::variant<bool*, std::string*> value_pointer,
            std::vector<std::variant<char, std::string>> labels);

        void set_value(std::variant<bool, std::string> const& value) const;

        std::vector<std::variant<char, std::string>> const& operator*() const;
    };

    class flag_filter
    {
        std::unordered_multimap<std::variant<char, std::string>, flag> flag_map_;

    public:

        explicit flag_filter(std::vector<flag> const& flags);

        void operator()(std::list<std::string>& arguments) const;
    };
}
