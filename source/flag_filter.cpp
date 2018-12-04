#include <dispute/dispute.hpp>

disp::flag_filter::flag_filter(std::vector<flag> const& flags)
{
    for (auto const& flag : flags)
    {
        for (auto const& label : *flag)
            flag_map_.emplace(label, flag);
    }
}

void disp::flag_filter::operator()(std::list<std::string>& arguments) const
{
    auto constexpr FLAG_CHAR = '-';

    for (auto arg_it = arguments.begin(); arg_it != arguments.end(); ++arg_it)
    {
        auto argument = *arg_it;

        if (argument.front() != FLAG_CHAR)
            continue;

        argument = argument.substr(1);

        std::variant<bool, std::string> argument_value = true;

        auto const value_separator_position = argument.find_first_of('=');
        if (value_separator_position != std::string::npos)
        {
            argument_value = argument.substr(value_separator_position + 1);
            argument = argument.substr(0, value_separator_position);
        }

        if (argument.front() == FLAG_CHAR)
        {
            argument = argument.substr(1);

            auto const& [flags_begin, flags_end] = flag_map_.equal_range(argument);
            for (auto flag_it = flags_begin; flag_it != flags_end; ++flag_it)
                flag_it->second.set_value(argument_value);
        }
        else
        {
            for (auto const c : argument)
            {
                auto const& [flags_begin, flags_end] = flag_map_.equal_range(c);
                for (auto flag_it = flags_begin; flag_it != flags_end; ++flag_it)
                    flag_it->second.set_value(argument_value);
            }
        }

        arguments.erase(arg_it--);
    }
}
