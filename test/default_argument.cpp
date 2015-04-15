#include <gtest/gtest.h>

#include <parameter/keyword.hpp>
#include <parameter/argument_io.hpp>
#include <parameter/argument_pack.hpp>
#include <iostream>

PARAMETER_KEYWORD(size);
PARAMETER_KEYWORD(pos);
PARAMETER_KEYWORD(ok);

struct Myt {
    template <class... Args>
    Myt(Args... args)
        : Myt(parameter::pack_args(std::forward<Args>(args)...))
    {
    }

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

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}