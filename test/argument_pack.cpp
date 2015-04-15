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
        EXPECT_EQ(args[size_], 10);
        EXPECT_EQ(args[pos_], "Hello world");
        EXPECT_EQ(args[ok_], true);
    }
};

TEST(argument_test, trivial_types)
{
    Myt v{size_ = 10, pos_ = "Hello world", ok_ = true};
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}