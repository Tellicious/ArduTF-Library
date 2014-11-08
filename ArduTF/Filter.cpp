/*-----------------------------------------------------------------------------------/
  Arduino Filter Library
  by Andrea Vivani <tellicious@icloud.com> 
  This Library is licensed under GPLv3 License
/-----------------------------------------------------------------------------------*/

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <Filter.h>


//----------------------------------Constructor----------------------------------//
FILT::FILT(double* Output,double n1,double n2,double n3,double d1,double d2,double d3,uint32_t T) {
	_Output=Output;
	_T=T;
	double T_sec=(double) T/1e3;
	double den=d3*T_sec*T_sec + 2*d2*T_sec+ 4*d1;
	_d2=-(2*d3*T_sec*T_sec - 8*d1)/den;
	_d3=-(d3*T_sec*T_sec - 2*d2*T_sec + 4*d1)/den;
	_n1=(n3*T_sec*T_sec + 2*n2*T_sec + 4*n1)/den;
	_n2=(2*n3*T_sec*T_sec - 8*n1)/den;
	_n3=(n3*T_sec*T_sec - 2*n2*T_sec + 4*n1)/den;
	//set to 0 all the support variables
	_u_old=0;
	_u_old_2=0;
	_f_old=0;
	_f_old_2=0;
	_Filt=0;
	_start=0;
	_lastTime=millis();
	}



/*--------------------------------Calculate Output-------------------------------//
This function should be called inside an If statement that checks if the time 
elapsed since the last step is greater or equal than the step time
 //---------------------------------------------------------------------------------*/
 void FILT::Compute(double u)
{
	_Filt=_d2*_f_old+_d3*_f_old_2+_n1*u+_n2*_u_old+_n3*_u_old_2;
	_u_old_2=_u_old;
	_u_old=u;
	_f_old_2=_f_old;
	_f_old=_Filt;
    	*_Output=_Filt;
}

/*-----------------------------AutoCalculate Output----------------------------//
This function can be called inside the loop() environment without the need for
a loop-time check. It should be called as the condition of an if statement so that
if it returns false, the program will stop, otherwise it can continue
 //---------------------------------------------------------------------------------*/
bool FILT::AutoCompute(double u)
{
	uint32_t now = millis();
   if((now-_lastTime)>=_T){
   		_lastTime=now;
		FILT::Compute(u);
    	if ((millis()-_lastTime)>=_T){
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
void FILT::SetStartingValue(double start)
{	
	_start=start;
	_f_old_2=start;
	_f_old=start;
	return;
}
/*------------------------------------Reset----------------------------------//
This function can be called to reset to starting values
 //---------------------------------------------------------------------------------*/
void FILT::Reset()
{
	_f_old_2=_start;
	_f_old=_start;
	_u_old=0;
	_u_old_2=0;
	return;
}
