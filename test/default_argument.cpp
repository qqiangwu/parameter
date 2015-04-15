#include <gtest/gtest.h>

#include <parameter/keyword.hpp>
#include <parameter/argument_io.hpp>
#include <parameter/argument_pack.hpp>
#include <iostream>

PARAMETER_KEYWORD(size);
PARAMETER_KEYWORD(pos);
PARAMETER_KEYWORD(ok);

struct Myt {
    PARAMETER_ENABLE_CONSTRUCTOR(Myt)

private:
    template <class... Args>
    Myt(parameter::Argument_pack<Args...> args)
    {
        EXPECT_EQ(args[size_ | 20], 10);
        EXPECT_EQ(args[pos_], "Hello world");
        EXPECT_EQ(args[ok_ | true], true);
        EXPECT_EQ(args[ok_ | false], false);
    }
};

TEST(default_argument_test, trivial_types)
{
    Myt v{size_ = 10, pos_ = "Hello world"};
}

template <class... Args>
void foo(Args... args)
{
    auto pack = parameter::pack_args(args...);

    EXPECT_EQ(pack[size_], 1000);
    EXPECT_EQ(pack[ok_ | false], false);
}

TEST(default_argument_test, function)
{
    foo(size_ = 1000, pos_ = true);
}

template <class... Args>
void bar(Args... args)
{
    auto pack = parameter::pack_args(args...);

    EXPECT_EQ(pack[size_ | 1000], 1000);
    EXPECT_EQ(pack[ok_ | false], false);
}

TEST(default_argument_test, empty_function)
{
    bar();
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}