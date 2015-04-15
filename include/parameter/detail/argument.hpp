#ifndef QIANGWU_PARAMETER_DETAIL_ARGUMENT_HPP_
#define QIANGWU_PARAMETER_DETAIL_ARGUMENT_HPP_

namespace parameter {
    namespace detail {
        template<class Tag, class ArgT>
        struct Argument {
            using tag_type = Tag;

            ArgT arg;

            explicit Argument(ArgT&& a)
                : arg(std::forward<ArgT>(a))
            {}

            operator const ArgT&() const
            {
                return arg;
            }
        };
    }  // of namespace detail
}  // of namespace parameter

#endif  //!QIANGWU_PARAMETER_DETAIL_ARGUMENT_HPP_