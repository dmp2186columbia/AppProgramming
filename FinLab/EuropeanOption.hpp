
// EuropeanOption.hpp
#include <string>;
using std::string;
class EuropeanOption
{

private:
	void init(); // default values
	void copy(const EuropeanOption	&opt2);
	
	double	CallPrice() const;
	double	PutPrice() const;
	double	CallDelta() const;
	double	PutDelta() const;
	double	CallGamma() const;
	double	PutGamma() const;
	

public:
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

	void toggle();
};