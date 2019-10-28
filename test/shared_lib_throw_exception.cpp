//Copyright (c) 2006-2019 Emil Dotchevski and Reverge Studios, Inc.
//Copyright (c) 2019-2019 David Callu

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "shared_lib_throw_exception.hpp"

#include <boost/exception/info.hpp>

namespace
boost
    {
    namespace
    exception_test
        {
	void throw_my_exception_with_error_info_string( const std::string message )
	    {
	    throw my_exception() << error_info_string( message );
	    }
        }
    }
