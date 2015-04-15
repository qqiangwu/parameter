# parameter
A simple C++14 named parameter library

[![Build Status](https://travis-ci.org/qqiangwu/parameter.svg)](https://travis-ci.org/qqiangwu/parameter)

[![Build status](https://ci.appveyor.com/api/projects/status/72808phwx80gnbjm/branch/master?svg=true)](https://ci.appveyor.com/project/qqiangwu/parameter/branch/master)

[![Build Status](https://webapi.biicode.com/v1/badges/qiangwu/qiangwu/parameter/master)](https://www.biicode.com/qiangwu/parameter) 

# Example
```
#include <parameter/keyword.hpp>
#include <parameter/argument_pack.hpp>

PARAMETER_KEYWORD(size);
PARAMETER_KEYWORD(position);
PARAMETER_KEYWORD(flag);
PARAMETER_KEYWORD(visible);

class Window {
public:
    template <class... Args>
    Window(Args&&... args)
        : Window(parameter::pack_args(std::forward<Args>(args)...))
    {}
    
private:
    template <class... Args>
    Window(parameter::Argument_pack<Args...> args)
        : m_size(args[size_]), 
          m_pos(args[pos_]),
          m_flag(args[flag_]), 
          m_visible(args[visible_ | false])
    {}
};

int main()
{
    Window win{size_=Size{480, 300}, pos_=Point{0, 0}, flag_=0};
}
```