#include "TimeAlgo.h"
#include <Math.h>

//const double M_PI = 3.14159;

const int par360 = 360;
const int par365 = 365;
const int par284 = 284;
const int par15 = 15;
const int par4 = 4;
const int par12 = 12;

const float Xval_div_par = 365.242;	
const float EOT_par1 = 0.258;									
const float EOT_par2 = 7.416;									
const float EOT_par3 = 3.648;									
const float EOT_par4 = 9.228;
const float D_par = 23.45;


struct Daily_Str dailyVal;


float DegToRad(float deg)
{
	return((float)(deg*M_PI)/((float)180));
}

float RadToDeg(float rad)
{
	return((float)(rad*180)/((float)M_PI));
}

int sign_fun(float x)
{
	if (x >= 0)
		return (1);
	else
		return (-1);
}

double BackTrackVal(double I_L, double bt_angle)
{
	double app;
	
	if (sin(DegToRad(bt_angle)) != 0)
		app = (I_L - cos(DegToRad(bt_angle)))/sin(DegToRad(bt_angle));

	return RadToDeg(atan(app));
}


void DailyAlgo(void)
{

	dailyVal.X = par360*(dailyVal.year_day -1);									// dailyVal.X
	dailyVal.X = dailyVal.X/(float)Xval_div_par;
	dailyVal.EOT_Min = EOT_par1*cos(DegToRad(dailyVal.X)) - EOT_par2*sin(DegToRad(dailyVal.X)) 
				- EOT_par3*cos(DegToRad(2*dailyVal.X)) - EOT_par4*sin(DegToRad(2*dailyVal.X));	// dailyVal.EOT_Min
	
	dailyVal.LC_Min = (SysParams.longitude.f - SysParams.ref_meridian.f)*par4;	// dailyVal.LC_Min
	
	dailyVal.D = D_par*sin(DegToRad((float)par360*(par284+dailyVal.year_day)/(float)par365));	// dailyVal.D
	
}


void BetaEval(struct TIME* local_time, struct Solar_Str* hunter) 
{
	double app;
	
	hunter->TS_min = dailyVal.EOT_Min + dailyVal.LC_Min + 				// TS_Min
						60*(local_time->hour) + local_time->min;

	hunter->Solar_Angle = (float)(par12*60 - hunter->TS_min)/4;		// Solar Angle
	
	app = sin(DegToRad(SysParams.latitude.f))* sin(DegToRad(dailyVal.D))+
			cos(DegToRad(SysParams.latitude.f))* cos(DegToRad(dailyVal.D))*cos(DegToRad(hunter->Solar_Angle));

	hunter->Solar_Height = RadToDeg(asin(app));							// Solar Height

	/* Calcolo Azimut... */
	if (cos(DegToRad(hunter->Solar_Height)) != 0)
	{
		app = cos(DegToRad(dailyVal.D))* sin(DegToRad(hunter->Solar_Angle))/ cos(DegToRad(hunter->Solar_Height));

		if (sin(DegToRad(SysParams.latitude.f)) != 0)
		{
			/* .... con fattori di correzione */
			if (SysParams.latitude.f >= 0)
			{
				if(sin(DegToRad(hunter->Solar_Height)) >= (sin(DegToRad(dailyVal.D))/sin(DegToRad(SysParams.latitude.f))))
					hunter->Azimut = RadToDeg(asin(app));		
				else
					hunter->Azimut = sign_fun(RadToDeg(asin(app))) * (180 - fabs(RadToDeg(asin(app))));
			}
			else
			{
				if(sin(DegToRad(hunter->Solar_Height)) < (sin(DegToRad(dailyVal.D))/sin(DegToRad(SysParams.latitude.f))))
					hunter->Azimut = RadToDeg(asin(app));		
				else
					hunter->Azimut = RadToDeg(asin(app));		
			}
		
			// K1 and K2
			hunter->K1 = cos(DegToRad(hunter->Azimut - SysParams.AW_angle.f))* 
							cos(DegToRad(hunter->Solar_Height));
			hunter->K2 = sin(DegToRad(hunter->Solar_Height));
		
			if (((hunter->K1*hunter->K1)+(hunter->K2*hunter->K2)) != 0)
			{
				app = (hunter->K1*hunter->K1)/((hunter->K1*hunter->K1)+ (hunter->K2*hunter->K2));
				
				app = sqrt(app);
				
				hunter->B_Angle.f = RadToDeg(asin(app));
				
				// After Noon B_Angle is negative 
				if (hunter->Solar_Angle < 0)
					hunter->B_Angle.f = -hunter->B_Angle.f;
				
				//SET_NEW_BETA();
			}
		}
	}
}


void InitSysParam()
{
	SysParams.ModbusConf1.ModbusConfstr = 0;	
	SysParams.WindAl_Tilt.f = 0;
	SysParams.I_L_param.f = 2.0;
	SysParams.BT_Start.f = 5;
	SysParams.BT_Stop.f = 42;
	SysParams.Track_Err.f = 5;
	SysParams.Track_Hyst.f = 5;
	SysParams.AW_angle.f = 90;
	SysParams.latitude.f = 0;//45.95;
	SysParams.longitude.f = 0;//10.5;
	SysParams.ref_meridian.f = 0;//15;
	SysParams.ThermalDecrTilt.f = 10;
	SysParams.ThermalDecrTemp.f = 54;
	SysParams.TempHyst.f = 1;
	SysParams.I_L_morning.f = 2.0;
	SysParams.I_L_evening.f = 2.5;
}




void AlgoInit()
{
	int array_ind, bt_app, dt_app;
	
	for(array_ind = 0; array_ind < BT_NUM; array_ind++)
	{
		back_tracking.bt_val[array_ind] = 0;
		back_tracking.beta_val[array_ind] = 0;
	}
	
	bt_app = (int)SysParams.BT_Start.f;
	array_ind = 0;
	
	while (bt_app <= (int)SysParams.BT_Stop.f)
	{
		back_tracking.bt_val[array_ind] = bt_app;
		back_tracking.beta_val[array_ind] = BackTrackVal(SysParams.I_L_param.f, back_tracking.bt_val[array_ind]);
		
		//printf("bt_app = %d           back_tracking.beta_val[array_ind] = %f\r\n", bt_app, back_tracking.beta_val[array_ind]);
		
// Papier 0112 - In BT l'errore max consentito è pari a Track_Err
		bt_app = bt_app + (int)(SysParams.Track_Err.f);
	
		array_ind++;
	}
	back_tracking.max_ind = array_ind - 1;
}





void AddMinute(struct TIME *t)
{
	t->min++;
	if (t->min > 59)
	{
		t->min = 0,
		t->hour++;
	}
}
