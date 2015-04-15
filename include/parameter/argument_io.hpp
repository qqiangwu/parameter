#ifndef QIANGWU_PARAMETER_ARGUMENT_IO_HPP_
#define QIANGWU_PARAMETER_ARGUMENT_IO_HPP_

#include <parameter/detail/argument.hpp>
#include <parameter/detail/default_argument.hpp>

namespace parameter {
    namespace detail {
        template <class CharT, class Traits, class Tag, class ArgT>
        inline decltype(auto)
        operator<<(std::basic_ostream<CharT, Traits>& out, Argument<Tag, ArgT>& arg)
        {
            return out << arg.arg;
        }

        template <class CharT, class Traits, class Tag, class ArgT>
        inline decltype(auto)
        operator<<(std::basic_ostream<CharT, Traits>& out, Default_argument<Tag, ArgT>& arg)
        {
            return out << arg.arg;
        }
    }  // of namespace detail
}  // of namespace parameter

#endif  //!QIANGWU_PARAMETER_ARGUMENT_IO_HPP_