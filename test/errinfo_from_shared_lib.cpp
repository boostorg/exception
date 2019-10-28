//Copyright (c) 2006-2019 Emil Dotchevski and Reverge Studios, Inc.
//Copyright (c) 2019-2019 David Callu

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "shared_lib_throw_exception.hpp"

#include <boost/exception/get_error_info.hpp>
#include <boost/core/lightweight_test.hpp>

int
main()
    {
    try
        {
	boost::exception_test::throw_my_exception_with_error_info_string("doh");
        }
    catch( boost::exception & e )
        {
        BOOST_TEST(boost::get_error_info<boost::exception_test::error_info_string>(e) &&
		   !strcmp(boost::get_error_info<boost::exception_test::error_info_string>(e)->c_str(),"doh"));
        }
    return boost::report_errors();
    }
