#ifndef QIANGWU_PARAMETER_DETAIL_ARGUMENT_SINK_HPP_
#define QIANGWU_PARAMETER_DETAIL_ARGUMENT_SINK_HPP_

#include <utility>
#include <parameter/detail/argument.hpp>
#include <parameter/detail/default_argument.hpp>

namespace parameter {
    namespace detail {
        template <class Tag>
        struct Keyword {
            template <class ArgT>
            auto operator=(ArgT&& arg) const
            {
                return Argument<Tag, ArgT>{std::forward<ArgT>(arg)};
            }

            template <class ArgT>
            auto operator|(ArgT&& def_value) const
            {
                return Default_argument<Tag, ArgT>{std::forward<ArgT>(def_value)};
            }
        };
    }  // of namespace detail
}  // of namespace parameter

#endif  //!QIANGWU_PARAMETER_DETAIL_ARGUMENT_SINK_HPP_