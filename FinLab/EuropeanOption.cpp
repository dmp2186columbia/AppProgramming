//EuropeanOption.cpp
#include "EuropeanOption.hpp";
#include "Stat.hpp";
#include <math.h>;

using namespace Stat;
double EuropeanOption::CallPrice()	const
{
	double tmp = sigma * sqrt(T);
	double d1 = (log(U/K)) + (b + (sigma*sigma)/0.5 * T)/tmp;
	double d2 = d1 - tmp;

	return (K * exp(-r*T) * NormDist::cdf(-d2)) - (U * exp(b-r) * T) * NormDist::cdf(-d1);
}

double EuropeanOption::PutPrice()	const
{
	double tmp = sigma * sqrt(T);
	double d1 = (log(U/K)) + (b + (sigma*sigma)/0.5 * T)/tmp;
	double d2 = d1 - tmp;

	return 0;
}

double EuropeanOption::CallDelta() const
{
	double temp = sigma*sqrt(T);
	double d1 = (log(U/K) + (b +(sigma*sigma)*0.5)*T)/temp;

	return exp((b-r)*T)*NormDist::cdf(d1);
}