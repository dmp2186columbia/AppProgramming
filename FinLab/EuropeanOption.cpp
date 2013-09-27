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
	return (temp1+temp2)/tradingdays;
}

double EuropeanOption::PutTheta() const
{

	double temp1=(-U*NormDist::pdf(getd1())*sigma*exp((b-r)*T))/(2*sqrt(T));
	double temp2=(b-r)*U*NormDist::cdf(-getd1())*exp((b-r)*T)+r*K*exp(-r*T)*NormDist::cdf(-getd2());
	return (temp1+temp2)/tradingdays;
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
	b = 0.03;

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
/*double BarrierOption::CallPrice() const
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
*/
double BarrierOption::CallPrice() const
{
	double A, B, C, D, E, F, dA, dB, dC, dD, dE, dF;
	double sigrt = (sigma*sqrt(T));
	double mu = (b - sigma*sigma*0.5)/(sigma*sigma);
	double lambda = sqrt(mu*mu + 2.0 * r /(sigma*sigma));
	double x1 = log(U/K)/sigrt + (1 + mu)*sigrt;
	double x2 = log(U/barrier)/sigrt + (1 + mu)*sigrt;
	double y1 = log(barrier*barrier/(U*K))/sigrt + (1+mu)*sigrt;
	double y2 = log(barrier/U)/sigrt + (1+mu)*sigrt;
	double z = log(barrier/U)/sigrt + lambda*sigrt;

	int phi, eta;
	if (barrierType==1) // for other barrier type, change phi and eta.
	{
		phi =1;
		eta =-1;
	}
	else
	{
		phi=0;
		eta=0;
	}

	A = phi*U*exp((b-r)*T)*NormDist::cdf(phi*x1) - phi*K*exp(-r*T)*NormDist::cdf(phi*x1-phi*sigrt);
	B = phi*U*exp((b-r)*T)*NormDist::cdf(phi*x2) - phi*K*exp(-r*T)*NormDist::cdf(phi*x2-phi*sigrt);
	C = phi*U*exp((b-r)*T)*pow(barrier/U,2.*(1.+mu))*NormDist::cdf(eta*y1)
		- 
		phi*K*exp(-r*T)*pow(barrier/U,2.*mu)*NormDist::cdf(eta*y1-eta*sigrt);
	D = phi*U*exp((b-r)*T)*pow(barrier/U,2.*(1.+mu))*NormDist::cdf(eta*y2)
		- 
		phi*K*exp(-r*T)*pow(barrier/U,2.*mu)*NormDist::cdf(eta*y2-eta*sigrt);
	E = rebate*exp(-r*T)*(NormDist::cdf(eta*x2-eta*sigrt)-pow(barrier/U, 2.*mu)*NormDist::cdf(eta*y2-eta*sigrt));
	F = rebate*(pow(barrier/U,mu+lambda)*NormDist::cdf(eta*z)+pow(barrier/U,mu-lambda)*NormDist::cdf(eta*z-2.*eta*lambda*sigrt));

	
	if (K >= barrier)
	{
		return rebate;
	}
	else
	{
		return A -B +C -D +F;
	}
}

double BarrierOption::CallDelta() const
{
	double dA, dB, dC, dD, dE, dF;
	double sigrt = (sigma*sqrt(T));
	double mu = (b - sigma*sigma*0.5)/(sigma*sigma);
	double lambda = sqrt(mu*mu + 2.0 * r /(sigma*sigma));
	double x1 = log(U/K)/sigrt + (1 + mu)*sigrt;
	double x2 = log(U/barrier)/sigrt + (1 + mu)*sigrt;
	double y1 = log(barrier*barrier/(U*K))/sigrt + (1+mu)*sigrt;
	double y2 = log(barrier/U)/sigrt + (1+mu)*sigrt;
	double z = log(barrier/U)/sigrt + lambda*sigrt;

	int phi, eta;
	if (barrierType==1) // for other barrier type, change phi and eta.
	{
		phi =1;
		eta =-1;
	}
	else
	{
		phi=0;
		eta=0;
	}

	dA = phi*exp((b-r)*T)*NormDist::cdf(phi*x1);
	dB = phi*exp((b-r)*T)*NormDist::cdf(phi*x2) + exp((b-r)*T)*(NormDist::pdf(x2)/sigrt)*(1.-K/barrier);
	dC = -phi*2.*mu*pow(barrier/U,2.*mu)*(1./U)*(U*exp((b-r)*T)*(barrier/U)*(barrier/U)	*NormDist::cdf(eta*y1)
          - K *exp(-r*T)*NormDist::cdf(eta*y1-eta*sigma*sqrt(T)))-  phi*pow(barrier/U,2.*mu+2.)*exp((b-r)*T)*NormDist::cdf(eta*y1); 
	dD = -2.*mu*(phi/U)*pow(barrier/U,2.*mu)*(U*exp((b-r)*T)*(barrier/U)*(barrier/U)*NormDist::cdf(eta*y2)
		- K*exp(-r*T)*NormDist::cdf(eta*(y2-sigma*sqrt(T))))
		-  phi*pow(barrier/U,2.*mu+2.)*exp((b-r)*T)*NormDist::cdf(eta*y2)-phi*eta*exp((b-r)*T)*pow(barrier/U,2.*mu+2.)*NormDist::pdf(y2)/(sigma*sqrt(T))*(1.-K/barrier); 
	dE = 2.*(rebate/U)*exp(-r*T)*pow(barrier/U,2.*mu)*(NormDist::cdf(eta*(y2-sigma*sqrt(T)))*mu+eta*NormDist::pdf(y2-sigma*sqrt(T))/(sigma*sqrt(T))); 
	dF = -pow(barrier/U,mu+lambda)*(rebate/U)*((mu+lambda)*NormDist::cdf(eta*z)+(mu-lambda)*pow(barrier/U,2.*lambda)*NormDist::cdf(eta*(z-2.*lambda*sigma*sqrt(T))))
		- 2.*eta*rebate*pow(barrier/U,mu+lambda)*NormDist::pdf(z)/(U*sigma*sqrt(T)); 


	if (K>=barrier)
	{
		return dF;
	}
	else
	{
		return dA - dB + dC - dD + dF;
	}
}

void BarrierOption::print() const
{
	std::cout<<"S="<< U <<";\t K=" << K <<";\t T=" << T <<std::endl<< "r=" << r <<";\t sigma="<<sigma<<" ;\t carry="<<b<<std::endl;
	std::cout<<"barrier="<<barrier<<";\t rebate="<<rebate<<";\t barrierType ="<<barrierType<<std::endl;
}

void BarrierOption::init()
{// Default values, default type = C
	r = 0.05;
	sigma=0.15;
	K = 100;
	T = 2.0;
	U = 100;
	b = 0.03;

	optType = "C";

	barrier = 110;
	rebate = 0;
	barrierType =1;
	
}

BarrierOption::BarrierOption()
{//Set default, type = Call, barrierType = Up Out (1)
	init();
}



