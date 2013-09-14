#define _USE_MATH_DEFINES
#include "Stat.hpp"
#include <math.h>;
namespace Stat
{
	double const precision = 0.0000001;	//actual precision only up to 10e-6
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
			{//very crude estimation, dumb & slow
				double tempx =-6;
				double temp  = 0;
				while (tempx<x)
				{
					temp =  temp + precision*((1/sqrt(2*M_PI))*(exp(-tempx*tempx/2)));
					tempx = tempx + precision;
				}
				return temp;
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
