//EuropeanOption.cpp
#include <iostream>;
#include <cstdlib>;
#include "EuropeanOption.hpp";
#include "Stat.hpp";
#include <math.h>;

using namespace Stat;


double EuropeanOption::getd1() const
{
	return (log(U/K) + (b + (sigma*sigma)/0.5) * T)/getTemp();
}

double EuropeanOption::getd2() const
{
	return getd1()-getTemp();
}

double EuropeanOption::getTemp() const
{
	return sigma * sqrt(T);
}

double EuropeanOption::CallPrice() const
{
	return U * exp((b-r)*T) * NormDist::cdf(getd1()) - (K * exp(-r*T) * NormDist::cdf(getd2())); //changed
}

double EuropeanOption::PutPrice() const
{
	return (K * exp(-r*T) * NormDist::cdf(-getd2())) - U  * exp((b-r)*T) * NormDist::cdf(-getd1()); // corrected	
}

double EuropeanOption::CallDelta() const
{
	return exp((b-r)*T) * NormDist::cdf(getd1());
}

double EuropeanOption::PutDelta() const
{
	return -exp((b-r)*T)*NormDist::cdf(-getd1());//changed
}

double EuropeanOption::CallGamma() const
{
	return NormDist::pdf(getd1())*exp((b-r)*T)/(U * getTemp());
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

	double temp = sigma*sqrt(T);
	double d1 = (log(U/K) + (b +(sigma*sigma)*0.5)*T)/temp;
	double q = getProb();

	return exp(-q*T)*U*sqrt(T)*NormDist::cdf(d1);
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

double EuropeanOption::Vega() const
{
	if (optType=="C")
		return CallVega();
	else
		return PutVega();
}


void EuropeanOption::toggle()
{
	if (optType=="C")
		optType == "P";
	else
		optType == "C";
}

void EuropeanOption::print() const
{
	std::cout<<"S="<< U <<"; K=" << K <<"; T=" << T <<std::endl<< "r=" << r <<"; sigma="<<sigma<<" ;div="<<b<<std::endl;
}

double EuropeanOption::getProb() const
{
	double up = getUp();
	double down = 1/up;
	return (exp((r-b)*getDelta_t())-down)/(up - down); //b is carrying cost

}

double EuropeanOption::getDelta_t() const
{
	return T/steps;
}

double EuropeanOption::getUp() const
{
	return exp(sigma*sqrt(getDelta_t()));
}

/////////////// Barrier options:	
double BarrierOption::CallPrice() const
{
	double delta_t = getDelta_t();
	double Ut;
	double up = getUp();
	double down = 1/up;
	double q = getProb();

	double payoff = 0;
	if (barrierType==1)
	{
	//	std::cout << "starting price computation";

		for (int i = 0; i < iteration; i++)
		{
			Ut = U; // start a new simulation. Reset underlying price.
			for (int j = 0; j < steps; j++)
			{
				double random = (double) rand()/RAND_MAX;
				(random < q) ? (Ut *=up) : (Ut *= down);
				if (Ut > barrier)
				{
					payoff += rebate;
					break;
				}
				
			}
			if ((Ut > K) && (Ut <= barrier ))
			{
				payoff += (Ut - K);
				std::cout<< "current payoff = " <<(Ut-K) << std::endl;
				std::cout << "Ut is"<<Ut << " and total payoff is " << payoff <<std::endl;
			}
		}

		return payoff/iteration;

	}
	else
		return 0;
}


void BarrierOption::init()
{// Default values, default type = C
	r = 0.05;
	sigma=0.2;
	K = 120;
	T = 1;
	U = 100;
	b = -0.02;

	optType = "C";

	barrier = 150;
	rebate = 10;
	barrierType =1;
	
}

BarrierOption::BarrierOption()
{//Set default, type = Call
	init();
}
