#ifndef QIANGWU_PARAMETER_KEYWORD_HPP_
#define QIANGWU_PARAMETER_KEYWORD_HPP_

#include <parameter/detail/keyword.hpp>

#define PARAMETER_KEYWORD(tag)\
    constexpr auto tag##_ = ::parameter::detail::Keyword<struct tag>{}

#endif  //!QIANGWU_PARAMETER_KEYWORD_HPP_