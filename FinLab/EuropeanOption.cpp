//EuropeanOption.cpp
#include <iostream>;
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

	return 0; //Not Correct!!
}

double EuropeanOption::CallDelta() const
{
	double temp = sigma*sqrt(T);
	double d1 = (log(U/K) + (b +(sigma*sigma)*0.5)*T)/temp;

	return exp((b-r)*T)*NormDist::cdf(d1);
}


double EuropeanOption::PutDelta() const
{
	double temp = sigma*sqrt(T);
	double d1 = (log(U/K) + (b +(sigma*sigma)*0.5)*T)/temp;

	return exp((b-r)*T)*NormDist::cdf(d1);//Not correct!!
}

double EuropeanOption::CallGamma() const
{
	return 0;
}

double EuropeanOption::PutGamma() const
{
	return 0;
}

double EuropeanOption::CallTheta() const
{
	return 0;
}

double EuropeanOption::PutTheta() const
{
	return 0;
}

double EuropeanOption::CallVega() const
{
	return 0;
}

double EuropeanOption::PutVega() const
{
	return 0;
}

double EuropeanOption::CallRho() const
{
	return 0;
}

double EuropeanOption::PutRho() const
{
	return 0;
}

void EuropeanOption::init()
{// Default values, default type = C
	r = 0.05;
	sigma=0.2;
	K = 100;
	T = 1;
	U = 100;
	b = -0.02;

	optType = "C";
}

void EuropeanOption::copy(const EuropeanOption& o2)
{
	r= o2.r;
	sigma = o2.sigma;
	K = o2.K;
	T = o2.T;
	U = o2.U;
	b = o2.b;

	optType = o2.optType;
}

EuropeanOption::EuropeanOption()
{//Set default, type = Call
	init();
}

EuropeanOption::EuropeanOption(const EuropeanOption& o2)
{//Copy constructor
	copy(o2);
}

EuropeanOption::EuropeanOption(const string& optTp)
{
	init();
	optType = optTp;
}

EuropeanOption::~EuropeanOption()
{
	//delete object
}

EuropeanOption& EuropeanOption::operator= (const EuropeanOption& o2)
{
	if (this == &o2) return *this;
	copy(o2);
	return * this;
}
/// public functions start here
double EuropeanOption::Price() const
{
	if (optType=="C") 
		return CallPrice();
	else
		return PutPrice();
}

double EuropeanOption::Delta() const
{
	if (optType=="C")
		return CallDelta();
	else if (optType=="P")
		return PutDelta();
}

double EuropeanOption::Gamma() const
{
	if (optType=="C")
		return CallGamma();
	else
		return PutGamma();
}

double EuropeanOption::Theta() const
{
	if (optType=="C")
		return CallTheta();
	else
		return PutTheta();
}

double EuropeanOption::Rho() const
{
	if (optType=="C")
		return CallRho();
	else
		return PutRho();
}

void EuropeanOption::toggle()
{
	if (optType=="C")
		optType == "P";
	else
		optType == "C";
}

void EuropeanOption::print()
{
	std::cout<<"S="<< U <<"; K=" << K <<"; T=" << T <<std::endl<< "r=" << r <<"; sigma="<<sigma<<" ;div="<<b<<std::endl;
}