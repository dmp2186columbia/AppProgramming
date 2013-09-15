#define _USE_MATH_DEFINES
#include "Stat.hpp"
#include <math.h>;
namespace Stat
{
	double NormDist::Dist(double x, bool cumulative)
	{//Standard normal
		if (cumulative)
		{
			if (x<-6)
			{
				return 0;
			}
			else if (x>6)
			{
				return 1;
			}
			else
			{
				if (x>=0)
				{//
					double k = 1/(1+ 0.2316419*x);
					double a1 = 0.319381530;
					double a2 = -0.356563782;
					double a3 = 1.781477937;
					double a4 = -1.821255978;
					double a5 = 1.330274429;
					return 1 - NormDist::Dist(x,false) * (a1*k+a2*pow(k,2) + a3*pow(k,3) + a4*pow(k,4) + a5*pow(k,5));
				}
				else
				{
					return 1- NormDist::Dist(-x,true);
				}
			}
		}
		else
		{
			return (1/(sqrt(2*M_PI))) * exp(-x*x/2);
		}
	}
	double NormDist::Dist(double x,double mean,double stDev, bool cumulative)
	{
		if (cumulative)
		{
			return NormDist::Dist((x-mean)/stDev,true);
		}
		else
		{
			return (1/(stDev*sqrt(2*M_PI))) * exp(-(pow(x-mean,2))/(2*stDev*stDev));
		}
	}


	double NormDist::pdf(double x)
	{
		return Dist(x,false);	
	}

	double NormDist::cdf(double x)
	{
		return Dist(x,true);	
	}	

	double NormDist::pdf(double x,double mean,double stDev)
	{
		return Dist(x,mean,stDev, false);	
	}

	double NormDist::cdf(double x,double mean,double stDev)
	{
		return Dist(x,mean,stDev, true);	
	}
}
