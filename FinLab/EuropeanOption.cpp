//EuropeanOption.cpp
	#include <iostream>;
#include <cstdlib>;
#include "EuropeanOption.hpp";
#include "Stat.hpp";
#include <math.h>;

using namespace Stat;

double EuropeanOption::getd1() const
{
	return (log(U/K) + (b + (sigma*sigma)*0.5) * T)/getTemp();
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
	return CallGamma();
}

double EuropeanOption::CallTheta() const
{
	double temp1=(-U*NormDist::pdf(getd1())*sigma*exp((b-r)*T))/(2*sqrt(T));
	double temp2=(r-b)*U*NormDist::cdf(getd1())*exp((b-r)*T)-r*K*exp(-r*T)*NormDist::cdf(getd2());
	return (temp1+temp2)/365;
}

double EuropeanOption::PutTheta() const
{

	double temp1=(-U*NormDist::pdf(getd1())*sigma*exp((b-r)*T))/(2*sqrt(T));
	double temp2=(b-r)*U*NormDist::cdf(-getd1())*exp((b-r)*T)+r*K*exp(-r*T)*NormDist::cdf(-getd2());
	return temp1+temp2;
}

double EuropeanOption::CallVega() const
{
	return U*exp((b-r)*T)*sqrt(T);
}

double EuropeanOption::PutVega() const
{
	return CallVega();
}

double EuropeanOption::CallRho() const
{
	return K*T*exp(-r*T)*NormDist::cdf(getd2());
}

double EuropeanOption::PutRho() const
{
	return -K*T*exp(-r*T)*NormDist::cdf(-getd2());
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
	std::cout<<"S="<< U <<"; K=" << K <<"; T=" << T <<std::endl<< "r=" << r <<"; sigma="<<sigma<<" ;carry="<<b<<std::endl;
}

double EuropeanOption::getProb() const
{
	double up = getUp();
	double down = 1/up;
	return (exp(b*getDelta_t())-down)/(up - down); //b is carrying cost

}

double EuropeanOption::getDelta_t() const
{
	return T/steps;
}

double EuropeanOption::getUp() const
{
	return exp(sigma*sqrt(getDelta_t()));
}

std::pair<double, bool> BarrierOption::StockEvolution(double up, double q) const
{
	double Ut=U;
	bool hitBarrier = false;
	for (int i = 0; i < steps; i++)
	{
		double random = (double) rand()/RAND_MAX;
		(random < q) ? (Ut *=up) : (Ut *= (1/up));
			//std::cout<< "stock price is: " << Ut <<std::endl;
			if (Ut > barrier)
			{
				hitBarrier=true; // stock evolved past barrier, payoff = rebate 
				break;
			}
	}
	return std::make_pair(Ut, hitBarrier);
}

/////////////// Barrier options:	
double BarrierOption::CallPrice() const
{
	double delta_t = getDelta_t();
	double up =  getUp();
	double p = getProb();
	double payoff = 0;
	if (barrierType==1)
	{
		for (int i = 0; i < iteration; i++)
		{ //Monte Carlo starts here

			std::pair<double, bool> outcome =StockEvolution(up, p);
			if (i % 1000 == 0) std::cout<<".";
		//	std::cout<<"stock price is "<<outcome.first<<"\t";
			if (outcome.second) // hit barrier, return rebate
			{
			//std::cout<<"rebate is" << rebate<<std::endl;
				payoff += rebate;
			}
			else
			{
				double po = outcome.first-K;
				(po<0) ? (po=0) : (po);
		//		std::cout<<"outcome is "<<po<<std::endl;
				payoff += po; // Call: St- K
			}
		}
	/*std::cout<<std::endl;
	std::cout<<up<<std::endl;
	std::cout<<delta_t<<std::endl;
	std::cout<<p<<std::endl;*/

	return payoff/iteration;
	}
	else
		return 0;
}


double BarrierOption::CallDelta() const
{
	BarrierOption option1;
	BarrierOption option2;
	double delta = 0.01;
	option2.U = option1.U*(1 + delta);

	return (option2.CallPrice()-option1.CallPrice())/(option1.U*delta);
}





void BarrierOption::init()
{// Default values, default type = C
	r = 0.05;
	sigma=0.20;
	K = 100;
	T = 1.0;
	U = 120;
	b = 0.03;

	optType = "C";

	barrier = 150;
	rebate = 0;
	barrierType =1;
	
}

BarrierOption::BarrierOption()
{//Set default, type = Call, barrierType = Up Out (1)
	init();
}



