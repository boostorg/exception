//Copyright (c) 2006-2026 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined( BOOST_NO_EXCEPTIONS )
#   error This program requires exception handling.
#endif

#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/serialization/nlohmann_writer.hpp>
#include <boost/throw_exception.hpp>

#include "nlohmann/json.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <iomanip>
#include <iostream>
#include <exception>

using output_writer = boost::exception_serialization::nlohmann_writer<nlohmann::ordered_json>;

namespace boost { namespace exception_serialization {

template <class Handle, class E>
void
serialize(Handle & h, E const & e, char const * name)
    {
    h.dispatch(
        [&](nlohmann_writer<nlohmann::json> & w) { write_nested(w, e, name); },
        [&](nlohmann_writer<nlohmann::ordered_json> & w) { write_nested(w, e, name); }
    );
    }

} }

struct my_error_tag1;
struct my_error_tag2;

typedef boost::error_info<my_error_tag1, int> my_error1;
typedef boost::error_info<my_error_tag2, std::string> my_error2;

struct
my_info
    {
    int code;
    char const * message;

    template <class Json>
    friend
    void
    to_json(Json & j, my_info const & e)
        {
        j["code"] = e.code;
        j["message"] = e.message;
        }
    };

struct my_info_tag;
typedef boost::error_info<my_info_tag, my_info> my_error3;

struct
test_exception:
    virtual boost::exception,
    virtual std::exception
    {
    char const *
    what() const noexcept override
        {
        return "test_exception::what";
        }
    };

void
check_output(nlohmann::ordered_json const & j, bool has_source_location)
    {
    if( has_source_location )
        {
        BOOST_TEST(j.contains("throw_file"));
        BOOST_TEST(j.contains("throw_line"));
        BOOST_TEST(j.contains("throw_function"));
        }
#ifndef BOOST_NO_RTTI
    BOOST_TEST(j.contains("dynamic_exception_type"));
#endif
    BOOST_TEST(j.contains("std::exception::what"));
    BOOST_TEST_EQ(j["std::exception::what"].get<std::string>(), "test_exception::what");

    BOOST_TEST(j.contains("my_error_tag1"));
    BOOST_TEST_EQ(j["my_error_tag1"].get<int>(), 42);

    BOOST_TEST(j.contains("my_error_tag2"));
    BOOST_TEST_EQ(j["my_error_tag2"].get<std::string>(), "hello");

    BOOST_TEST(j.contains("my_info_tag"));
    auto const & mij = j["my_info_tag"];
    BOOST_TEST_EQ(mij["code"].get<int>(), 1);
    BOOST_TEST_EQ(mij["message"].get<std::string>(), "error one");
    }

int
main()
    {
        {
        std::cout << "Testing write_diagnostic_information_to:\n";
        nlohmann::ordered_json j;
        try
            {
            test_exception e;
            e <<
                my_error1(42) <<
                my_error2("hello") <<
                my_error3({1, "error one"});
            BOOST_THROW_EXCEPTION(e);
            }
        catch( test_exception & e )
            {
            output_writer w{j};
            boost::write_diagnostic_information_to(e, w);
            }
        std::cout << std::setw(2) << j << std::endl;
        check_output(j, true);
        }

        {
        std::cout << "\nTesting write_current_exception_diagnostic_information_to:\n";
        nlohmann::ordered_json j;
        try
            {
            test_exception e;
            e <<
                my_error1(42) <<
                my_error2("hello") <<
                my_error3({1, "error one"});
            BOOST_THROW_EXCEPTION(e);
            }
        catch( ... )
            {
            output_writer w{j};
            boost::write_current_exception_diagnostic_information_to(w);
            }
        std::cout << std::setw(2) << j << std::endl;
        check_output(j, true);
        }

    return boost::report_errors();
    }
