#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <dispute/dispute.hpp>

using namespace disp;

TEST_CASE("test1")
{
    std::list<std::string> args = { "-a" };

    auto apple = false;

    flag_filter const filter(
        {
            flag(&apple, { 'a' })
        });

    filter(args);

    CHECK(args.empty());

    CHECK(apple);
}

TEST_CASE("test2")
{
    std::list<std::string> args = { "-a", "-b" };

    auto apple = false,
         banana = false;

    flag_filter const filter(
        {
            flag(&apple,  { 'a' }),
            flag(&banana, { 'b' })
        });

    filter(args);

    CHECK(args.empty());

    CHECK(apple);
    CHECK(banana);
}

TEST_CASE("test3")
{
    std::list<std::string> args = { "-ab" };

    auto apple = false,
         banana = false;

    flag_filter const filter(
        {
            flag(&apple,  { 'a' }),
            flag(&banana, { 'b' })
        });

    filter(args);

    CHECK(args.empty());

    CHECK(apple);
    CHECK(banana);
}

TEST_CASE("test4")
{
    std::list<std::string> args = { "--apple" };

    auto apple = false;

    flag_filter const filter(
        {
            flag(&apple, { "apple" })
        });

    filter(args);

    CHECK(args.empty());

    CHECK(apple);
}

TEST_CASE("test5")
{
    std::list<std::string> args = { "--apple=osx" };

    std::string apple;

    flag_filter const filter(
        {
            flag(&apple, { "apple" })
        });

    filter(args);

    CHECK(args.empty());

    CHECK(apple == "osx");
}
