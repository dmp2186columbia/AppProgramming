// EuropeanOption.hpp
#include <string>;
using std::string;
class EuropeanOption
{
private:
	
	virtual void init(); // default values
	void copy(const EuropeanOption	&opt2);
	
	double	virtual CallPrice() const;
	double	virtual PutPrice() const;
	double	virtual CallDelta() const;
	double	virtual PutDelta() const;
	double	virtual CallGamma() const;
	double	virtual PutGamma() const;
	double  virtual CallTheta() const;
	double  virtual PutTheta() const;
	double  virtual CallVega() const;
	double  virtual PutVega() const;
	double  virtual CallRho() const;
	double  virtual PutRho() const;

protected:
	double getProb() const;
	double getDelta_t() const;
	double getUp() const	;
	double getd1() const;
	double getd2() const;
	double getTemp() const;

public:
	static const int iteration = 10000;
	static const int steps = 100;

	double r; //discount rate
	double sigma; //vol
	double K; //strike
	double T; //Expiry
	double U; // Underlying price
	double b; // carrying cost = loan rate - dividend rate
	
	string optType;

	EuropeanOption();
	EuropeanOption(const EuropeanOption &opt2);
	EuropeanOption(const string &optType);

	virtual ~EuropeanOption();

	EuropeanOption& operator = (const EuropeanOption& opt2);

	double Price() const;
	double Delta() const;
	double Gamma() const;
	double Theta() const;
	double Vega()  const;
	double Rho()   const;

	void toggle();
	void print() const;
};

class BarrierOption : public EuropeanOption
{
private:
	void init();
	std::pair<double, bool> StockEvolution(double up, double q) const;
	
	double virtual CallPrice() const;
	double virtual CallDelta() const;
	/*double virtual PutPrice() const;
	double virtual CallDelta() const;
	double virtual PutDelta() const;
	double virtual CallGamma() const;
	double virtual PutGamma() const;
	double virtual CallTheta() const;
	double virtual PutTheta() const;
	double virtual CallVega() const;
	double virtual PutVega() const;
	double virtual CallRho() const;
	double virtual PutRho() const;*/

public:
	BarrierOption();
	double barrier;
	double rebate;

	short barrierType; //1: up-and-out 2: down-and-out

};