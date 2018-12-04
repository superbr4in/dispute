#include <sstream>

#include <dispute/dispute.hpp>

disp::format_string::format_string()
{
    constants_.push_back({ });
}

disp::format_string::format_string(std::string const& base)
{
    std::stringstream ss_constant, ss_escaped;

    auto escape = false;
    for (auto const cur_char : base)
    {
        switch (cur_char)
        {
        case '{':
            escape = true;
            continue;
        case '}':
            escape = false;

            auto escaped = ss_escaped.str();

            if (escaped.empty())
                continue;

            char escaped_sign_char = escaped.front();
            auto escaped_sign_positive = true;
            switch (escaped_sign_char)
            {
            case '-':
                escaped_sign_positive = false;
            case '+':
                escaped = escaped.substr(1);
                break;
            }

            if (escaped.empty())
                continue;

            constants_.push_back(ss_constant.str());
            ss_constant.str("");

            variables_.emplace_back(escaped_sign_positive, escaped.front());
            ss_escaped.str("");

            continue;
        }

        if (escape)
            ss_escaped << cur_char;
        else
            ss_constant << cur_char;
    }

    constants_.push_back(ss_constant.str());
}

std::string disp::format_string::operator()(std::unordered_map<char, int> const& value_map) const
{
    std::vector<std::string> var_values;
    for (auto const& [sign, var] : variables_)
    {
        auto const it_value = value_map.find(var);

        var_values.push_back(
            it_value == value_map.end()
                ? "0"
                : std::to_string((sign ? 1 : -1) * it_value->second));
        break;
    }

    std::stringstream ss_result;
    ss_result << constants_.front();
    for (unsigned i = 0; i < var_values.size(); ++i)
        ss_result << var_values.at(i) << constants_.at(i + 1);

    return ss_result.str();
}
