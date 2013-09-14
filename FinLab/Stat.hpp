namespace Stat
{
	class NormDist
	{
		private:
			static double Dist(double x,double mean,double stDev, bool cumulative);
			static double Dist(double x, bool cumulative); //standard normal
		public:
			static double pdf(double x,double mean,double stDev);
			static double pdf(double x);
			static double cdf(double x,double mean,double stDev);
			static double cdf(double x);
	};
  
}
