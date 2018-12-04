#include <dispute/dispute.hpp>

disp::flag::flag(
    std::variant<bool*, std::string*> const value_pointer,
    std::vector<std::variant<char, std::string>> const labels)
    : value_pointer_(std::move(value_pointer)), labels_(std::move(labels)) { }

void disp::flag::set_value(std::variant<bool, std::string> const& value) const
{
    if (std::holds_alternative<bool*>(value_pointer_))
        *std::get<bool*>(value_pointer_) = std::get<bool>(value);

    if (std::holds_alternative<std::string*>(value_pointer_))
        *std::get<std::string*>(value_pointer_) = std::get<std::string>(value);
}

std::vector<std::variant<char, std::string>> const& disp::flag::operator*() const
{
    return labels_;
}
