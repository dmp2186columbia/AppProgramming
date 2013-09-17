#include "Stat.hpp";
#include "EuropeanOption.hpp";
#include <iostream>;
#include <math.h>;


void exercise1(void)
{
	std::cout<<"Exercise 1"<<std::endl;
	double x = -5.0;
	while (x<=5.0001)
	{
		std::cout << "f(" << x << ")=" << Stat::NormDist::pdf(x);
		std::cout<<"\t | F("<< x << ")=" <<Stat::NormDist::cdf(x) <<std::endl;
		x = x + 0.2;
	}
}

void exercise2(void)
{
	std::cout<<"Exercise 2"<<std::endl;
	EuropeanOption option;
	std::cout<<"Initial values:"<<std::endl;
	option.print();
	//(a)
	std::cout<<"K in range [80,120] step 2:"<<std::endl;
	double tempK = 80;
	while (tempK<120.01)
	{
		std::cout<<"K = "<<tempK;
		option.K=tempK;
		std::cout<<";\tCall Price="<<option.Price();
		option.toggle();
		std::cout<<";\tPut Price="<<option.Price()<<std::endl;
		tempK = tempK + 2;
	}
	option.K=100;
	
	//(b)
	std::cout<<"T in range [0.2,5] step 0.2:"<<std::endl;
	double tempT= 0.2;
	while (tempT<5.01)
	{
		std::cout<<"T = "<<tempT;
		option.T=tempT;
		std::cout<<";\tCall Price="<<option.Price();
		option.toggle();
		std::cout<<";\tPut Price="<<option.Price()<<std::endl;
		tempT = tempT + 0.2;
	}
	option.T=1;
		
	//(c)
	std::cout<<"r in range [0, 0.2] step 0.01:"<<std::endl;
	double tempr= 0;
	while (tempr<0.2001)
	{
		std::cout<<"r = "<<tempr;
		option.r=tempr;
		std::cout<<";\tCall Price="<<option.Price();
		option.toggle();
		std::cout<<";\tPut Price="<<option.Price()<<std::endl;
		tempr = tempr + 0.01;
	}
	option.r=0.05;
}

void exercise3(void)
{
	std::cout<<"Exercise 3";
}

void exercise4(void)
{
	std::cout<<"Exercise 4";
}
int main () 
{
	/*int select;
	std::cout << "Select an exercise to run (1-4):\n";
	std::cin >> select;
	switch (select)
	{
	case 1 : exercise1();
		break;
	case 2 : exercise2();
		break;
	case 3 : exercise3();
		break;
	case 4 : exercise4();
		break;
	default : std::cout<< "some error happened";
		break;
	}*/
	exercise2();
	return 0;
	
}





