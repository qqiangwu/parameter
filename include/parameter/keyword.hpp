#ifndef QIANGWU_PARAMETER_KEYWORD_HPP_
#define QIANGWU_PARAMETER_KEYWORD_HPP_

#include <parameter/detail/keyword.hpp>

#define PARAMETER_KEYWORD_FULL(namespace_, tag)\
    namespace namespace_ {\
        struct tag;\
    }\
    constexpr auto tag##_ = ::parameter::detail::Keyword<namespace_::tag>{}

#define PARAMETER_KEYWORD(tag)  PARAMETER_KEYWORD_FULL(keyword, tag)

#endif  //!QIANGWU_PARAMETER_KEYWORD_HPP_