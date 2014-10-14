#ifndef Filter_h
#define Filter_h
#define LIBRARY_VERSION	1.0

class FILT
{	
		public:
		FILT(double*,double,double,double,double,double,double,uint32_t);  //constructor: the parameters are Output variable,n1,n2,n3,d1,d2,d3,T (sampling time in milliseconds) FILT(s)=(n1*s^2+n2*s+n3)/(d1*s^2+d2*s+d3)
		void Compute(double);  //calculates the numerical integral of input
		bool AutoCompute(double); //calculates the numerical integral of input automatically considering the respect of the loop time
		void SetStartingValue(double); //sets the starting value of the filter
		
		private:
		double *_Output;
		double _Filt,_f_old,_f_old_2,_u_old,_u_old_2;		//store the input and output values
		double _d2,_d3,_n1,_n2,_n3;		//store the coefficients of the discrete filter
		uint32_t _T;
		uint32_t _lastTime;
};
#endif
