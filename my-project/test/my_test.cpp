#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>
#include "api.h"

BOOST_AUTO_TEST_CASE( test_case1 )
{
    print_example();
    BOOST_CHECK( true );
}

BOOST_AUTO_TEST_CASE( test_case2 )
{
    BOOST_CHECK( false );
}

