#ifndef MFE_COMMON_H_
#define MFE_COMMON_H_

#include <iostream>
#include <functional>

namespace mfe {
namespace common {

enum class IntegralType {
	MIDPOINT,
	TRAPEZOIDAL,
	SYMPSON
};


double integral(std::function<double (double)>,  
		double a, 
		double b,
		IntegralType type = IntegralType::MIDPOINT,
		int initialN = 4,
		double tol = 1e-6);

/**
 *  \brief Price an option based on the black-scholes formula.
 *  \param type the type of the option call/put 
 *  \param s0 the spot price of the underlying asset
 *  \param k the strike price of the option
 *  \param t the time to maturity in months
 *  \param sigma the volatility of the option in percentage
 *  \param r the risk free interest rate in percentage
 *  \param q the continuosly paid dividends
 *  
 *  \return the price of the option
 *
 *  E.g. A call option with strike 45 in 6 months with an underlying asset price of 50, risk free intereset rate of 6%, dividents 2% and volatility of 20% 
 *  price_option('c', 50.0, 45.0, 6, 20.0, 6.0, 2.0)
 *  
 */ 
double price_option(char type,
		    double s0,
		    double k,
		    double t,
		    double sigma,
		    double r,
		    double q);

}
}
#endif
