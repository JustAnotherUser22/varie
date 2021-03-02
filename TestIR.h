
#ifndef TESTIR_H
#define TESTIR_H

//#include <stdint.h>


#define uint8_t short unsigned int
#define uint16_t unsigned int
#define uint32_t long unsigned int
#define int8_t short int
#define int16_t int
#define int32_t long int

////////////////////////////////////////////////////////////////////////////////////////
//ENUM E STRUCT LOCALI
///////////////////////////////////////////////////////////////////////////////////////

//lista dei possibili modelli di telecomando supportati dal programma
typedef enum 
{
	DEF_MODEL_GREE,
	DEF_MODEL_HAIER,
	
	NO_MODEL
}IR_MODEL;

//lista dei comandi supportati dai vari modelli
typedef enum 
{
	IR_CMD_ON,
	IR_CMD_OFF,
	IR_CMD_TIMER,
	IR_CMD_SET_MODE,
	IR_CMD_SET_FAN,
	IR_CMD_SET_SWING,
	IR_CMD_SET_TEMPERATURE,
	IR_CMD_SET_TURBO,
	IR_CMD_SET_LIGHT,
	IR_CMD_SET_SANIFICAZIONE,
	IR_CMD_SET_DEPURAZIONE,
	IR_CMD_SET_PALETTE_ORIZZONTALI,
	IR_CMD_SET_PALETTE_VERTICALI,
	IR_CMD_SET_TEMP,
	IR_CMD_SET_IFEEL,
	IR_CMD_SET_TIMER_ON,
	IR_CMD_SET_TIMER_OFF,
	IR_CMD_SET_QUIET,
	IR_CMD_SET_SLEEP_3_ORA_1_TEMPERATURA,
	IR_CMD_SET_SLEEP_3_ORA_2_TEMPERATURA,
	IR_CMD_SET_FAN_ID7,
	IR_CMD_SET_SLEEP_3_ORA_3_TEMPERATURA,
	IR_CMD_SET_SLEEP_3_ORA_4_TEMPERATURA,
	IR_CMD_SET_SLEEP_3_ORA_5_TEMPERATURA,
	IR_CMD_SET_SLEEP_3_ORA_6_TEMPERATURA,
	IR_CMD_SET_SLEEP_3_ORA_7_TEMPERATURA,
	IR_CMD_SET_SLEEP_3_ORA_8_TEMPERATURA,
	
	NO_CMD
}IR_CMD;


struct Table
{
	IR_MODEL model;
	IR_CMD command;
	int8_t* (*build_callback)();	//puntatore a una funzione che ritorna un vettore di int e non vuole argomenti
};


struct State
{
	//per pacchetto ID5
	uint8_t mode:3;
	uint8_t power:1;
	uint8_t fan:2;
	uint8_t swing:1;
	uint8_t sleepBitZero:1;
	
	uint8_t temperatura:4;
	uint8_t wifi:1;
	uint8_t timer:3;
	
	uint8_t TBD:4;
	uint8_t turbo:1;
	uint8_t light:1;
	uint8_t modalitaSanificazione:1;
	uint8_t modalitaDepurazione:1;
	
	uint8_t paletteVerticali:4;
	uint8_t paletteOrizzontali:4;
	
	uint8_t temp:2;
	uint8_t ifeel:1;
	
	//per pacchetto ID6
	uint8_t sleepBitUno:1;
	uint8_t quiet:2;
	uint16_t timer_ON:11;
	uint16_t timer_OFF:11;
	uint8_t timer_ON_enable:1;
	uint8_t timer_OFF_enable:1;
	
	//per pacchetto ID7
	uint8_t sleep_3_ora_1_temperatura:4;
	uint8_t sleep_3_ora_2_temperatura:4;	
	uint8_t fan_ID7:4;	
	
	//per pacchetto ID8
	uint8_t sleep_3_ora_3_temperatura:4;
	uint8_t sleep_3_ora_4_temperatura:4;
	uint8_t sleep_3_ora_5_temperatura:4;
	uint8_t sleep_3_ora_6_temperatura:4;
	uint8_t sleep_3_ora_7_temperatura:4;
	uint8_t sleep_3_ora_8_temperatura:4;
};


enum 
{
	MODE_AUTO = 0x0, 
	MODE_REFFRESCAMENTO, 
	MODE_DEUMIDIFICAZIONE, 
	MODE_VENTILAZIONE, 
	MODE_RISCALDAMENTO
};

enum
{
	POWER_OFF = 0X0,
	POWER_ON
};

enum
{
	FAN_AUTO = 0X0,
	FAN_LIVELLO_1,
	FAN_LIVELLO_2,
	FAN_LIVELLO_3
};

enum
{
	SWING_OFF = 0X0,
	SWING_ON
};

enum
{
	TEMP_16 = 0X0,
	TEMP_17,
	TEMP_18,
	TEMP_19,
	TEMP_20,
	TEMP_21,
	TEMP_22,
	TEMP_23,
	TEMP_24,
	TEMP_25,
	TEMP_26,
	TEMP_27,
	TEMP_28,
	TEMP_29,
	TEMP_30,
};

enum
{
	WIFI_OFF = 0x0,
	WIFI_ON,
};

enum
{
	NO_TIMER = 0x0,
	TIMER_OFF,
	TIMER_ON,
	TIME_ON_OFF,	
};

enum
{
	TURBO_OFF = 0x0,
	TURBO_ON,
};

enum
{
	LIGHT_OFF = 0x0,
	LIGHT_ON,
};

enum
{
	SANIFICAZIONE_OFF = 0x0,
	SANIFICAZIONE_ON,
};

enum
{
	DEPURAZIONE_OFF = 0x0,
	DEPURAZIONE_ON,
};

enum
{
	PALETTE_VERTICALI_AUTO = 0x0,
	PALETTE_VERTICALI_TUTTE,
	PALETTE_VERTICALI_POSIZIONE_1,
	PALETTE_VERTICALI_POSIZIONE_2,
	PALETTE_VERTICALI_POSIZIONE_3,
	PALETTE_VERTICALI_POSIZIONE_4,
	PALETTE_VERTICALI_POSIZIONE_5,
	PALETTE_VERTICALI_BASSO,
	PALETTE_VERTICALI_CENTRO = 0X9,
	PALETTE_VERTICALI_ALTO = 0XB,
};

enum
{
	PALETTE_ORIZZONTALI_AUTO = 0x0,
	PALETTE_ORIZZONTALI_TUTTE,
	PALETTE_ORIZZONTALI_POSIZIONE_1,
	PALETTE_ORIZZONTALI_POSIZIONE_2,
	PALETTE_ORIZZONTALI_POSIZIONE_3,
	PALETTE_ORIZZONTALI_POSIZIONE_4,
	PALETTE_ORIZZONTALI_POSIZIONE_5,
	PALETTE_ORIZZONTALI_ESTERNO = 0XC,
	PALETTE_ORIZZONTALI_ESTERNO_CENTRO = 0XD,
};

enum
{
	TEMP_OFF = 0X0,
	TEMP_MODE_1,
	TEMP_MODE_2,
	TEMP_MODE_3,
};

enum
{
	IFEEL_OFF = 0X0,
	IFEEL_ON	
};

enum
{
	NO_SLEEP = 0x0,
	SLEEP_1,
	SLEEP_2,
	SLEEP_3	
};

enum
{
	QUIET_OFF = 0X0,
	QUIET_AUTO,
	QUIET
};

//presenti nel file di mauro per inviare i dati, copiati qua dentro per usare la stessa nomenclatura
enum
{
    BSP_IR_TX_BIT0,
    BSP_IR_TX_BIT1,
    BSP_IR_TX_PREAMBLE,
    BSP_IR_TX_PAUSE,
    BSP_IR_TX_END
};



////////////////////////////////////////////////////////////////////////////////////////
//FUNZIONI E VARIABILI PUBBLICHE
///////////////////////////////////////////////////////////////////////////////////////

//array da passare alla funzione che comanda il pin del modulo IR per inviare dati
//accetta valori dell'enum sopra
uint8_t totalFrame[200];
uint8_t totalFrameCounter;

//variabile globale che contiene la dimensione del payload generato dai byte da inviare
uint8_t payloadSize;

//funzione da richiamare per inviare il comando desiderato tramite IR
void IRTX_Send(IR_CMD cmd, IR_MODEL model/*, IRobj* obj*/);

////////////////////////////////////////////////////////////////////////////////////////
//FUNZIONI LOCALI
///////////////////////////////////////////////////////////////////////////////////////

//funzioni per costruire i byte 0, 1 e 2 secondo il pacchetto con ID 5
uint8_t buildPacket5Byte0(struct State state);
uint8_t buildPacket5Byte1(struct State state);
uint8_t buildPacket5Byte2(struct State state);

//funzioni per la costruzione dei pacchetti con l'ID indicato
uint8_t* build_Gree_ID5_cb(struct State state);
uint8_t* build_Gree_ID6_cb(struct State state);
uint8_t* build_Gree_ID7_cb(struct State state);
uint8_t* build_Gree_ID8_cb(struct State state);
uint8_t* build_Gree_ID9_cb(struct State state);
uint8_t* build_Gree_IDA_cb(struct State state);

//funzione che costruisce il frame completo (costituito solo da '1' e '0')
int8_t* builtFrame(struct State state);

//funzione che crea il frame completo (con segnali di start, stop, pausa... dato il frame con soli '1' e '0' e il modello del telecomando)
void IR_TRANSMIT(int8_t* p, IR_MODEL m);

int8_t ComputeChecksum(int8_t b[]);
void ConvertByteToBinary(int8_t* v, int position);
int8_t* TurnOn_cb(struct State state);
void LSB2MSB(int8_t* n);

////////////////////////////////////////////////////////////////////////////////////////
//FUNZIONI DI TEST
///////////////////////////////////////////////////////////////////////////////////////

void PrintState(struct State* state);
void printAllData();
int8_t ComputeChecksumTest();
void ComparazioneMisure();
void size();
int8_t* placeholder();
void TestLSB2MSB();
void ConvertByte(int8_t b);
void printMyArray(int8_t* v);

//funzioni di decodifica della trama
void ConvertFromAnalysIR();
int IsPreamble(uint8_t* v);
int IsOne(uint8_t* v);
int IsZero(uint8_t* v);
int IsPause(uint8_t* v);
int IsEnd(uint8_t* v);

#endif
