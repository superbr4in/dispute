#include <dispute/dispute.h>

disp::flag::flag(
    std::vector<std::variant<char, std::string>> const& labels,
    std::variant<bool*, std::string*> const& value)
    : labels_(labels), value_(value) { }

std::vector<std::variant<char, std::string>> const& disp::flag::labels() const
{
    return labels_;
}

void disp::flag::set_value(bool const value) const
{
    if (!std::holds_alternative<bool*>(value_))
        throw std::invalid_argument("Invalid value");

    *std::get<bool*>(value_) = value;
}
void disp::flag::set_value(std::string const& value) const
{
    if (!std::holds_alternative<std::string*>(value_))
        throw std::invalid_argument("Invalid value");

    *std::get<std::string*>(value_) = value;
}
