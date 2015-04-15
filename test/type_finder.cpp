#include <gtest/gtest.h>

#include <parameter/keyword.hpp>
#include <parameter/argument_io.hpp>
#include <parameter/argument_pack.hpp>
#include <iostream>
#include <string>

namespace test {
    PARAMETER_KEYWORD(size);
    PARAMETER_KEYWORD(pos);
    PARAMETER_KEYWORD(ok);
}

template <class... Args>
void foo(Args&&... args)
{
    auto pack = parameter::pack_args(args...);

    // Yeah, it's ugly
    EXPECT_EQ(pack.template get<std::string>(), "String");
    EXPECT_EQ(pack.template get<int>(), 100);
    EXPECT_EQ(pack.get(false), true);
}

template <class... Args>
void bar(Args&&... args)
{
    auto pack = parameter::pack_args(args...);

    EXPECT_EQ(parameter::get<std::string>(pack), "String");
    EXPECT_EQ(parameter::get<int>(pack), 100);
    EXPECT_EQ(parameter::get(pack, false), true);
}

template <class... Args>
void boo(Args&&... args)
{
    auto pack = parameter::pack_args(args...);

    EXPECT_EQ(parameter::get<0>(pack), "String");
    EXPECT_EQ(parameter::get<2>(pack), 100);
    EXPECT_EQ(parameter::get<1>(pack), true);
}

TEST(argument_type, member_version)
{
    foo(std::string{"String"}, true, 100);
}

TEST(argument_type, standalone_version)
{
    bar(std::string{"String"}, true, 100);
}

TEST(argument_type, index_version)
{
    boo(std::string{"String"}, true, 100);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}