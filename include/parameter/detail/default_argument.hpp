#ifndef QIANGWU_PARAMETER_DETAIL_DEFAULT_ARGUMENT_HPP_
#define QIANGWU_PARAMETER_DETAIL_DEFAULT_ARGUMENT_HPP_


namespace parameter {
    namespace detail {
        template<class Tag, class ArgT>
        struct Default_argument {
            using tag_type = Tag;

            ArgT value;

            explicit Default_argument(ArgT&& a)
                : value(std::forward<ArgT>(a))
            {}

            operator const ArgT&() const
            {
                return value;
            }
        };
    }  // of namespace detail
}  // of namespace parameter


#endif //QIANGWU_PARAMETER_DETAIL_DEFAULT_ARGUMENT_HPP_
