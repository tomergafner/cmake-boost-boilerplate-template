#define BOOST_TEST_MODULE Test_Mfe_Common
#include <boost/test/included/unit_test.hpp>
#include "mfe_common.h"

BOOST_AUTO_TEST_CASE( test_midpoint_integral )
{
    auto result = mfe::common::integral([] (double x) {return x* x;}, 0, 2);
    BOOST_CHECK_CLOSE(result, (8.0 / 3.0), 1e-4);
}


BOOST_AUTO_TEST_CASE( test_trapezoidal_integral )
{
    auto result = mfe::common::integral([] (double x) {return x* x;}, 0, 2, 
		    			mfe::common::IntegralType::TRAPEZOIDAL);
    BOOST_CHECK_CLOSE(result, (8.0 / 3.0), 1e-4);
}


BOOST_AUTO_TEST_CASE( test_sympson_integral )
{
    auto result = mfe::common::integral([] (double x) {return x* x;}, 0, 2, 
		    			mfe::common::IntegralType::SYMPSON);
    BOOST_CHECK_CLOSE(result, (8.0 / 3.0), 1e-4);
}
