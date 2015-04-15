#ifndef QIANGWU_PARAMETER_ARGUMENT_PACK_HPP_
#define QIANGWU_PARAMETER_ARGUMENT_PACK_HPP_

#include <tuple>
#include <utility>
#include <type_traits>

#include <parameter/detail/keyword.hpp>

namespace parameter {
    namespace detail {
        template <class PackItem, class Tag>
        struct Is_match {
            static constexpr auto value = false;
        };

        template <class Tag, class ArgT>
        struct Is_match<Argument<Tag, ArgT>, Tag> {
            static constexpr auto value = true;
        };

        template <std::size_t I, class Tag, class... Args>
        struct Find_elem_imp;

        template <std::size_t I, class Tag, class Head, class... Tail>
        struct Find_elem_imp<I, Tag, Head, Tail...> {
            using t1 = std::remove_reference_t<Head>;
            using t2 = std::remove_cv_t<Head>;

            enum { value = Is_match<t2, Tag>::value? I: Find_elem_imp<I + 1, Tag, Tail...>::value };
        };

        template <std::size_t I, class Tag>
        struct Find_elem_imp<I, Tag> {
            enum { value = I };
        };

        template <class Tag, class... Args>
        struct Find_elem {
            enum { value = Find_elem_imp<0, Tag, Args...>::value };
        };
    }

    template <class T> struct show;

    template <class... Args>
    struct Argument_pack {
    public:
        Argument_pack(Args&&... args)
            : pack_(std::make_tuple(std::forward<Args>(args)...))
        {}

        template <class Tag>
        decltype(auto) operator[](const detail::Keyword<Tag>& keyword)
        {
            constexpr auto pos = detail::Find_elem<Tag, Args...>::value;

            static_assert(pos != argument_size, "Cannot find the keyword");

            return std::get<pos>(pack_);
        }

        template <class Tag, class ArgT>
        decltype(auto) operator[](const detail::Default_argument<Tag, ArgT>& def)
        {
            constexpr std::size_t I = detail::Find_elem<Tag, Args...>::value;

            using Retriever = std::conditional_t<
                        I == argument_size,
                        Default_retriever,
                        Pack_retriever<I>>;

            return Retriever::get(pack_, def);
        }

        static constexpr auto argument_size = sizeof...(Args);

    private:
        struct Default_retriever {
            template <class Tuple, class DefaultArg>
            static decltype(auto) get(Tuple& t, DefaultArg& def)
            {
                return def.value;
            }
        };

        template <std::size_t I>
        struct Pack_retriever {
            template <class Tuple, class DefaultArg>
            static decltype(auto) get(Tuple& t, DefaultArg& def)
            {
                return std::get<I>(t);
            }
        };

        std::tuple<Args...> pack_;
    };

    template <class... Args>
    inline auto pack_args(Args&&... args)
    {
        return Argument_pack<Args...>(std::forward<Args>(args)...);
    }
}

#endif  //!QIANGWU_PARAMETER_ARGUMENT_PACK_HPP_