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
        std::vector<std::variant<char, std::string>> const labels_;

        std::variant<bool*, std::string*> const value_;

    public:

        flag(
            std::vector<std::variant<char, std::string>> const& labels,
            std::variant<bool*, std::string*> const& value);

        std::vector<std::variant<char, std::string>> const& labels() const;

        void set_value(bool value) const;
        void set_value(std::string const& value) const;
    };

    class flag_filter
    {
        std::vector<flag> const flags_;

        std::unordered_multimap<char, flag const*> short_labels_;
        std::unordered_multimap<std::string, flag const*> long_labels_;

    public:

        explicit flag_filter(std::vector<flag> flags);

        void operator()(std::list<std::string>& arguments) const;
    };
}
