/*-----------------------------------------------------------------------------------/
  Arduino Filtered Derivative Library
  by Andrea Vivani <tellicious@icloud.com> 
  This Library is licensed under GPLv3 License
/-----------------------------------------------------------------------------------*/

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <Derivative.h>


//----------------------------------Constructor----------------------------------//
DIFF::DIFF(double* Output,double N,uint32_t T){
	_Output=Output;
	_T=T;
	double T_sec=(double) T/1e3;
	_kf=(2-N*T_sec)/(2+N*T_sec);
	_kd=2*N/(2+N*T_sec);
	//set to 0 all the support variables
	_u_old=0;
	_Diff=0;
	_lastTime=millis();
}



/*--------------------------------Calculate Output-------------------------------//
This function should be called inside a If statement that checks if the time 
elapsed since the last step is greater or equal than the step time
 //---------------------------------------------------------------------------------*/
 void DIFF::Compute(double u)
{
	_Diff=_kf*_Diff+_kd*(u-_u_old);
	_u_old=u;
    	*_Output=_Diff;
}

/*-----------------------------AutoCalculate Output----------------------------//
This function can be called inside the loop() environment without the need for
a loop-time check. It should be called as the condition of an if statement so that
if it returns false, the program will stop, otherwise it can continue
 //---------------------------------------------------------------------------------*/
bool DIFF::AutoCompute(double u)
{
	uint32_t now = millis();
   if((now-_lastTime)>=_T){
   		_lastTime=now;
		DIFF::Compute(u);
    	if ((millis()-_lastTime)>=_T){
    		*_Output=0;
    		return false;
    	}
    	else{return true;}
    }
    else if ((now-_lastTime)<0){ _lastTime=0L;}
}
