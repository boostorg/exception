//Copyright (c) 2006-2010 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_CE6983AC753411DDA764247956D89593
#define UUID_CE6983AC753411DDA764247956D89593

#include <boost/config.hpp>
#include <utility>
#include <string>

#if (__GNUC__*100+__GNUC_MINOR__>301) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma GCC system_header
#endif
#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(push,1)
#endif

namespace
boost
    {
    namespace
    exception_detail
        {
        class
        error_info_base
            {
            public:

            virtual std::string name_value_string() const = 0;

            protected:

            virtual
            ~error_info_base() throw()
                {
                }
            };
        }

    template <class Tag,class T>
    class
    error_info:
        public exception_detail::error_info_base
        {
        public:
        typedef T value_type;
        error_info( value_type const & v ):
            v_(v)
            {
            }
#if (__GNUC__*100+__GNUC_MINOR__!=406) //workaround for g++ bug
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
        error_info( error_info const & x ):
            v_(x.v_)
            {
            }
        error_info( value_type && v ) BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(value_type(std::move(v)))):
            v_(std::move(v))
            {
            }
        error_info( error_info && x ) BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(value_type(std::move(x.v_)))):
            v_(std::move(x.v_))
            {
            }
#endif
#endif
        ~error_info() throw()
            {
            }
        value_type const &
        value() const
            {
            return v_;
            }
        value_type &
        value()
            {
            return v_;
            }
        private:
        error_info & operator=( error_info const & );
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
        error_info & operator=( error_info && x );
#endif
        std::string name_value_string() const;
        value_type v_;
        };
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif
