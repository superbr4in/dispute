#include <dispute/dispute.h>
#include <simple-visitation/visitor.h>

disp::flag_filter::flag_filter(std::vector<flag> flags)
    : flags_(std::move(flags))
{
    for (auto const& flag : flags_)
    {
        for (auto const& label : flag.labels())
        {
            std::visit(
                hit::generic_visitor
                {
                    [this, &flag](char const value)
                    {
                        short_labels_.emplace(value, &flag);
                    },
                    [this, &flag](std::string const& value)
                    {
                        long_labels_.emplace(value, &flag);
                    }
                },
                label);
        }
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

        if (argument.front() == FLAG_CHAR)
        {
            argument = argument.substr(1);

            auto const& [flags_begin, flags_end] = long_labels_.equal_range(argument);
            for (auto flag_it = flags_begin; flag_it != flags_end; ++flag_it)
                flag_it->second->set_value(true);
        }
        else
        {
            for (auto const c : argument)
            {
                auto const& [flags_begin, flags_end] = short_labels_.equal_range(c);
                for (auto flag_it = flags_begin; flag_it != flags_end; ++flag_it)
                    flag_it->second->set_value(true);
            }
        }

        arguments.erase(arg_it--);
    }
}
