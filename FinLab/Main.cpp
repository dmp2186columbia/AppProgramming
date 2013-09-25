#include "Stat.hpp";
#include "EuropeanOption.hpp";
#include <iostream>;
#include <math.h>;
#include <fstream>;
#include <string>;
#define EVER ;; 


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


void exercise3_a(void)
{
    EuropeanOption option;
	double temp;
    std::cout << "Enter Spot Price:" << std::endl;
	if (!(std::cin >> temp) || temp < 0.0)
	{
		std::cout << "Input not valid" << std::endl;
		return;
	}
	option.U = temp;

    std::cout << "Enter Strike Price:" << std::endl;
	if (!(std::cin >> temp) || temp < 0.0)
	{
		std::cout << "Input not valid" << std::endl;
		return;
	}
    option.K = temp;

    std::cout << "Enter Discount Rate:" << std::endl;
	if (!(std::cin >> temp) || temp > 1.0 || temp < 0.0)
	{
		std::cout << "Input not valid" << std::endl;
		return;
	}
    option.r = temp;
    

    double temp1, temp2;
    std::cout << "Enter Loan Rate:" << std::endl;
	if (!(std::cin >> temp1) || temp1 > 1.0 || temp1 < 0.0)
	{
		std::cout << "Input not valid" << std::endl;
		return;
	}
    std::cout << "Enter Dividend Yield:" << std::endl;
    if (!(std::cin >> temp2) || temp2 > 1.0 || temp2 < 0.0)
	{
		std::cout << "Input not valid" << std::endl;
		return;
	}
    option.r = temp;
    option.b = temp1 - temp2;

    std::cout << "Enter Expiration:" << std::endl;
	if (!(std::cin >> temp) || temp < 0.0)
	{
		std::cout << "Input not valid" << std::endl;
		return;
	}
    option.T = temp;
    

    std::cout << "Enter Volatility:" << std::endl;
	if (!(std::cin >> temp))
	{
		std::cout << "Input not valid" << std::endl;
		return;
	}
    option.sigma = temp;

    std::cout << "Price is " << option.Price() << std::endl;
    std::cout << "Delta is " << option.Delta() << std::endl;
    std::cout << "Gamma is " << option.Gamma() << std::endl;
    std::cout << "Theta is " << option.Theta() << std::endl;
    std::cout << "Vega is " << option.Vega() << std::endl;
    std::cout << "Rho is " << option.Rho() << std::endl;

}


void exercise3_b(void)
{
    std::ifstream file("a.txt");
    std::string str;

    EuropeanOption option;

    std::cout << "Spot Price:" << std::endl;
    std::getline(file, str);
	option.U = atof(str.c_str());
	
    std::cout << "Strike Price:" << std::endl;
	std::getline(file, str);
    option.K = atof(str.c_str());

    std::cout << "Enter Discount Rate:" << std::endl;
	std::getline(file, str);
    option.r = atof(str.c_str());
    
    std::cout << "Enter Loan Rate:" << std::endl;
	std::getline(file, str);
    double temp1 = atof(str.c_str());

	std::cout << "Enter Dividend Yield:" << std::endl;
	std::getline(file, str);
    double temp2 = atof(str.c_str());
    option.b = temp1 - temp2;

    std::cout << "Enter Expiration:" << std::endl;
	std::getline(file, str);
    option.T = atof(str.c_str());

    std::cout << "Enter Volatility:" << std::endl;
	std::getline(file, str);
    option.sigma = atof(str.c_str());

   std::cout << "Price is " << option.Price() << std::endl;
    std::cout << "Delta is " << option.Delta() << std::endl;
    std::cout << "Gamma is " << option.Gamma() << std::endl;
    std::cout << "Theta is " << option.Theta() << std::endl;
    std::cout << "Vega is " << option.Vega() << std::endl;
    std::cout << "Rho is " << option.Rho() << std::endl;
	
}


void exercise4(void)
{
	std::cout<<"Exercise 4"<<std::endl;
	BarrierOption option;
	option.barrier = 125;
	option.barrierType=1;
	option.rebate = 10;

	double price = option.Price();
	std::cout<< price;
}

char menu(void)
{
	std::cout<<"====================================================="<<std::endl;
	std::cout<<"(1) Run exercise 1"<<std::endl;
	std::cout<<"(2) Run exercise 2"<<std::endl;
	std::cout<<"(3) Run exercise 3"<<std::endl;
	std::cout<<"(4) Run exercise 4"<<std::endl;
	std::cout<<"(q) Quit"<<std::endl;
	std::cout<<"Your selection: ";
	char temp;
	std::cin>>temp;
	std::cout<<std::endl;
	return temp;
}

void exercise3(void)
{
	char select;
	std::cout<< "Exercise 3, select (a) or (b)" << std::endl;
	std::cin>> select;
	if (select == 'a')
	{
		exercise3_a();
		return;
	}
	else if (select == 'b')
	{
		exercise3_b();
		return;
	}
	else
	{
		std::cout << "Invalid Command" << std::endl;
		return;
	}
}

int main () 
{
	std::cout<<"====================================================="<<std::endl;
	std::cout<<"====== FINLAB OPTION PRICING PROGRAM VER 0.0.0 ======"<<std::endl;
	for (EVER)
	{
		char selection = menu();
		switch (selection)
		{
		case '1': exercise1();
			break;
		case '2': exercise2();
			break;
		case '3': exercise3();
			break;
		case '4': exercise4();
			break;
		default : std::cout<<"Command not recognized."<<std::endl;
			break;
		}
		if (selection=='q')
		{
			std::cout<<"Quiting programm..."<<std::endl;
			break;
		}
		std::cin.clear();
		std::cin.ignore(100, '\n');
	}
	return 0;
}




