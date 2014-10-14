#ifndef Integrator_h
#define Integrator_h
#define LIBRARY_VERSION	1.0

class INT
{	
		public:
		INT(double*,uint32_t);  //constructor: the two parameters are the output variable and the loop time in milliseconds
		void Compute(double);  //calculates the numerical integral of input
		bool AutoCompute(double); //calculates the numerical integral of input automatically considering the respect of the loop time
		void SetStartingValue(double); //sets the starting value of the integrator
		
		private:
		double *_Output;
		double _Int,_ki,_u_old;
		uint32_t _T;
		uint32_t _lastTime;
};
#endif
