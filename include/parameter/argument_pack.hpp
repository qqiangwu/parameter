#ifndef QIANGWU_PARAMETER_ARGUMENT_PACK_HPP_
#define QIANGWU_PARAMETER_ARGUMENT_PACK_HPP_

#include <tuple>
#include <utility>
#include <type_traits>

#include <parameter/detail/keyword.hpp>

namespace parameter {
    namespace detail {
        template <class T>
        using remove_cvr_t = std::remove_cv_t<std::remove_reference_t<T>>;

        template <class PackItem, class Tag>
        struct Is_match {
            static constexpr auto value = false;
        };

        template <class Tag, class ArgT>
        struct Is_match<Argument<Tag, ArgT>, Tag> {
            static constexpr auto value = true;
        };

        template <class PackItem, class TargetT>
        struct Is_same {
            static constexpr auto value = std::is_same<remove_cvr_t<PackItem>, remove_cvr_t<TargetT>>::value;
        };

        template <class TargetT, class Tag, class ArgT>
        struct Is_same<Argument<Tag, ArgT>, TargetT> {
            static constexpr auto value = std::is_same<remove_cvr_t<ArgT>, remove_cvr_t<TargetT>>::value;
        };

        template <template <class, class> class Pred, std::size_t I, class TargetT, class... Args>
        struct Find_elem_imp;

        template <template <class, class> class Pred, std::size_t I, class TargetT, class Head, class... Tail>
        struct Find_elem_imp<Pred, I, TargetT, Head, Tail...> {
            using t1 = std::remove_reference_t<Head>;
            using t2 = std::remove_cv_t<t1>;

            enum { value = Pred<t2, TargetT>::value? I: Find_elem_imp<Pred, I + 1, TargetT, Tail...>::value };
        };

        template <template <class, class> class Pred, std::size_t I, class TargetT>
        struct Find_elem_imp<Pred, I, TargetT> {
            enum { value = I };
        };

        template <template <class, class> class Pred, class TargetT, class... Args>
        struct Find_elem {
            enum { value = Find_elem_imp<Pred, 0, TargetT, Args...>::value };
        };
    }

    template <class T> struct show;

    template <class... Args>
    struct Argument_pack {
    public:
        static constexpr auto argument_size = sizeof...(Args);
        
        explicit Argument_pack(Args&&... args)
            : pack_(std::forward_as_tuple(std::forward<Args>(args)...))
        {}

        template <class Tag>
        decltype(auto) operator[](const detail::Keyword<Tag>& keyword)
        {
            constexpr auto pos = detail::Find_elem<detail::Is_match, Tag, Args...>::value;

            static_assert(pos != argument_size, "Cannot find the keyword");

            return std::get<pos>(pack_);
        }

        template <class Tag, class ArgT>
        decltype(auto) operator[](const detail::Default_argument<Tag, ArgT>& def)
        {
            constexpr std::size_t I = detail::Find_elem<detail::Is_match, Tag, Args...>::value;

            using Retriever = std::conditional_t<
                        I == argument_size,
                        Default_retriever,
                        Pack_retriever<I>>;

            return Retriever::get(pack_, def.value);
        }

        template <std::size_t I>
        decltype(auto) get()
        {
            return std::get<I>(pack_);
        }

        template <class ArgT>
        decltype(auto) get()
        {
            constexpr std::size_t I = detail::Find_elem<detail::Is_same, ArgT, Args...>::value;

            static_assert(I != argument_size, "Cannot find argument of the type");

            return std::get<I>(pack_);
        }

        template <class ArgT>
        decltype(auto) get(ArgT&& default_value)
        {
            constexpr std::size_t I = detail::Find_elem<detail::Is_same, ArgT, Args...>::value;

            using Retriever = std::conditional_t<
                    I == argument_size,
                    Default_retriever,
                    Pack_retriever<I>>;

            return Retriever::get(pack_, default_value);
        }
        
        auto size() const noexcept
        {
            return argument_size;
        }

    private:
        struct Default_retriever {
            template <class Tuple, class DefaultArg>
            static decltype(auto) get(Tuple& t, DefaultArg& def)
            {
                return def;
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

    template <class TargetT, class... Args>
    inline decltype(auto) get(Argument_pack<Args...>& pack)
    {
        return pack.template get<TargetT>();
    }

    template <class TargetT, class... Args>
    inline decltype(auto) get(Argument_pack<Args...>& pack, TargetT&& val)
    {
        return pack.get(val);
    }

    template <std::size_t I, class... Args>
    inline decltype(auto) get(Argument_pack<Args...>& pack)
    {
        return pack.template get<I>();
    }
}  // of namespace parameter

#define PARAMETER_ENABLE_CONSTRUCTOR(class_name)\
    template <class... Args>\
    class_name(Args&&... args) \
        : class_name(parameter::pack_args(std::forward<Args>(args)...))\
    {}

#endif  //!QIANGWU_PARAMETER_ARGUMENT_PACK_HPP_