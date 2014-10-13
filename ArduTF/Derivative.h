#ifndef Derivative_h
#define Derivative_h
#define LIBRARY_VERSION	1.0

class DIFF
{	
		public:
		DIFF(double*,double,uint32_t);  //constructor: the three parameters are the output variable, the filtering constant N: DIFF(s)=s/(1+s/N) and the loop time in micros
		void Compute(double);  //calculates the numerical derivative of input
		bool AutoCompute(double); //calculates the numerical derivative of input automatically considering the respect of the loop time
		
		private:
		double *_Output;
		double _Diff,_kf,_kd,_u_old;
		uint32_t _T;
		uint32_t _lastTime;
};
#endif