#include <iostream>
#include <cmath>
#include <cctype>

#include "mfe_common.h"

namespace mfe {
namespace common {	
// Cumulative distribution of z with an error smaller 
// than 7.5e-7 at any point on the real axis.
// Implementation of the algorithm presented
// in Primer for the mathematics of financial engineering page 103.
// 
double cum_dist_normal(double x) 
{
	double z = std::abs(x);
	double y = 1 / (1 + 0.2316419 * z);
	double a1 = 0.319381530;
	double a2 = -0.356563782;
	double a3 = 1.781477937;
	double a4 = -1.821255978;
	double a5 = 1.330274429;
	double result = 1 - exp(-(x * x) / 2)*(a1 * y + a2 * pow(y, 2.0) +  a3 * pow(y, 3.0) + a4 * pow(y, 4.0) + a5 * pow(y, 5.0)) / sqrt(2 * M_PI);
	return x > 0 ? result : (1 - result);	
}

double interval(double a, double b, int n) {
	return (b - a) / n;
}

double midpoint_step(std::function<double (double)> f,
		     double a, 
		     double b, 
		     int n) {
	auto h = interval(a, b, n);
	double result = 0.0;
	for (int i = 0; i < n; i++) {
        	result += f(a + h/2.0 + i * h); 	
	}
	return result * h;
}

double trapezoidal_step(std::function<double (double)> f,
			double a,
			double b,
			int n) {
	auto h = interval(a, b, n);
	double result = (f(a) + f(b)) / 2;
	for(int i = 1; i < n - 1; i++) {
		result += f(a + h * i);
	}
	return result * h;
}

double sympson_step(std::function<double (double)> f,
		double a,
		double b,
		int n) {
	auto h = interval(a, b, n);
	double result = f(a) + f(b);
	for(int i = 1; i < n - 1; i ++) {
		result += f(a + h * i) * 2;
	}
	for(int i = 0; i < n; i ++) {
		result += f(a + h / 2 + h * i) * 4;
	}
	return result * h / 6.0;
}

using integral_step = double (*) (std::function<double (double)>, double, double, int);

double integral(integral_step step, 
		std::function<double (double)> f,
		double a,
		double b,
		int n,
		double tol
		) {
	auto result1 = step(f, a, b, n);
	n *= 2;
	auto result2 = step(f, a, b, n);
	while( std::abs(result2 - result1) > tol) {
		result1 = result2;
		n *= 2;
		result2 = step(f, a, b, n);
	}
	return result2;
}

double integral(std::function<double (double)> f,  
		double a, 
		double b,
		IntegralType type,
		int initialN,
		double tol) {
	switch(type)
	{
		case IntegralType::MIDPOINT:
			return integral(midpoint_step, f, a, b, initialN, tol);
		case IntegralType::TRAPEZOIDAL: 
			return integral(trapezoidal_step, f, a, b, initialN, tol);
		case IntegralType::SYMPSON: 
			return integral(sympson_step, f, a, b, initialN, tol);
	}
	return 0.0;
}

double calculate_d1(double s0,
	  double k,
	  double t,
	  double sigma,
	  double r,
	  double q) 
{
	return (log(s0 / k) + (r - q + sigma * sigma / 2) * t) / (sigma * sqrt(t));
}


double calculate_d2(double s0,
	  double k,
	  double t,
	  double sigma,
	  double r,
	  double q) 
{
	return (log(s0 / k) + (r - q - sigma * sigma / 2) * t) / (sigma * sqrt(t));
}


double price_option(char type,
		    double s0,
		    double k,
		    double t,
		    double sigma,
		    double r,
		    double q)
{

	auto d1 = calculate_d1(s0, k, t, sigma, r, q);
	auto d2 = calculate_d2(s0, k, t, sigma, r, q); 

	if(type == 'c') {
		return s0 * exp(-q * t) * cum_dist_normal(d1) - k * exp(-r * t) * cum_dist_normal(d2);	
	}
	else if (type == 'p') {
	        return - s0 * exp(-q * t) * cum_dist_normal(-d1) + k * exp(-r * t) * cum_dist_normal(-d2);
	}	
	else {
		///@todo throw an exception here
		return -1.0;
	}
}

} // End namesapce common
} // End namespace mfe
