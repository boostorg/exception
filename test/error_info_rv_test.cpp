//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/exception/get_error_info.hpp>
#include <boost/exception/info.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/detail/workaround.hpp>
#include <string.h>

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
int
main()
    {
	BOOST_FAIL("Platform does not support rvalue references.");
	return 1;
	}
#else
struct move_only;
typedef boost::error_info<struct tag_test1,move_only> test1;
struct
test_exception:
    boost::exception
    {
    };
struct
move_only
    {
    explicit move_only(int x) : x_(x) { }
    move_only( move_only && other ) : x_(other.x_) { }
    int x_;
    private:
    move_only( move_only const & );
    };
void
throw_test1()
    {
    throw test_exception() << test1(move_only(7));
    }
void
throw_test_throw_file_rv()
	{
	throw test_exception() << std::move(boost::throw_file("throw_file"));
	}
void
throw_test_throw_function_rv()
	{
	throw test_exception() << std::move(boost::throw_function("throw_function"));
	}
void
throw_test_throw_line_rv()
	{
	throw test_exception() << std::move(boost::throw_line(42));
	}
int
main()
    {
    try
        {
        throw_test1();
        BOOST_ASSERT(false);
        }
    catch(
    boost::exception & x )
        {
        BOOST_TEST(boost::get_error_info<test1>(x));
        BOOST_TEST(boost::get_error_info<test1>(x)->x_ == 7);
        }
    catch(
    ... )
        {
        BOOST_TEST(false);
        }
    try
        {
        throw_test_throw_function_rv();
        BOOST_ASSERT(false);
        }
    catch(
    boost::exception & x )
        {
        BOOST_TEST(boost::get_error_info<boost::throw_function>(x) && !strcmp(*boost::get_error_info<boost::throw_function>(x),"throw_function"));
        }
    catch(
    ... )
        {
        BOOST_TEST(false);
        }
    try
        {
        throw_test_throw_file_rv();
        BOOST_ASSERT(false);
        }
    catch(
    boost::exception & x )
        {
        BOOST_TEST(boost::get_error_info<boost::throw_file>(x) && !strcmp(*boost::get_error_info<boost::throw_file>(x),"throw_file"));
        }
    catch(
    ... )
        {
        BOOST_TEST(false);
        }
    try
        {
        throw_test_throw_line_rv();
        BOOST_ASSERT(false);
        }
    catch(
    boost::exception & x )
        {
        BOOST_TEST(boost::get_error_info<boost::throw_line>(x) && *boost::get_error_info<boost::throw_line>(x)==42);
        }
    catch(
    ... )
        {
        BOOST_TEST(false);
        }
    return boost::report_errors();
    }
#endif
