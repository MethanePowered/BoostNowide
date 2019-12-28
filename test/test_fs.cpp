//
//  Copyright (c) 2015 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <boost/nowide/cstdio.hpp>
#include <boost/nowide/fstream.hpp>
#include <boost/nowide/integration/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>
#include <iostream>

#include "test.hpp"

int main()
{
    try
    {
        boost::nowide::nowide_filesystem();
        const std::string prefix = boost::filesystem::unique_path("nowide-%%%%-%%%%-").string();
        const std::string utf8_name =
          prefix + "\xf0\x9d\x92\x9e-\xD0\xBF\xD1\x80\xD0\xB8\xD0\xB2\xD0\xB5\xD1\x82-\xE3\x82\x84\xE3\x81\x82.txt";

        boost::nowide::ofstream f(utf8_name.c_str());
        TEST(f);
        f << "Test" << std::endl;
        f.close();

        TEST(boost::filesystem::is_regular_file(boost::nowide::widen(utf8_name)));
        TEST(boost::filesystem::is_regular_file(utf8_name));

        boost::nowide::remove(utf8_name.c_str());

        TEST(!boost::filesystem::is_regular_file(boost::nowide::widen(utf8_name)));
        TEST(!boost::filesystem::is_regular_file(utf8_name));
    } catch(std::exception const &e)
    {
        std::cerr << "Failed : " << e.what() << std::endl;
        BOOST_NOWIDE_TEST_RETURN_FAILURE;
    }

    return boost::report_errors();
}

///
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
