#pragma once

#include <list>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace disp
{
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
