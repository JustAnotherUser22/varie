/**********************************************************************************************************************
 *               COPYRIGHT NOTICE: (C) 2020, Astrel Group                                                             *
 *               All rights reserved.                                                                                 *
 **********************************************************************************************************************/

#ifndef TESTIR_H
#define TESTIR_H

/**********************************************************************************************************************
 *  1. Include files                                                                                                  *
 **********************************************************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/**********************************************************************************************************************
 *  2. Defines                                                                                                        *
 **********************************************************************************************************************/
/*#define uint8_t short unsigned int
#define uint16_t unsigned int
#define uint32_t long unsigned int
#define int8_t short int
#define int16_t int
#define int32_t long int*/

/**********************************************************************************************************************
 *  3. Macros                                                                                                         *
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  4. Enum  (da cancellare perchè copiate dal file sul server                                                                                                         *
 **********************************************************************************************************************/

// da HvacIrViessman.h
enum
{
    HVACIR_DEF_VIESSMANN_HORIZONTAL_SWING_MODE=0,
    HVACIR_DEF_VIESSMANN_VERTICAL_SWING_MODE,
    HVACIR_DEF_VIESSMANN_QUIET_MODE,
    HVACIR_DEF_VIESSMANN_SLEEP_MODE,
    HVACIR_DEF_VIESSMANN_TEMPERATURE_VIEW_MODE,
    HVACIR_DEF_VIESSMANN_MODE_NUM
};

enum
{
    HVACIR_DEF_VIESSMANN_SETPOINT_SLEEP3,
};

enum
{
    HVACIR_DEF_VIESSMANN_FEATURE_IFEEL=0,
    HVACIR_DEF_VIESSMANN_FEATURE_LIGHT,
    HVACIR_DEF_VIESSMANN_FEATURE_PURIFICATION,
    HVACIR_DEF_VIESSMANN_FEATURE_SANITIZATION,
    HVACIR_DEF_VIESSMANN_FEATURE_WIFI,
    HVACIR_DEF_VIESSMANN_FEATURE_NUM
};

enum
{
    HVACIR_DEF_VIESSMANN_HORIZONTAL_SWING_MODE_AUTO=0,
    HVACIR_DEF_VIESSMANN_HORIZONTAL_SWING_MODE_ALL,
    HVACIR_DEF_VIESSMANN_HORIZONTAL_SWING_MODE_POS1,
    HVACIR_DEF_VIESSMANN_HORIZONTAL_SWING_MODE_POS2,
    HVACIR_DEF_VIESSMANN_HORIZONTAL_SWING_MODE_POS3,
    HVACIR_DEF_VIESSMANN_HORIZONTAL_SWING_MODE_POS4,
    HVACIR_DEF_VIESSMANN_HORIZONTAL_SWING_MODE_POS5,
    HVACIR_DEF_VIESSMANN_HORIZONTAL_SWING_MODE_EXT=0x0C,
    HVACIR_DEF_VIESSMANN_HORIZONTAL_SWING_MODE_EXT_MIDDLE=0x0D
};

enum
{
    HVACIR_DEF_VIESSMANN_VERTICAL_SWING_MODE_AUTO=0,
    HVACIR_DEF_VIESSMANN_VERTICAL_SWING_MODE_ALL,
    HVACIR_DEF_VIESSMANN_VERTICAL_SWING_MODE_POS1,
    HVACIR_DEF_VIESSMANN_VERTICAL_SWING_MODE_POS2,
    HVACIR_DEF_VIESSMANN_VERTICAL_SWING_MODE_POS3,
    HVACIR_DEF_VIESSMANN_VERTICAL_SWING_MODE_POS4,
    HVACIR_DEF_VIESSMANN_VERTICAL_SWING_MODE_POS5,
    HVACIR_DEF_VIESSMANN_VERTICAL_SWING_MODE_LOW,
    HVACIR_DEF_VIESSMANN_VERTICAL_SWING_MODE_MIDDLE=0x09,
    HVACIR_DEF_VIESSMANN_VERTICAL_SWING_MODE_HIGH=0x0B
};

enum
{
    HVACIR_DEF_VIESSMANN_TEMPERATURE_VIEW_MODE_OFF=0,
    HVACIR_DEF_VIESSMANN_TEMPERATURE_VIEW_MODE_1,
    HVACIR_DEF_VIESSMANN_TEMPERATURE_VIEW_MODE_2,
    HVACIR_DEF_VIESSMANN_TEMPERATURE_VIEW_MODE_3
};

enum
{
    HVACIR_DEF_VIESSMANN_SLEEP_MODE_DISABLED=0,
    HVACIR_DEF_VIESSMANN_SLEEP_MODE_1,
    HVACIR_DEF_VIESSMANN_SLEEP_MODE_2,
    HVACIR_DEF_VIESSMANN_SLEEP_MODE_3
};

enum
{
    HVACIR_DEF_VIESSMANN_QUIET_MODE_OFF=0,
    HVACIR_DEF_VIESSMANN_QUIET_MODE_AUTO,
    HVACIR_DEF_QUIET_MODE_ON
};


//HavicIr.h
enum
{
    HVACIR_DEF_MANUFACTURER_NULL,
    HVACIR_DEF_MANUFACTURER_VIESSMANN
};

enum
{
    HVACIR_DEF_FAN_MODE=0,
    HVACIR_DEF_SYS_MODE,
    HVACIR_DEF_TIMER_MODE,
    HVACIR_DEF_MODE_NUM
};

enum
{
    HVACIR_DEF_FAN_MODE_LOW=1,
    HVACIR_DEF_FAN_MODE_MID=2,
    HVACIR_DEF_FAN_MODE_HIGH=3,
    HVACIR_DEF_FAN_MODE_AUTO=5,
    HVACIR_DEF_FAN_MODE_SILENT=16
};

enum
{
    HVACIR_DEF_SYS_MODE_OFF=0,
    HVACIR_DEF_SYS_MODE_AUTO=1,
    HVACIR_DEF_SYS_MODE_COOLING=3,
    HVACIR_DEF_SYS_MODE_HEATING=4,
    HVACIR_DEF_SYS_MODE_FAN_ONLY=7,
    HVACIR_DEF_SYS_MODE_DRY=8
};

enum
{
    HVACIR_DEF_OFF_CMD=0,
    HVACIR_DEF_ON_CMD,
    HVACIR_DEF_TOGGLE_CMD
};

enum
{
    HVACIR_DEF_SETPOINT_HEATING=0,
    HVACIR_DEF_SETPOINT_HEATING_MIN,
    HVACIR_DEF_SETPOINT_HEATING_MAX,
    HVACIR_DEF_SETPOINT_COOLING,
    HVACIR_DEF_SETPOINT_COOLING_MIN,
    HVACIR_DEF_SETPOINT_COOLING_MAX,
};

enum
{
    HVACIR_DEF_FEATURE_SWING=0,
    HVACIR_DEF_FEATURE_TURBO,
    HVACIR_DEF_FEATURE_NUM
};

enum
{
    HVACIR_DEF_TIMER_ON=0,
    HVACIR_DEF_TIMER_OFF
};

enum
{
    HVACIR_DEF_TIMER_MODE_DISABLED=0,
    HVACIR_DEF_TIMER_MODE_OFF,
    HVACIR_DEF_TIMER_MODE_ON,
    HVACIR_DEF_TIMER_MODE_ON_OFF
};

//obj proveniente dall'alto (vedi file Settings.h)
#define CONFIG_DEF_ENABLE_VIESSMANN_FEATURES
#define CONFIG_DEF_ENABLE_SWING
#define CONFIG_DEF_ENABLE_HEATING_SETPOINT
#define CONFIG_DEF_ENABLE_HEATING_SETPOINT_LIMITS
#define CONFIG_DEF_ENABLE_COOLING_SETPOINT_LIMITS
#define CONFIG_DEF_ENABLE_TIMER
#define SETTINGS_DEF_MANUFACTURERS_FEATURES_ENABLED

typedef union
{
    struct
    {
        uint32_t    ifeel_enabled           : 1;
        uint32_t    light_enabled           : 1;
        uint32_t    purification_enabled    : 1;
        uint32_t    sanitization_enabled    : 1;
        uint32_t    wifi_enabled            : 1;
    }bits;

    uint32_t mask;
} settings_viessmann_features_t;

typedef struct
{
    settings_viessmann_features_t   hvacir_features;
    uint8_t                         hvacir_quiet_mode;
    uint8_t                         hvacir_sleep_mode;
    uint8_t                         hvacir_horizontal_swing_mode;
    uint8_t                         hvacir_vertical_swing_mode;
    uint8_t                         hvacir_temperature_view_mode;
    int16_t                         hvacir_sleep3_setpoints[8];
}settings_viessmann_List_t;


typedef struct
{
    #ifdef CONFIG_DEF_ENABLE_VIESSMANN_FEATURES
    settings_viessmann_List_t   viessmann;
    #endif
}settings_manufacturers_List_t;


typedef union
{
    struct
    {
        uint32_t    turbo_enabled : 1;
        #ifdef CONFIG_DEF_ENABLE_SWING
        uint32_t    swing_enabled : 1;
        #endif
    }bits;

    uint32_t mask;
} settings_features_t;

typedef struct
{
    settings_features_t hvacir_features;
    bool                hvacir_is_on;
    uint8_t             hvacir_fan_mode;
    uint8_t             hvacir_sys_mode;
    #ifdef CONFIG_DEF_ENABLE_HEATING_SETPOINT
    int16_t             hvacir_ambient_heating_setpoint;
    #ifdef CONFIG_DEF_ENABLE_HEATING_SETPOINT_LIMITS
    int16_t             hvacir_ambient_heating_setpoint_min;
    int16_t             hvacir_ambient_heating_setpoint_max;
    #endif
    #endif
    int16_t             hvacir_ambient_cooling_setpoint;
    #ifdef CONFIG_DEF_ENABLE_COOLING_SETPOINT_LIMITS
    int16_t             hvacir_ambient_cooling_setpoint_min;
    int16_t             hvacir_ambient_cooling_setpoint_max;
    #endif
    #ifdef CONFIG_DEF_ENABLE_TIMER
    uint8_t             hvacir_timer_mode;
    uint8_t             hvacir_on_timer_duration;
    uint8_t             hvacir_off_timer_duration;
    #endif

    #ifdef SETTINGS_DEF_MANUFACTURERS_FEATURES_ENABLED
    settings_manufacturers_List_t   ManufacturerSettigs;
    #endif
}settings_List_t;

/**********************************************************************************************************************
 *  4. Enum                                                                                                           *
 **********************************************************************************************************************/

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
	FAN_LIVELLO_3,
	FAN_LIVELLO_4,
	FAN_LIVELLO_5
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


/**********************************************************************************************************************
 *  5. Structures                                                                                                     *
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  6. Type definitions                                                                                               *
 **********************************************************************************************************************/

//lista dei possibili modelli di telecomando supportati dal programma
typedef enum 
{
	DEF_MODEL_GREE,
	DEF_MODEL_HAIER,		//allo stato attuale delle cose haier non è supportato
	
	NO_MODEL
}IR_MODEL;

//lista dei comandi supportati dai vari modelli
typedef enum 
{
	IR_CMD_ON,
	IR_CMD_OFF,
	IR_CMD_SET_MODE,
	IR_CMD_SET_TEMPERATURE,
	
	//comandi richiesti dal cliente
	IR_CMD_CHANGE_MODE,
	IR_CMD_CHANGE_FAN,
	IR_CMD_CHANGE_SET_POINT,
	IR_CMD_ON_OFF,
	IR_CMD_SET_QUIET_MODE,
	
	NO_CMD
}IR_CMD;


typedef struct 
{
	IR_MODEL model;
	IR_CMD command;
	int8_t* (*build_callback)();	//puntatore a una funzione che ritorna un vettore di int e non vuole argomenti
}Table;


typedef struct 
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
	uint16_t timer_ON_duration:11;
	uint16_t timer_OFF_duration:11;
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
}State;


/**********************************************************************************************************************
 * 7. public variables                                                                          *
 **********************************************************************************************************************/

//array da passare alla funzione che comanda il pin del modulo IR per inviare dati
//accetta valori dell'enum sopra
uint8_t totalFrame[200];
uint8_t totalFrameCounter;

//variabile globale che contiene la dimensione del payload generato dai byte da inviare
uint8_t payloadSize;


/**********************************************************************************************************************
 * 8. Global function definitions (public)                                                                           *
 **********************************************************************************************************************/

//funzione da richiamare per inviare il comando desiderato tramite IR
void IRTX_Send(IR_CMD cmd, IR_MODEL model, settings_List_t* obj);


/**********************************************************************************************************************
 * 9. Global function definitions (private)                                                                           *
 **********************************************************************************************************************/

State FromObjToState(settings_List_t* obj);
uint8_t ConvertObjTemperatureToStateTemperature(int16_t objTemperature);

//funzioni per costruire i byte 0, 1 e 2 secondo il pacchetto con ID 5
uint8_t buildPacket5Byte0(State* state);
uint8_t buildPacket5Byte1(State* state);
uint8_t buildPacket5Byte2(State* state);

//funzioni per la costruzione dei pacchetti con l'ID indicato
uint8_t* build_Gree_ID5_cb(State* state);
uint8_t* build_Gree_ID6_cb(State* state);
uint8_t* build_Gree_ID7_cb(State* state);
uint8_t* build_Gree_ID8_cb(State* state);
uint8_t* build_Gree_ID9_cb(State* state);
uint8_t* build_Gree_IDA_cb();
int8_t ComputeChecksum(int8_t b[]);

//funzione che costruisce il frame completo (costituito solo da '1' e '0')
int8_t* builtFrame(State* state);

//funzione che crea il frame completo (con segnali di start, stop, pausa... dato il frame con soli '1' e '0' e il modello del telecomando)
void IR_TRANSMIT(int8_t* p, IR_MODEL m);

void ConvertByteToBinary(int8_t* v, int position);
void LSB2MSB(int8_t* n);


/**********************************************************************************************************************
 * 10. Global function definitions (private, only for test)                                                                           *
 **********************************************************************************************************************/
void TestObjToState();

void PrintState(State* state);
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
int IsPreamble(uint16_t* v);
int IsOne(uint16_t* v);
int IsZero(uint16_t* v);
int IsPause(uint16_t* v);
int IsEnd(uint16_t* v);


#endif
