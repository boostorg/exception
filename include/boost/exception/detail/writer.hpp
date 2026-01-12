//Copyright (c) 2006-2026 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_DETAIL_WRITER_HPP_INCLUDED
#define BOOST_EXCEPTION_DETAIL_WRITER_HPP_INCLUDED

#include <boost/exception/detail/type_info.hpp>
#include <type_traits>
#include <utility>

namespace
boost
    {
    template <class Tag, class T> class error_info;

    namespace
    exception_serialization
        {
        struct writer_adl {};
        }

    namespace
    exception_detail
        {
        template <class T>
        struct first_arg;

        template <class C, class R, class A1, class... A>
        struct
        first_arg<R(C::*)(A1, A...)>
            {
            using type = A1;
            };

        template <class C, class R, class A1, class... A>
        struct
        first_arg<R(C::*)(A1, A...) const>
            {
            using type = A1;
            };

        class
        writer:
            exception_serialization::writer_adl
            {
            writer(writer const &) = delete;
            writer & operator=(writer const &) = delete;

            core::typeinfo const * type_;
            void * w_;

            bool
            dispatch_()
                {
                return false;
                }

            template <class F1, class... Fn>
            bool
            dispatch_(F1 && f1, Fn && ... fn)
                {
                using writer_type = typename std::decay<typename first_arg<decltype(&std::decay<F1>::type::operator())>::type>::type;
                if (writer_type * w = get<writer_type>())
                    {
                    std::forward<F1>(f1)(*w);
                    return true;
                    }
                return dispatch_(std::forward<Fn>(fn)...);
                }

            protected:

            template <class Writer>
            explicit
            writer(Writer * w) noexcept:
                type_(&BOOST_CORE_TYPEID(Writer)),
                w_(w)
                {
                }

            public:

            template <class Writer>
            Writer *
            get() noexcept
                {
                return *type_ == BOOST_CORE_TYPEID(Writer) ? static_cast<Writer *>(w_) : nullptr;
                }

            template <class... Fn>
            bool
            dispatch(Fn && ... fn)
                {
                return dispatch_(std::forward<Fn>(fn)...);
                }
            };

        template <class Writer>
        struct
        writer_adaptor:
            writer
            {
            explicit
            writer_adaptor(Writer & w) noexcept:
                writer(&w)
                {
                }
            };
        }
    }

#endif
