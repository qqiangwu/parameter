# parameter
A simple C++14 named parameter library

[![Build Status](https://travis-ci.org/qqiangwu/parameter.svg)](https://travis-ci.org/qqiangwu/parameter)

[![Build status](https://ci.appveyor.com/api/projects/status/72808phwx80gnbjm/branch/master?svg=true)](https://ci.appveyor.com/project/qqiangwu/parameter/branch/master)

[![Build Status](https://webapi.biicode.com/v1/badges/qiangwu/qiangwu/parameter/master)](https://www.biicode.com/qiangwu/parameter) 

# Example: By keyword
```C++
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
```

# Example: By type
```C++
template <class... Args>
void foo(Args&&... args)
{
    auto pack = parameter::pack_args(args...);

    EXPECT_EQ(parameter::get<std::string>(pack), "String");
    EXPECT_EQ(parameter::get<int>(pack), 100);
    EXPECT_EQ(parameter::get(pack, false), true);
}

foo(std::string{"String"}, true, 100);
```

# Example: By index
```C++
template <class... Args>
void boo(Args&&... args)
{
    auto pack = parameter::pack_args(args...);

    EXPECT_EQ(parameter::get<0>(pack), "String");
    EXPECT_EQ(parameter::get<2>(pack), 100);
    EXPECT_EQ(parameter::get<1>(pack), true);
}

boo(std::string{"String"}, true, 100);
```