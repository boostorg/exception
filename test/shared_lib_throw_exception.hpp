//Copyright (c) 2006-2019 Emil Dotchevski and Reverge Studios, Inc.
//Copyright (c) 2019-2019 David Callu

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_884f590590084f34be8437f87b774691
#define UUID_884f590590084f34be8437f87b774691

#include <boost/exception/error_info.hpp>
#include <boost/exception/exception.hpp>

#include <string>

namespace
boost
    {
    namespace
    exception_test
        {
	struct my_exception: virtual boost::exception {};
	typedef boost::error_info<struct error_info_string_, std::string> error_info_string;

	void throw_my_exception_with_error_info_string( const std::string message );
        }
    }

#endif
