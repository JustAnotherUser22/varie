

#ifndef TIMEALGO_H
#define TIMEALGO_H


struct TIME
{
	int hour;
	int min;
	int sec;
};


typedef union
{
	unsigned int i;
	float f;
}
intfloat;

struct Solar_Str
{
	int TS_min;		// Solar Time (min)
	double Solar_Angle;		// Angle
	double Solar_Height;	// Angle
	double Azimut;			// Azimut
	double K1;									
	double K2;
	double BT_Angle;		// Current Back Tracking Angle
	intfloat B_Angle;			// Tilt Angle
};	


struct Daily_Str
{
	int year_day;
	double X;
	double EOT_Min;			// Minutes
	double LC_Min;			// Minutes
	double D;				// Angle
};


union ModbusConf
{
	int ModbusConfstr;
	struct ModbusConfBitStr
	{
		int spare:20;
		
		int ModbusSpeed_bit:1;
		int CalibSet_bit:1;
		int AlarmReset_bit:1;
		int WindAl_bit:1;
		int SnowAl_bit:1;
		int SnowSensEn_bit:1;
		int InnerWindSensEn_bit:1;
		int ExtTempEn_bit:1;
		int WestSetTr1_bit:1;
		int HorSetTr1_bit:1;
		int EstSetTr1_bit:1;
		int ManFunTr1_bit:1;
	}bits;
};

struct Sys_Params_Type
{
	union ModbusConf ModbusConf1;
	intfloat longitude;
	intfloat latitude;
	intfloat I_L_param;
	intfloat ref_meridian;
	intfloat AW_angle;
	intfloat BT_Start;
	intfloat BT_Stop;
	intfloat Track_Err;
	intfloat Track_Hyst;
	intfloat WindAl_Tilt;
	intfloat ThermalDecrTilt;					// Angolo riduzione termica
	intfloat ThermalDecrTemp;					// Temperatura inizio riduzione termica
	intfloat TempHyst;							// Isteresi Temperatura
	intfloat I_L_morning;						//fattore di ricoprimento per la mattina
	intfloat I_L_evening;						//fattore di ricoprimento per la sera
};

struct Sys_Params_Type SysParams;

#define BT_NUM				15
struct BT_Type
{
	int max_ind;
	float bt_val[BT_NUM];
	float beta_val[BT_NUM];
};
struct BT_Type back_tracking;




float DegToRad(float deg);
float RadToDeg(float rad);
int sign_fun(float x);
double BackTrackVal(double I_L, double bt_angle);
void DailyAlgo(void);
void BetaEval(struct TIME* local_time, struct Solar_Str* hunter);
void InitSysParam();
void AddMinute(struct TIME *t);
void AlgoInit();	//questa è solo una parte della "vera" funzione implementata nell'inseguitore

#endif
