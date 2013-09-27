#include "Stat.hpp";
#include "EuropeanOption.hpp";
#include <iostream>;
#include <math.h>;
#include <fstream>;
#include <string>;
#define EVER ;; 

void pressEnterToContinue()
{
	std::cin.sync();
	std::cout << std::endl << "Press Enter to continue..." << std::endl;
	std::cin.get();
}

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
	EuropeanOption callOption;
	EuropeanOption putOption;
	putOption.optType="P";
	std::cout<<"Initial values:"<<std::endl;
	callOption.print();
	//(a)
	std::cout<<"K in range [80,120] step 2:"<<std::endl<<std::endl;
	double tempK = 80;
	while (tempK<120.01)
	{
		std::cout<<"K = "<<tempK<<std::endl;
		callOption.K=tempK;
		putOption.K=tempK;
		std::cout<<"\tCall Price="<<callOption.Price();
		std::cout<<";\tPut Price="<<putOption.Price()<<";"<<std::endl;
		std::cout<<"\tCall Delta="<<callOption.Delta();
		std::cout<<";\tPut Delta="<<putOption.Delta()<<";"<<std::endl;
		std::cout<<"\tCall Gamma="<<callOption.Gamma();
		std::cout<<";\tPut Gamma="<<putOption.Gamma()<<";"<<std::endl;
		std::cout<<"\tCall Theta="<<callOption.Theta();
		std::cout<<";\tPut Theta="<<putOption.Theta()<<";"<<std::endl;
		std::cout<<"\tCall Vega="<<callOption.Vega();
		std::cout<<";\tPut Vega="<<putOption.Vega()<<";"<<std::endl;
		std::cout<<"\tCall Rho="<<callOption.Rho();
		std::cout<<";\tPut Rho="<<putOption.Rho()<<";"<<std::endl;
	
		tempK = tempK + 2;
	}
	callOption.K=100;
	putOption.K=100;
	pressEnterToContinue();
	//(b)
	std::cout<<"T in range [0.2,5] step 0.2:"<<std::endl;
	double tempT= 0.2;
	while (tempT<5.01)
	{
		std::cout<<"T = "<<tempT<<std::endl;
		callOption.T=tempT;
		putOption.T=tempT;
		std::cout<<"\tCall Price="<<callOption.Price();
		std::cout<<";\tPut Price="<<putOption.Price()<<";"<<std::endl;
		std::cout<<"\tCall Delta="<<callOption.Delta();
		std::cout<<";\tPut Delta="<<putOption.Delta()<<";"<<std::endl;
		std::cout<<"\tCall Gamma="<<callOption.Gamma();
		std::cout<<";\tPut Gamma="<<putOption.Gamma()<<";"<<std::endl;
		std::cout<<"\tCall Theta="<<callOption.Theta();
		std::cout<<";\tPut Theta="<<putOption.Theta()<<";"<<std::endl;
		std::cout<<"\tCall Vega="<<callOption.Vega();
		std::cout<<";\tPut Vega="<<putOption.Vega()<<";"<<std::endl;
		std::cout<<"\tCall Rho="<<callOption.Rho();
		std::cout<<";\tPut Rho="<<putOption.Rho()<<";"<<std::endl;
	
		
		tempT = tempT + 0.2;
	}
	callOption.T=1;
	putOption.T=1;
	pressEnterToContinue();
	
	//(c)
	std::cout<<"r in range [0, 0.2] step 0.01:"<<std::endl;
	double tempr= 0;
	while (tempr<0.2001)
	{
		std::cout<<"r = "<<tempr<<std::endl;
		callOption.r=tempr;
		putOption.r=tempr;
		std::cout<<"\tCall Price="<<callOption.Price();
		std::cout<<";\tPut Price="<<putOption.Price()<<";"<<std::endl;
		std::cout<<"\tCall Delta="<<callOption.Delta();
		std::cout<<";\tPut Delta="<<putOption.Delta()<<";"<<std::endl;
		std::cout<<"\tCall Gamma="<<callOption.Gamma();
		std::cout<<";\tPut Gamma="<<putOption.Gamma()<<";"<<std::endl;
		std::cout<<"\tCall Theta="<<callOption.Theta();
		std::cout<<";\tPut Theta="<<putOption.Theta()<<";"<<std::endl;
		std::cout<<"\tCall Vega="<<callOption.Vega();
		std::cout<<";\tPut Vega="<<putOption.Vega()<<";"<<std::endl;
		std::cout<<"\tCall Rho="<<callOption.Rho();
		std::cout<<";\tPut Rho="<<putOption.Rho()<<";"<<std::endl;
	
		tempr = tempr + 0.01;
	}
	callOption.r=0.05;
	putOption.r=0.05;

	pressEnterToContinue();
	std::cout<<"sigma in range [0.02, 0.5] step 0.02:"<<std::endl;
	double tempsigma= 0.02;
	while (tempsigma<0.5001)
	{
		std::cout<<"sigma = "<<tempsigma<<std::endl;
		callOption.sigma=tempsigma;
		putOption.sigma=tempsigma;
		std::cout<<"\tCall Price="<<callOption.Price();
		std::cout<<";\tPut Price="<<putOption.Price()<<";"<<std::endl;
		std::cout<<"\tCall Delta="<<callOption.Delta();
		std::cout<<";\tPut Delta="<<putOption.Delta()<<";"<<std::endl;
		std::cout<<"\tCall Gamma="<<callOption.Gamma();
		std::cout<<";\tPut Gamma="<<putOption.Gamma()<<";"<<std::endl;
		std::cout<<"\tCall Theta="<<callOption.Theta();
		std::cout<<";\tPut Theta="<<putOption.Theta()<<";"<<std::endl;
		std::cout<<"\tCall Vega="<<callOption.Vega();
		std::cout<<";\tPut Vega="<<putOption.Vega()<<";"<<std::endl;
		std::cout<<"\tCall Rho="<<callOption.Rho();
		std::cout<<";\tPut Rho="<<putOption.Rho()<<";"<<std::endl;
	
		tempsigma= tempsigma + 0.02;
	}
	callOption.sigma=0.2;
	putOption.sigma=0.2;

}

bool exercise3_a(void)
{
    EuropeanOption option;
	double temp;
    std::cout << "Enter Spot Price:" << std::endl;
	if (!(std::cin >> temp) || temp < 0.0)
	{
		std::cout << "Input not valid" << std::endl;
		return false;
	}
	option.U = temp;

    std::cout << "Enter Strike Price:" << std::endl;
	if (!(std::cin >> temp) || temp < 0.0)
	{
		std::cout << "Input not valid" << std::endl;
		return false;
	}
    option.K = temp;

    std::cout << "Enter Discount Rate:" << std::endl;
	if (!(std::cin >> temp) || temp > 1.0 || temp < 0.0)
	{
		std::cout << "Input not valid" << std::endl;
		return false;
	}
    option.r = temp;
    

    double temp1, temp2;
    std::cout << "Enter Loan Rate:" << std::endl;
	if (!(std::cin >> temp1) || temp1 > 1.0 || temp1 < 0.0)
	{
		std::cout << "Input not valid" << std::endl;
		return false;
	}
    std::cout << "Enter Dividend Yield:" << std::endl;
    if (!(std::cin >> temp2) || temp2 > 1.0 || temp2 < 0.0)
	{
		std::cout << "Input not valid" << std::endl;
		return false;
	}
    option.b = temp1 - temp2;

    std::cout << "Enter Expiration:" << std::endl;
	if (!(std::cin >> temp) || temp < 0.0)
	{
		std::cout << "Input not valid" << std::endl;
		return false;
	}
    option.T = temp;
    

    std::cout << "Enter Volatility:" << std::endl;
	if (!(std::cin >> temp))
	{
		std::cout << "Input not valid" << std::endl;
		return false;
	}
    option.sigma = temp;

	// printout
	std::cout<<"Your input:"<<std::endl;
	option.print();
	std::cout<<std::endl;
	std::cout << "Price is " << option.Price() << std::endl;
    std::cout << "Delta is " << option.Delta() << std::endl;
    std::cout << "Gamma is " << option.Gamma() << std::endl;
    std::cout << "Theta is " << option.Theta() << std::endl;
    std::cout << "Vega is " << option.Vega() << std::endl;
    std::cout << "Rho is " << option.Rho() << std::endl;
	return true;
}

void exercise3_b(void)
{
    std::ifstream file("a.txt");
    std::string str;

    EuropeanOption option;

    std::getline(file, str);
	option.U = atof(str.c_str());

	std::getline(file, str);
    option.K = atof(str.c_str());

	std::getline(file, str);
    option.r = atof(str.c_str());
    
	std::getline(file, str);
    double temp1 = atof(str.c_str());

	std::getline(file, str);
    double temp2 = atof(str.c_str());
    option.b = temp1 - temp2;

	std::getline(file, str);
    option.T = atof(str.c_str());

	std::getline(file, str);
    option.sigma = atof(str.c_str());
	
	std::cout<<"Data from text:"<<std::endl;
	option.print();
	std::cout<<std::endl;
	std::cout << "Price is " << option.Price() << std::endl;
    std::cout << "Delta is " << option.Delta() << std::endl;
    std::cout << "Gamma is " << option.Gamma() << std::endl;
    std::cout << "Theta is " << option.Theta() << std::endl;
    std::cout << "Vega is " << option.Vega() << std::endl;
    std::cout << "Rho is " << option.Rho() << std::endl;
}

void exercise3(void)
{
	char select;
	std::cout<< "Exercise 3, select (a) or (b)" << std::endl<<"Your selection:";
	std::cin>> select;
	if (select == 'a')
	{
		for (EVER)
		{
			bool finish = exercise3_a();
			if (finish==true) break;
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
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

void exercise4(void)
{
	std::cout<<"Exercise 4"<<std::endl;
	BarrierOption option;
	
	option.print();

	std::cout<<"Option price=" << option.Price()<<std::endl;
	std::cout<<"Delta = "<<option.Delta()<<std::endl<<std::endl;

	option.K = 105.0;
	option.barrier=90.0;
	option.rebate = 10.0;
	option.T =3.0;
	option.print();	
	std::cout<<"Option price=" << option.Price()<<std::endl;
	std::cout<<"Delta = "<<option.Delta()<<std::endl;
	
	
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

int main () 
{
	
	for (EVER)
	{
		std::cout<<"====================================================="<<std::endl;
		std::cout<<"====== FINLAB OPTION PRICING PROGRAM VER 0.0.0 ======"<<std::endl;
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
		case 'q' : break;	
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
		std::cout<<std::endl;
	}
	return 0;
}




