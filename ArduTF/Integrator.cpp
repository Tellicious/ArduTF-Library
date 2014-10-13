/*-----------------------------------------------------------------------------------/
  Arduino Integrator Library
  by Andrea Vivani <andrea.vivani@gmail.com> 
  This Library is licensed under GPLv3 License
/-----------------------------------------------------------------------------------*/

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <Integrator.h>


//----------------------------------Constructor----------------------------------//
INT::INT(double* Output,uint32_t T){
	_Output=Output;
	_T=T;
	double T_sec=(double) T/1e6;
	_ki=0.5*T_sec;
	//set to 0 all the support variables
	_u_old=0;
	_Int=0;
}



/*--------------------------------Calculate Output-------------------------------//
This function should be called inside a If statement that checks if the time 
elapsed since the last step is greater or equal than the step time
 //---------------------------------------------------------------------------------*/
 void INT::Compute(double u)
{
	_Int+=_ki*(u+_u_old);
	_u_old=u;
    *_Output=_Int;
}

/*-----------------------------AutoCalculate Output----------------------------//
This function can be called inside the loop() environment without the need for
a loop-time check. It should be called as the condition of an if statement so that
if it returns false, the program will stop, otherwise it can continue
 //---------------------------------------------------------------------------------*/
bool INT::AutoCompute(double u)
{
	uint32_t now = micros();
   if((now-_lastTime)>=_T){
   		_lastTime=now;
		INT::Compute(u);
    	if ((micros()-_lastTime)>=_T){
    		*_Output=0;
    		return false;
    	}
    	else{return true;}
    }
    else if ((now-_lastTime)<0){ _lastTime=0L;}
}

/*-----------------------------Set starting value----------------------------//
This function should be called BEFORE the first computation if it is 
required to have a starting value different from zero
 //---------------------------------------------------------------------------------*/
void INT::SetStartingValue(double start)
{
	_Int=start;
	return;
}