#include <stdio.h>
#include <stdlib.h>
#include "TestIR.h"
//#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////////////
//VARIABILI LOCALI
///////////////////////////////////////////////////////////////////////////////////////

Table t[] = 
{
	{DEF_MODEL_GREE, IR_CMD_ON, &builtFrame},
	{DEF_MODEL_GREE, IR_CMD_OFF, &placeholder},
	{DEF_MODEL_HAIER, IR_CMD_ON, &placeholder},
	{DEF_MODEL_HAIER, IR_CMD_OFF, &placeholder},
	
	//comandi chiesti dal cliente
	{DEF_MODEL_GREE, IR_CMD_CHANGE_MODE, &placeholder},
	{DEF_MODEL_GREE, IR_CMD_CHANGE_FAN, &placeholder},
	{DEF_MODEL_GREE, IR_CMD_CHANGE_SET_POINT, &placeholder},
	{DEF_MODEL_GREE, IR_CMD_ON_OFF, &placeholder},
	{DEF_MODEL_GREE, IR_CMD_SET_QUIET_MODE, &placeholder},
	
	{DEF_MODEL_HAIER, IR_CMD_CHANGE_MODE, &placeholder},
	{DEF_MODEL_HAIER, IR_CMD_CHANGE_FAN, &placeholder},
	{DEF_MODEL_HAIER, IR_CMD_CHANGE_SET_POINT, &placeholder},
	{DEF_MODEL_HAIER, IR_CMD_ON_OFF, &placeholder},
	{DEF_MODEL_HAIER, IR_CMD_SET_QUIET_MODE, &placeholder},
	
	
	
	{NO_MODEL, NO_CMD, &placeholder},
};


State s = 
{
	.mode = MODE_REFFRESCAMENTO,
	.power = POWER_OFF,
	.fan = FAN_AUTO,
	.swing = SWING_OFF,
	.sleepBitZero = 0,
	
	.temperatura = TEMP_16,
	.wifi = WIFI_OFF,
	.timer = TIMER_ON,
	
	.TBD = 4,
	.turbo = TURBO_OFF,
	.light = LIGHT_OFF,
	.modalitaSanificazione = SANIFICAZIONE_OFF,
	.modalitaDepurazione = DEPURAZIONE_OFF,
	
	.paletteVerticali = PALETTE_VERTICALI_AUTO,
	.paletteOrizzontali = PALETTE_ORIZZONTALI_AUTO,
	
	.temp = TEMP_OFF,
	.ifeel = IFEEL_OFF,
	
	//per pacchetto ID6
	.sleepBitUno = 0,
	.quiet = QUIET_OFF,
	.timer_ON = 0X123,
	.timer_OFF = 0X456,
	.timer_ON_enable = 0,
	.timer_OFF_enable = 0,
	
	//per pacchetto ID7
	.sleep_3_ora_1_temperatura = TEMP_16,
	.sleep_3_ora_2_temperatura = TEMP_17,
	.fan_ID7 = 1,	
	
	//per pacchetto ID8
	.sleep_3_ora_3_temperatura = TEMP_18,
	.sleep_3_ora_4_temperatura = TEMP_19,
	.sleep_3_ora_5_temperatura = TEMP_20,
	.sleep_3_ora_6_temperatura = TEMP_21,
	.sleep_3_ora_7_temperatura = TEMP_22,
	.sleep_3_ora_8_temperatura = TEMP_23,
};


////////////////////////////////////////////////////////////////////////////////////////
//FUNZIONI PUBBLICHE
///////////////////////////////////////////////////////////////////////////////////////

void IRTX_Send(IR_CMD cmd, IR_MODEL model, settings_List_t* obj)
{
	int8_t counter = 0;
	int8_t* payload; 
	
	State state = FromObjToState(obj);
	
	for (counter = 0; t[counter].model != NO_MODEL; counter++)
	{
		if(t[counter].model == model && t[counter].command == cmd)
		{
			payload = t[counter].build_callback(s);
		}
	}
	
	//for (counter = 0; counter < 10; counter++)
	//	printf("%d ", payload[counter]);
		
	if(payload)
		IR_TRANSMIT(payload, model);
}



////////////////////////////////////////////////////////////////////////////////////////
//FUNZIONI LOCALI
///////////////////////////////////////////////////////////////////////////////////////

State FromObjToState(settings_List_t* obj)
{
	State s;
	
	
	if(obj->hvacir_ifeel_enabled)
		s.ifeel = IFEEL_ON;
	else
		s.ifeel = IFEEL_OFF;
	
	if(obj->hvacir_light_enabled)
		s.light = LIGHT_ON;
	else
		s.light = LIGHT_OFF;
	
	if(obj->hvacir_purification_enabled)
		s.modalitaDepurazione = DEPURAZIONE_ON;
	else
		s.modalitaDepurazione = DEPURAZIONE_OFF;
		
	if(obj->hvacir_sanitization_enabled)
		s.modalitaSanificazione = SANIFICAZIONE_ON;
	else
		s.modalitaSanificazione = SANIFICAZIONE_OFF;
		
	if(obj->hvacir_swing_enabled)
		s.swing = SWING_ON;
	else
		s.swing = SWING_OFF;
	
	if(obj->hvacir_turbo_enabled)
		s.turbo = TURBO_ON;
	else
		s.turbo = TURBO_OFF;
		
	if(obj->hvacir_wifi_enabled)
		s.wifi = WIFI_ON;
	else
		s.wifi = WIFI_OFF;	
		
		

	
	
	if (obj->hvacir_sys_mode == HVACIR_DEF_SYS_MODE_OFF)
	{
		s.mode = MODE_AUTO;
		s.temperatura = ConvertObjTemperatureToStateTemperature(obj->hvacir_ambient_heating_setpoint);	//TODO: controlla questa conversione
	}
	if (obj->hvacir_sys_mode == HVACIR_DEF_SYS_MODE_AUTO)
	{
		s.mode = MODE_AUTO;
		//TODO: controlla che temperatura viene inviata in questo caso
	}
	if (obj->hvacir_sys_mode == HVACIR_DEF_SYS_MODE_COOLING)
	{
		s.mode = MODE_REFFRESCAMENTO;
		s.temperatura = ConvertObjTemperatureToStateTemperature(obj->hvacir_ambient_cooling_setpoint);	//TODO: controlla questa conversione
	}
	if (obj->hvacir_sys_mode == HVACIR_DEF_SYS_MODE_HEATING)
	{
		s.mode = MODE_RISCALDAMENTO;
		s.temperatura = ConvertObjTemperatureToStateTemperature(obj->hvacir_ambient_heating_setpoint);	//TODO: controlla questa conversione
	}
	if (obj->hvacir_sys_mode == HVACIR_DEF_SYS_MODE_FAN_ONLY)
	{
		s.mode = MODE_VENTILAZIONE;
		//in questo caso la temperatura inviata è un parametro inutile
		s.temperatura = 0;
	}
	if (obj->hvacir_sys_mode == HVACIR_DEF_SYS_MODE_DRY)
	{
		s.mode = MODE_DEUMIDIFICAZIONE;
		s.temperatura = ConvertObjTemperatureToStateTemperature(obj->hvacir_ambient_cooling_setpoint - 16);	//TODO: controlla questa conversione
	}
		
		
	//TODO controlla velocità nel caso a 3 opzioni
	if (obj->hvacir_fan_mode == HVACIR_DEF_FAN_MODE_LOW)	
	{
		s.fan = FAN_LIVELLO_1;
		s.fan_ID7 = FAN_LIVELLO_1;
	}
	if (obj->hvacir_fan_mode == HVACIR_DEF_FAN_MODE_MID)	
	{
		s.fan = FAN_LIVELLO_3;
		s.fan_ID7 = FAN_LIVELLO_3;
	}
	if (obj->hvacir_fan_mode == HVACIR_DEF_FAN_MODE_HIGH)	
	{
		s.fan = FAN_LIVELLO_3;
		s.fan_ID7 = FAN_LIVELLO_5;
	}
	if (obj->hvacir_fan_mode == HVACIR_DEF_FAN_MODE_AUTO)	
	{
		s.fan = FAN_AUTO;
		s.fan_ID7 = FAN_AUTO;
	}
	if (obj->hvacir_fan_mode == HVACIR_DEF_FAN_MODE_SILENT)	
	{
		s.fan = 0;	//TBD
		s.fan_ID7 = 0;	//TBD
	}
	
	
	//TODO: queste funzionano perchè sono stati usati gli stessi valori del protocollo per l'hvacir
	//forse è meglio dividere i due casi, da concordare
	s.paletteOrizzontali = obj->hvacir_horizontal_swing_mode;
	s.paletteVerticali = obj->hvacir_vertical_swing_mode;
	s.quiet = obj->hvacir_quiet_mode;
	
	s.sleepBitZero = obj->hvacir_sleep_mode;
	s.sleepBitUno = obj->hvacir_sleep_mode >> 1;
	
	
	
	
	return s;
}

uint8_t ConvertObjTemperatureToStateTemperature(int16_t objTemperature)
{
	return (uint8_t) (objTemperature - 16);
}


uint8_t buildPacket5Byte0(State state)
{
	return (state.sleepBitZero << 7) | (state.swing << 6) | (state.fan << 4) | (state.power << 3) | state.mode;
}

uint8_t buildPacket5Byte1(State state)
{
	return (state.timer << 5) | (state.wifi << 4) | state.temperatura;
}

uint8_t buildPacket5Byte2(State state)
{
	return (state.modalitaSanificazione < 6) | (state.light << 5) | (state.turbo << 4) | state.TBD;
}



uint8_t* build_Gree_ID5_cb(State state)
{
	static uint8_t c[8];
	
	uint8_t i;
	for(i = 0; i < 8; i++)
		c[i] = 0x00;
	
	c[0] = buildPacket5Byte0(state);
	c[1] = buildPacket5Byte1(state);
	c[2] = buildPacket5Byte2(state);
	c[3] = (0x05 << 4) | (state.modalitaDepurazione << 1);
	c[4] = (state.paletteOrizzontali << 4) | state.paletteVerticali;
	c[5] = 0x00;
	c[6] = 0x00;
	c[7] = ComputeChecksum(c) << 4;		
	
	printf("\n");
	for(i = 0; i < 8; i++)
		printf("%02x ", c[i]);
	
	return c;
}

uint8_t* build_Gree_ID6_cb(State state)
{
	static uint8_t c[8];
	
	uint8_t i;
	for(i = 0; i < 8; i++)
		c[i] = 0x00;
		
	c[0] = buildPacket5Byte0(state);
	c[1] = buildPacket5Byte1(state);
	c[2] = buildPacket5Byte2(state);
	c[3] = (0x06 << 4) | (state.modalitaDepurazione << 1);
	c[4] = state.timer_ON & 0x0FF;
	c[5] = (state.timer_OFF_enable << 7) | (((state.timer_OFF & 0x700) >> 8) << 4) | (state.timer_ON_enable << 3) | ((state.timer_ON & 0x700) >> 8);
	c[6] = state.timer_OFF & 0x0FF;
	c[7] = ComputeChecksum(c) << 4;	
		
	printf("\n");
	for(i = 0; i < 8; i++)
		printf("%02x ", c[i]);
		
	return c;
}

uint8_t* build_Gree_ID7_cb(State state)
{
	static uint8_t c[8];
	
	uint8_t i;
	for(i = 0; i < 8; i++)
		c[i] = 0x00;
	
	c[0] = buildPacket5Byte0(state);
	c[1] = buildPacket5Byte1(state);
	c[2] = buildPacket5Byte2(state);
	c[3] = (0x07 << 4) | (state.modalitaDepurazione << 1);
	c[4] = (state.quiet << 6) | state.sleepBitUno;
	c[5] = (state.sleep_3_ora_2_temperatura << 4) | state.sleep_3_ora_1_temperatura;
	c[6] = state.fan_ID7 << 4;
	c[7] = ComputeChecksum(c) << 4;	
	
	printf("\n");
	for(i = 0; i < 8; i++)
		printf("%02x ", c[i]);
	
	return c;
}

uint8_t* build_Gree_ID8_cb(State state)
{
	static uint8_t c[8];
	
	uint8_t i;
	for(i = 0; i < 8; i++)
		c[i] = 0x00;
	
	c[0] = buildPacket5Byte0(state);
	c[1] = buildPacket5Byte1(state);
	c[2] = buildPacket5Byte2(state);
	c[3] = (0x08 << 4) | (state.modalitaDepurazione << 1);
	c[4] = (state.sleep_3_ora_4_temperatura << 4) | state.sleep_3_ora_3_temperatura;
	c[5] = (state.sleep_3_ora_6_temperatura << 4) | state.sleep_3_ora_5_temperatura;
	c[6] = (state.sleep_3_ora_8_temperatura << 4) | state.sleep_3_ora_7_temperatura;
	c[7] = ComputeChecksum(c) << 4;	
	
	printf("\n");
	for(i = 0; i < 8; i++)
		printf("%02x ", c[i]);
	
	return c;
}

uint8_t* build_Gree_IDA_cb(State state)
{
	static uint8_t c[8];
	
	uint8_t i;
	for(i = 0; i < 8; i++)
		c[i] = 0x00;
	
	c[3] = (0x0A << 4);
	c[7] = ComputeChecksum(c) << 4;	
	
	printf("\n");
	for(i = 0; i < 8; i++)
		printf("%02x ", c[i]);
	
	return c;
}

int8_t ComputeChecksum(int8_t b[])
{
	int8_t cks = (int8_t)((0x0A + (b[0] & 0x0F) + (b[1] & 0x0F) + (b[2] & 0x0F) + (b[3] & 0x0F) + ((b[4] & 0xF0) >> 4) + ((b[5] & 0xF0) >> 4) + ((b[6] & 0xF0) >> 4)) & 0x0F); 
	//printf("%x", cks);
	return cks;
}


void IR_TRANSMIT(int8_t* p, IR_MODEL m)
{
	//questa qua richiamerà la funzione già fatta da mauro per inviare i byte
	
	//imposta lunghezza tempo di on e off
	//imposta altri simboli (start, stop)
	//metti tutto in un buffer e invia
	
	if(m == DEF_MODEL_GREE)
	{
		totalFrameCounter = 0;
		
		uint8_t packets = payloadSize / 8;	//ogni pacchetto contiene 8 bytes
		
		uint8_t i = 0;
		for(i = 0; i < packets; i++)	//ogni "pacchetto" ha un formato come quello costruito sotto
		{
			totalFrame[totalFrameCounter++] = BSP_IR_TX_PREAMBLE;
		
			ConvertByte(p[i * 8 + 0]);
			ConvertByte(p[i * 8 + 1]);
			ConvertByte(p[i * 8 + 2]);
			ConvertByte(p[i * 8 + 3]);
			
			totalFrame[totalFrameCounter++] = BSP_IR_TX_BIT0;
			totalFrame[totalFrameCounter++] = BSP_IR_TX_BIT1;
			totalFrame[totalFrameCounter++] = BSP_IR_TX_BIT0;	
			totalFrame[totalFrameCounter++] = BSP_IR_TX_PAUSE;
			
			ConvertByte(p[i * 8 + 4]);
			ConvertByte(p[i * 8 + 5]);
			ConvertByte(p[i * 8 + 6]);
			ConvertByte(p[i * 8 + 7]);
			
			totalFrame[totalFrameCounter++] = BSP_IR_TX_END;
		}
		
		printf("\n\n");
		for(i = 0; i < packets; i++)
			printMyArray(&totalFrame[i * 70]);		//8byte = 64 bit, + altri 6 di preambolo, pausa, end '0' e '1'
		
		
		/*totalFrame[totalFrameCounter++] = BSP_IR_TX_PREAMBLE;
		
		ConvertByte(p[0]);
		ConvertByte(p[1]);
		ConvertByte(p[2]);
		ConvertByte(p[3]);
		
		totalFrame[totalFrameCounter++] = BSP_IR_TX_BIT0;
		totalFrame[totalFrameCounter++] = BSP_IR_TX_BIT1;
		totalFrame[totalFrameCounter++] = BSP_IR_TX_BIT0;	
		totalFrame[totalFrameCounter++] = BSP_IR_TX_PAUSE;
		
		ConvertByte(p[4]);
		ConvertByte(p[5]);
		ConvertByte(p[6]);
		ConvertByte(p[7]);
		
		totalFrame[totalFrameCounter++] = BSP_IR_TX_END;
		
		printAllData();*/
	}
	else if(m == DEF_MODEL_HAIER)
	{
		
	}
}


/*
vuole come argomento un vettore di caratteri esadecimali
converte ogniuno di questi caratteri nel suo equivalente in binario
e per ogni cifra binaria ritorna un intero che vale '1' o '0'
*/
void ConvertByteToBinary(int8_t* v, int position)
{
	int i;
	for(i = position; i < position + 5; i++)	//considera 4 valori consecutivi
	{
		int mask = 0x01;
		while(mask <= 0x20)
		{
			if( (v[i] & mask) == 0)
				totalFrame[totalFrameCounter++] = BSP_IR_TX_BIT0;
			else
				totalFrame[totalFrameCounter++] = BSP_IR_TX_BIT1;
			mask = mask << 1;
		}
	}
}

/*void ConvertByte(int8_t b)
{
	uint8_t i = 8;	
	uint8_t bin[8];
	uint8_t cnt = 0;
	
	for(i = 0; i < 8; i++)
		bin[i] = 0;
	
	uint8_t mask = 0x01;
	for(cnt = 0; cnt < 8; cnt++)
	{
		printf("%x\n", mask);
		if( ( b & mask) == 0)
			bin[7-cnt] = BSP_IR_TX_BIT0;
		else
			bin[7-cnt] = BSP_IR_TX_BIT1;
		mask = mask << 1;
		i++;
	}	
	
	for(i = 0; i < 8; i++)
		printf("%d ", bin[i]);
}*/


/*
converte un byte nei corrispettivi 8 bit e inserisce ciascuno di questi 8 bit nell'array che verrè passato alla funzione di interrupt che manda i dati
NOTA: nella conversione viene inviato per primo il bit meno significativo!!!
*/
void ConvertByte(int8_t b)
{
	uint8_t cnt = 0;
	uint8_t mask = 0x01;
	
	for(cnt = 0; cnt < 8; cnt++)
	{
		if( ( b & mask) == 0)
			totalFrame[totalFrameCounter++] = BSP_IR_TX_BIT0;
		else
			totalFrame[totalFrameCounter++] = BSP_IR_TX_BIT1;
		mask = mask << 1;
	}	
}


/*
crea un unico vettore con i frame concatenatenati
da notare che
packet ID 0x05 -> sempre inviato
packet ID 0x06 -> inviato solo per impostare o disattivare timer
packet ID 0x07 -> sempre inviato
packet ID 0x08 -> inviato solo in modalità sleep 3
packet ID 0x0A -> sempre inviato (ultimo pacchetto) (??????????????)
*/
int8_t* builtFrame(State state)
{
	/*
	int8_t *firstFrame = build_Gree_ID5_cb(state);
	int8_t *secondFrame = build_Gree_ID7_cb(state);
	//int8_t* lastFrame = build_Gree_IDA_cb(state);

	//dichiarazione dell'array che comprende i frame creati sopra
	#define LENGTH 16
	int8_t* totalFrame = malloc(LENGTH); //TBD
	
	int i = 0;
	int j = 0;
	
	for(j = 0; j < 8; j++)
	{
		totalFrame[i] = firstFrame[j];
		i++;
	}
	
	for(j = 0; j < 8; j++)
	{
		totalFrame[i] = secondFrame[j];
		i++;
	}
	
	printf("\n");
	for(i = 0; i < 16; i++)
		printf("%x ",totalFrame[i]);
	
	return totalFrame;
	*/
	//////////////////////////////////////
	
	/*		
	controlla che il comando sia effettivamente supportato, altrimenti ritorna errore.
	se è supportato costruisci i frame corrispondenti, per es:
	-costrusci sempre frame 0x05 e 0x07
	- if(timer == on) -> costruisci frame 0x06
	- if(sleep3 == on) -> costruisci frame 0x08
	alla fine accoda tutti i byte
	*/
	
	IR_CMD cmd = 0;
	
	//lunghezza totale del pacchetto espressa in byte (ogni pacchetto è composto da 8 byte);
	int8_t totalLength = 0;
	
	//dichiarazione dei frame
	uint8_t *frame5 = NULL;
	uint8_t *frame6 = NULL;
	uint8_t *frame7 = NULL;
	uint8_t* frame8 = NULL;
	uint8_t *frameA = NULL;
	
	//popolamento dei frame (se necessario)
	frame5 = build_Gree_ID5_cb(state);
	totalLength += 8;
	
	frame7 = build_Gree_ID7_cb(state);
	totalLength += 8;
	
	if(state.timer != NO_TIMER)
    {
		frame6 = build_Gree_ID6_cb(state);
		totalLength += 8;
	}	
	
	if( (state.sleepBitZero == 1) && (state.sleepBitUno == 1) &&	//se sono in sleep 3
		(cmd != IR_CMD_OFF) && 										//e non ho premuto il pulsante per spegnere il dispositivo
		(cmd != IR_CMD_SET_MODE) )									//e non sto cambiando modalità
	{
		frame8 = build_Gree_ID8_cb(state);
		totalLength += 8;
	}	
	
	payloadSize = totalLength;
	
	int8_t* totalFrame = malloc(totalLength * sizeof(int8_t));
	//static int8_t totalFrame[totalLength];
	
	int i = 0;
	int j = 0;
	
	if(frame5 != NULL)
		for(j = 0; j < 8; j++)
			totalFrame[i++] = frame5[j];
	
	if(frame6 != NULL)
		for(j = 0; j < 8; j++)
			totalFrame[i++] = frame6[j];
	
	if(frame7 != NULL)
		for(j = 0; j < 8; j++)
			totalFrame[i++] = frame7[j];
	
	if(frame8 != NULL)
		for(j = 0; j < 8; j++)
			totalFrame[i++] = frame8[j];
	
	if(frameA != NULL)
		for(j = 0; j < 8; j++)
			totalFrame[i++] = frameA[j];
			
	printf("\n\n");
		for(i = 0; i < totalLength; i++)
			printf("%02x ",totalFrame[i]);
	
	return totalFrame;	
}


//funzione che si occupa di creare il pacchetto nel caso di accensione
int8_t* TurnOn_cb(State state)
{
	//TODO: eventuale controllo nel caso in cui il nuovo stato sia uguale a quello attuale?
	
	state.power = POWER_OFF;
	int8_t* c = builtFrame(state);
	return c;
}

 void LSB2MSB(int8_t* n)
 {
 	int8_t tmp = 0;
 	uint8_t mask = 0x01;
 	uint8_t i;
 	int8_t arr[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
 	
 	
 	printf("n = %x \n", (*n));
 	int v = (*n);
 	
 	for(i = 0; i < 8; i++)
	{
		int m = v & mask;
		printf("m = %x\n", m);
		
		if( ( (*n) & mask) != 0)
			tmp |= arr[i];
		
		mask = mask << 1;	
	}
	printf("tmp = %x \n", tmp); 
	
 	(*n) = tmp;
 	
 	printf("fine n = %x \n", (*n)); 	
 }

////////////////////////////////////////////////////////////////////////////////////////
//FUNZIONI DI TEST
///////////////////////////////////////////////////////////////////////////////////////

void TestObjToState()
{
	settings_List_t obj = {
		.hvacir_ifeel_enabled = true,
		.hvacir_light_enabled = true,
    	.hvacir_purification_enabled = true,
    	.hvacir_sanitization_enabled = true,
    	.hvacir_swing_enabled = true,
    	.hvacir_turbo_enabled = true,
    	.hvacir_wifi_enabled = true,
    	.hvacir_fan_mode = HVACIR_DEF_FAN_MODE_LOW,
    	//uint8_t         hvacir_fan_mode_sequence;	//parametro zigbee che non mi interessa
    	/*.hvacir_horizontal_swing_mode = 
    uint8_t         hvacir_quiet_mode;
    uint8_t         hvacir_sleep_mode;
    uint8_t         hvacir_sys_mode;
    uint8_t         hvacir_last_on_sys_mode;
    uint8_t         hvacir_temperature_view_mode;
    uint8_t         hvacir_timer_mode;
    uint8_t         hvacir_vertical_swing_mode;
    int16_t         hvacir_ambient_heating_setpoint;		//setpoint da usare in caso riscaldamento
    int16_t         hvacir_ambient_heating_setpoint_min;	//non mi serve
    int16_t         hvacir_ambient_heating_setpoint_max;	//non mi serve
    int16_t         hvacir_ambient_cooling_setpoint;		//setpoint da usare in caso raffreddamento e deumidificazione
    int16_t         hvacir_ambient_cooling_setpoint_min;	//non mi serve
    int16_t         hvacir_ambient_cooling_setpoint_max;	//non mi serve
    int16_t         hvacir_sleep3_setpoints[8];
    uint8_t         hvacir_on_timer_duration;
    uint8_t         hvacir_off_timer_duration;
	*/
	};
	
	State localState;
	//PrintState(&localState);
	localState = FromObjToState(&obj);
	PrintState(&localState);
}

void PrintState(State* state)
{
	printf("mode:         %02X\n", state->mode);
	printf("power:        %02X\n", state->power);
	printf("fan:          %02X\n", state->fan);
	printf("swing:        %02X\n", state->swing);
	printf("sleepBitZero: %02X\n", state->sleepBitZero);
	
	printf("temperatura:  %02X\n", state->temperatura);
	printf("wifi:         %02X\n", state->wifi);
	printf("timer:        %02X\n", state->timer);
	
	printf("TBD:          %02X\n", state->TBD);
	printf("turbo:        %02X\n", state->turbo);
	printf("light:        %02X\n", state->light);
	printf("modalitaSanificazione: %02X\n", state->modalitaSanificazione);
	printf("modalitaDepurazione:   %02X\n", state->modalitaDepurazione);
	
	printf("paletteVerticali:   %02X\n", state->paletteVerticali);
	printf("paletteOrizzontali: %02X\n", state->paletteOrizzontali);
	
	printf("temp:             %02X\n", state->temp);
	printf("ifeel:            %02X\n", state->ifeel);
	
	printf("sleepBitUno:      %02X\n", state->sleepBitUno);
	printf("quiet:            %02X\n", state->quiet);
	printf("timer_ON:         %02X\n", state->timer_ON);
	printf("timer_OFF:        %02X\n", state->timer_OFF);
	printf("timer_ON_enable:  %02X\n", state->timer_ON_enable);
	printf("timer_OFF_enable: %02X\n", state->timer_OFF_enable);
	
	printf("sleep_3_ora_1_temperatura: %02X\n", state->sleep_3_ora_1_temperatura);
	printf("sleep_3_ora_2_temperatura: %02X\n", state->sleep_3_ora_2_temperatura);
	printf("fan_ID7: %02X\n", state->fan_ID7);
	
	printf("sleep_3_ora_3_temperatura: %02X\n", state->sleep_3_ora_3_temperatura);
	printf("sleep_3_ora_4_temperatura: %02X\n", state->sleep_3_ora_4_temperatura);
	printf("sleep_3_ora_5_temperatura: %02X\n", state->sleep_3_ora_5_temperatura);
	printf("sleep_3_ora_6_temperatura: %02X\n", state->sleep_3_ora_6_temperatura);
	printf("sleep_3_ora_7_temperatura: %02X\n", state->sleep_3_ora_7_temperatura);
	printf("sleep_3_ora_8_temperatura: %02X\n", state->sleep_3_ora_8_temperatura);
}


void FromAnalysIR2Frame()
{
	//trama ON
	//funziona correttamente girando i bit, ricorda che alla fine il checksum deve essere shiftato di 4 posizioni
	/*int8_t b[]= {0b00110000, 
			     0b11010000,
				 0b00000010,
				 0b00001010,
				 0b00000000,
				 0b00000000,
				 0b00000000
				 };*/
				 
	//trama ON 2
	/*int8_t b[]= {0b00110000, 
			     0b11010000,
				 0b00000010,
				 0b00001110,
				 0b00000000,
				 0b00000000,
				 0b00000000
				 };*/
				 
	//trama del consulente esterno
	//funziona correttamente se NON giri i bit e girando il checksum
	int8_t b[]= {0x00, 
			     0x09,
				 0x20,
				 0x50,
				 0x00,
				 0xC0,
				 0x00
				 };		 
	
	//trama OFF
	/*int8_t b[]= {0b00100000, 
			     0b11010000,
				 0b00000000,
				 0b00001010,
				 0b00000000,
				 0b00000000,
				 0b00000000
				 };	*/
	
				 
	
	int i;
	for(i = 0; i < 7; i++)
		LSB2MSB(&b[i]);
	
	int8_t checksum = ComputeChecksum(b) << 4;
	//LSB2MSB(&checksum);
	
	for(i = 0; i < 7; i++)
		printf("%x\n", b[i]);
		
	printf("checksum = %x\n", checksum);
}

void TestLSB2MSB()
{
	/*int8_t v[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0b, 0x0c , 0x0d, 0x0e, 0x0f};
	int i;
	
	for(i = 0; i < 16; i++)
		printf("%x ", v[i]);
	
	printf("\n");
	
	for(i = 0; i < 16; i++)
		LSB2MSB(&v[i]);

	for(i = 0; i < 16; i++)
		printf("%x ", v[i]);*/
		
	//con i bit forniti da anlysIR non funziona
	int8_t b[]= {0b00110000, 
			     0b11010000,
				 0b00000010,
				 0b00001010,
				 0b00000000,
				 0b00000000,
				 0b00000000
				 };
			
	int i;
	for(i = 0; i < 7; i++)	 
		LSB2MSB(&b[i]);
		
	for(i = 0; i < 7; i++)
		printf("%x\n", b[i]);
}

int8_t* placeholder()
{
	static int8_t c[10];
	int i;
	for(i = 0; i < 10; i++)
		c[i] = 1;
	return c;
}

void size()
{
	printf("uint8_t : %d\n", sizeof(uint8_t));
	printf("uint16_t : %d\n", sizeof(uint16_t));
	printf("uint32_t : %d\n", sizeof(uint32_t));
	printf("int8_t : %d\n", sizeof(int8_t));
	printf("int16_t : %d\n", sizeof(int16_t));
	printf("int32_t : %d\n", sizeof(int32_t));
}

void printAllData()
{
	int i;
	printf("\n");
		
	printf("%d\n", totalFrame[0]);	//preambolo
	
	for(i = 1; i < 1+8; i++)
		printf("%d ", totalFrame[i]);
	
	printf("\n");
	
	for(i = 9; i < 9+8; i++)
		printf("%d ", totalFrame[i]);
	
	printf("\n");
	
	for(i = 17; i < 17+8; i++)
		printf("%d ", totalFrame[i]);
	
	printf("\n");
	
	for(i = 25; i < 25+8; i++)
		printf("%d ", totalFrame[i]);
	
	printf("\n");
	
	printf("%d\n", totalFrame[33]);
	printf("%d\n", totalFrame[34]);
	printf("%d\n", totalFrame[35]);
	printf("%d\n", totalFrame[36]);
	
	for(i = 37; i < 37+8; i++)
		printf("%d ", totalFrame[i]);
	
	printf("\n");
	
	for(i = 45; i < 45+8; i++)
		printf("%d ", totalFrame[i]);
	
	printf("\n");
	
	for(i = 53; i < 53+8; i++)
		printf("%d ", totalFrame[i]);
	
	printf("\n");
	
	for(i = 61; i < 61+8; i++)
		printf("%d ", totalFrame[i]);
	
	printf("\n");
		
	printf("%d\n", totalFrame[69]);	//end
	
}

int8_t ComputeChecksumTest()
{
	//con i bit forniti da anlysIR non funziona
	/*int8_t b[]= {0b00110000, 
			     0b11010000,
				 0b00000010,
				 0b00001010,
				 0b00000000,
				 0b00000000,
				 0b00000000
				 };*/
	
	//occorre considerare i byte sopra come col bit più significativo a dx per farlo funzionare correttamente
	//ricorda che alla fine il checksum va shiftato di 4 posizioni
	int8_t b[]= {0x0C, 
			     0x0B,
			     0x40,
				 0x50,
				 0x00,
				 0x00,
				 0x00,
				 };
	
				 
	int8_t cks = (int8_t)((0x0A + (b[0] & 0x0F) + (b[1] & 0x0F) + (b[2] & 0x0F) + (b[3] & 0x0F) + ((b[4] & 0xF0) >> 4) + ((b[5] & 0xF0) >> 4) + ((b[6] & 0xF0) >> 4)) & 0x0F); 
	printf("%x", cks);
	return cks;
}

void ComparazioneMisure()
{
	int signal_off[10][279] = {
								{8984,4492,636,1670,604,604,604,604,604,604,636,1670,604,604,604,604,604,604,636,1670,604,604,604,604,636,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1670,604,604,604,604,604,604,604,604,604,604,604,604,636,1670,604,604,636,1670,604,604,604,604,636,1670,604,604,642,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1670,604,604,636,40012,8984,4492,636,1670,604,604,604,604,604,604,636,1670,604,604,604,604,604,604,636,1670,604,604,604,604,636,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1670,604,604,604,604,604,604,604,604,604,604,604,604,636,1670,636,1670,636,1670,604,604,604,604,636,1670,604,604,642,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1670,604,604,636,1670,604,604,636}, //AnalysIR Batch Export (IRremote) - RAW
							    {8984,4492,638,1670,640,568,640,568,640,568,638,1670,640,568,640,568,640,568,638,1670,640,568,640,568,638,1670,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,638,1670,640,568,640,568,640,568,640,568,640,568,640,568,638,1670,640,568,638,1670,640,568,640,568,638,1670,640,568,636,20000,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,638,1670,640,568,636,40012,8984,4492,638,1670,640,568,640,568,640,568,638,1670,640,568,640,568,640,568,638,1670,640,568,640,568,638,1670,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,638,1670,640,568,640,568,640,568,640,568,640,568,640,568,638,1670,638,1670,638,1670,640,568,640,568,638,1670,640,568,636,20000,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,638,1670,640,568,640,568,640,568,640,568,640,568,640,568,640,568,638,1670,640,568,638,1670,640,568,638}, //AnalysIR Batch Export (IRremote) - RAW
							    {8988,4492,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,638,1670,604,604,604,604,638,1670,604,604,636,19996,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,640,40012,8988,4492,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,638,1670,638,1670,604,604,604,604,638,1670,604,604,636,19996,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,638,1670,604,604,638}, //AnalysIR Batch Export (IRremote) - RAW
							    {8988,4492,640,1670,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,640,1670,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,640,1670,602,602,602,602,640,1670,602,602,638,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,640,40012,8988,4492,640,1670,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,640,1670,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,640,1670,640,1670,602,602,602,602,640,1670,602,602,638,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,640,1670,602,602,640}, //AnalysIR Batch Export (IRremote) - RAW
							    {8984,4492,638,1666,604,604,604,604,604,604,638,1666,604,604,604,604,604,604,638,1666,604,604,604,604,638,1666,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1666,604,604,604,604,604,604,604,604,604,604,604,604,638,1666,604,604,638,1666,604,604,604,604,638,1666,604,604,642,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1666,604,604,636,40008,8984,4492,638,1666,604,604,604,604,604,604,638,1666,604,604,604,604,604,604,638,1666,604,604,604,604,638,1666,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1666,604,604,604,604,604,604,604,604,604,604,604,604,638,1666,638,1666,638,1666,604,604,604,604,638,1666,604,604,642,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1666,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1666,604,604,638,1666,604,604,638}, //AnalysIR Batch Export (IRremote) - RAW
							    {8988,4492,640,1670,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,640,1670,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,640,1670,602,602,602,602,640,1670,602,602,638,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,640,40012,8988,4492,640,1670,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,640,1670,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,640,1670,640,1670,602,602,602,602,640,1670,602,602,638,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,640,1670,602,602,640}, //AnalysIR Batch Export (IRremote) - RAW
							    {8990,4494,638,1670,602,602,602,602,602,602,638,1670,602,602,602,602,602,602,638,1670,602,602,602,602,638,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,602,602,638,1670,602,602,602,602,638,1670,602,602,634,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,602,602,636,40008,8990,4494,638,1670,602,602,602,602,602,602,638,1670,602,602,602,602,602,602,638,1670,602,602,602,602,638,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,638,1670,638,1670,602,602,602,602,638,1670,602,602,634,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,602,602,638,1670,602,602,638}, //AnalysIR Batch Export (IRremote) - RAW
							    {8988,4492,636,1674,602,602,602,602,602,602,636,1674,602,602,602,602,602,602,636,1674,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,636,1674,602,602,602,602,636,1674,602,602,632,20004,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,636,40012,8988,4492,636,1674,602,602,602,602,602,602,636,1674,602,602,602,602,602,602,636,1674,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,636,1674,636,1674,602,602,602,602,636,1674,602,602,632,20004,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,636,1674,602,602,636}, //AnalysIR Batch Export (IRremote) - RAW
							    {8984,4492,636,1672,604,604,604,604,604,604,636,1672,604,604,604,604,604,604,636,1672,604,604,604,604,636,1672,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1672,604,604,604,604,604,604,604,604,604,604,604,604,636,1672,604,604,636,1672,604,604,604,604,636,1672,604,604,634,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1672,604,604,636,40016,8984,4492,636,1672,604,604,604,604,604,604,636,1672,604,604,604,604,604,604,636,1672,604,604,604,604,636,1672,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1672,604,604,604,604,604,604,604,604,604,604,604,604,636,1672,636,1672,636,1672,604,604,604,604,636,1672,604,604,634,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1672,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1672,604,604,636,1672,604,604,636}, //AnalysIR Batch Export (IRremote) - RAW
							    {8988,4492,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,638,1670,604,604,604,604,638,1670,604,604,634,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,636,40008,8988,4492,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,638,1670,638,1670,604,604,604,604,638,1670,604,604,634,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,638,1670,604,604,638}, //AnalysIR Batch Export (IRremote) - RAW
						  	}	;			
	
	unsigned int Signal_off_0[] = {8984,4492,636,1670,604,604,604,604,604,604,636,1670,604,604,604,604,604,604,636,1670,604,604,604,604,636,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1670,604,604,604,604,604,604,604,604,604,604,604,604,636,1670,604,604,636,1670,604,604,604,604,636,1670,604,604,642,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1670,604,604,636,40012,8984,4492,636,1670,604,604,604,604,604,604,636,1670,604,604,604,604,604,604,636,1670,604,604,604,604,636,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1670,604,604,604,604,604,604,604,604,604,604,604,604,636,1670,636,1670,636,1670,604,604,604,604,636,1670,604,604,642,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1670,604,604,636,1670,604,604,636}; //AnalysIR Batch Export (IRremote) - RAW
    unsigned int Signal_off_2[] = {8984,4492,638,1670,640,568,640,568,640,568,638,1670,640,568,640,568,640,568,638,1670,640,568,640,568,638,1670,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,638,1670,640,568,640,568,640,568,640,568,640,568,640,568,638,1670,640,568,638,1670,640,568,640,568,638,1670,640,568,636,20000,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,638,1670,640,568,636,40012,8984,4492,638,1670,640,568,640,568,640,568,638,1670,640,568,640,568,640,568,638,1670,640,568,640,568,638,1670,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,638,1670,640,568,640,568,640,568,640,568,640,568,640,568,638,1670,638,1670,638,1670,640,568,640,568,638,1670,640,568,636,20000,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,640,568,638,1670,640,568,640,568,640,568,640,568,640,568,640,568,640,568,638,1670,640,568,638,1670,640,568,638}; //AnalysIR Batch Export (IRremote) - RAW
    unsigned int Signal_off_4[] = {8988,4492,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,638,1670,604,604,604,604,638,1670,604,604,636,19996,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,640,40012,8988,4492,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,638,1670,638,1670,604,604,604,604,638,1670,604,604,636,19996,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,638,1670,604,604,638}; //AnalysIR Batch Export (IRremote) - RAW
    unsigned int Signal_off_6[] = {8988,4492,640,1670,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,640,1670,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,640,1670,602,602,602,602,640,1670,602,602,638,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,640,40012,8988,4492,640,1670,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,640,1670,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,640,1670,640,1670,602,602,602,602,640,1670,602,602,638,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,640,1670,602,602,640}; //AnalysIR Batch Export (IRremote) - RAW
    unsigned int Signal_off_8[] = {8984,4492,638,1666,604,604,604,604,604,604,638,1666,604,604,604,604,604,604,638,1666,604,604,604,604,638,1666,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1666,604,604,604,604,604,604,604,604,604,604,604,604,638,1666,604,604,638,1666,604,604,604,604,638,1666,604,604,642,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1666,604,604,636,40008,8984,4492,638,1666,604,604,604,604,604,604,638,1666,604,604,604,604,604,604,638,1666,604,604,604,604,638,1666,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1666,604,604,604,604,604,604,604,604,604,604,604,604,638,1666,638,1666,638,1666,604,604,604,604,638,1666,604,604,642,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1666,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1666,604,604,638,1666,604,604,638}; //AnalysIR Batch Export (IRremote) - RAW
    unsigned int Signal_off_10[] = {8988,4492,640,1670,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,640,1670,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,640,1670,602,602,602,602,640,1670,602,602,638,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,640,40012,8988,4492,640,1670,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,640,1670,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,640,1670,640,1670,602,602,602,602,640,1670,602,602,638,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,640,1670,602,602,640}; //AnalysIR Batch Export (IRremote) - RAW
    unsigned int Signal_off_12[] = {8990,4494,638,1670,602,602,602,602,602,602,638,1670,602,602,602,602,602,602,638,1670,602,602,602,602,638,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,602,602,638,1670,602,602,602,602,638,1670,602,602,634,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,602,602,636,40008,8990,4494,638,1670,602,602,602,602,602,602,638,1670,602,602,602,602,602,602,638,1670,602,602,602,602,638,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,638,1670,638,1670,602,602,602,602,638,1670,602,602,634,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,602,602,638,1670,602,602,638}; //AnalysIR Batch Export (IRremote) - RAW
    unsigned int Signal_off_14[] = {8988,4492,636,1674,602,602,602,602,602,602,636,1674,602,602,602,602,602,602,636,1674,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,636,1674,602,602,602,602,636,1674,602,602,632,20004,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,636,40012,8988,4492,636,1674,602,602,602,602,602,602,636,1674,602,602,602,602,602,602,636,1674,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,636,1674,636,1674,602,602,602,602,636,1674,602,602,632,20004,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,636,1674,602,602,636}; //AnalysIR Batch Export (IRremote) - RAW
    unsigned int Signal_off_16[] = {8984,4492,636,1672,604,604,604,604,604,604,636,1672,604,604,604,604,604,604,636,1672,604,604,604,604,636,1672,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1672,604,604,604,604,604,604,604,604,604,604,604,604,636,1672,604,604,636,1672,604,604,604,604,636,1672,604,604,634,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1672,604,604,636,40016,8984,4492,636,1672,604,604,604,604,604,604,636,1672,604,604,604,604,604,604,636,1672,604,604,604,604,636,1672,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1672,604,604,604,604,604,604,604,604,604,604,604,604,636,1672,636,1672,636,1672,604,604,604,604,636,1672,604,604,634,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1672,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1672,604,604,636,1672,604,604,636}; //AnalysIR Batch Export (IRremote) - RAW
    unsigned int Signal_off_18[] = {8988,4492,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,638,1670,604,604,604,604,638,1670,604,604,634,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,636,40008,8988,4492,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,638,1670,638,1670,604,604,604,604,638,1670,604,604,634,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,638,1670,604,604,638}; //AnalysIR Batch Export (IRremote) - RAW

	int signal_on[10][279] = {
								{8988,4492,642,1670,604,604,604,604,642,1670,642,1670,604,604,604,604,604,604,642,1670,604,604,604,604,642,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1670,642,1670,604,604,604,604,604,604,604,604,604,604,642,1670,604,604,642,1670,604,604,604,604,642,1670,604,604,638,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1670,642,1670,640,40012,8988,4492,642,1670,604,604,604,604,642,1670,642,1670,604,604,604,604,604,604,642,1670,604,604,604,604,642,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1670,642,1670,604,604,604,604,604,604,604,604,604,604,642,1670,642,1670,642,1670,604,604,604,604,642,1670,604,604,638,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1670,604,604,642,1670,642,1670,642}, //AnalysIR Batch Export (IRremote) - RAW
							    {8988,4492,640,1670,604,604,604,604,640,1670,640,1670,604,604,604,604,604,604,640,1670,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,640,1670,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,640,1670,604,604,604,604,640,1670,604,604,642,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,640,1670,636,40012,8988,4492,640,1670,604,604,604,604,640,1670,640,1670,604,604,604,604,604,604,640,1670,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,640,1670,604,604,604,604,604,604,604,604,604,604,640,1670,640,1670,640,1670,604,604,604,604,640,1670,604,604,642,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,640,1670,640,1670,640}, //AnalysIR Batch Export (IRremote) - RAW
							    {8984,4492,642,1666,604,604,604,604,642,1666,642,1666,604,604,604,604,604,604,642,1666,604,604,604,604,642,1666,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1666,642,1666,604,604,604,604,604,604,604,604,604,604,642,1666,604,604,642,1666,604,604,604,604,642,1666,604,604,638,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1666,642,1666,636,40008,8984,4492,642,1666,604,604,604,604,642,1666,642,1666,604,604,604,604,604,604,642,1666,604,604,604,604,642,1666,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1666,642,1666,604,604,604,604,604,604,604,604,604,604,642,1666,642,1666,642,1666,604,604,604,604,642,1666,604,604,638,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1666,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1666,604,604,642,1666,642,1666,642}, //AnalysIR Batch Export (IRremote) - RAW
						        {8988,4492,638,1670,604,604,604,604,638,1670,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,638,1670,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,638,1670,604,604,604,604,638,1670,604,604,634,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,638,1670,640,40008,8988,4492,638,1670,604,604,604,604,638,1670,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,638,1670,604,604,604,604,604,604,604,604,604,604,638,1670,638,1670,638,1670,604,604,604,604,638,1670,604,604,634,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,638,1670,638,1670,638}, //AnalysIR Batch Export (IRremote) - RAW
							    {8988,4492,640,1668,644,568,644,568,640,1668,640,1668,644,568,644,568,644,568,640,1668,644,568,644,568,640,1668,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,640,1668,640,1668,644,568,644,568,644,568,644,568,644,568,640,1668,644,568,640,1668,644,568,644,568,640,1668,644,568,640,20000,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,640,1668,640,1668,640,40016,8988,4492,640,1668,644,568,644,568,640,1668,640,1668,644,568,644,568,644,568,640,1668,644,568,644,568,640,1668,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,640,1668,640,1668,644,568,644,568,644,568,644,568,644,568,640,1668,640,1668,640,1668,644,568,644,568,640,1668,644,568,640,20000,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,640,1668,644,568,644,568,644,568,644,568,644,568,644,568,644,568,640,1668,644,568,640,1668,640,1668,640},//AnalysIR Batch Export (IRremote) - RAW
						        {8988,4492,636,1674,602,602,602,602,636,1674,636,1674,602,602,602,602,602,602,636,1674,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,636,1674,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,636,1674,602,602,602,602,636,1674,602,602,638,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,636,1674,636,40012,8988,4492,636,1674,602,602,602,602,636,1674,636,1674,602,602,602,602,602,602,636,1674,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,636,1674,602,602,602,602,602,602,602,602,602,602,636,1674,636,1674,636,1674,602,602,602,602,636,1674,602,602,638,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,636,1674,636,1674,636}, //AnalysIR Batch Export (IRremote) - RAW
							    {8988,4492,638,1672,604,604,604,604,638,1672,638,1672,604,604,604,604,604,604,638,1672,604,604,604,604,638,1672,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1672,638,1672,604,604,604,604,604,604,604,604,604,604,638,1672,604,604,638,1672,604,604,604,604,638,1672,604,604,636,20000,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1672,638,1672,636,40008,8988,4492,638,1672,604,604,604,604,638,1672,638,1672,604,604,604,604,604,604,638,1672,604,604,604,604,638,1672,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1672,638,1672,604,604,604,604,604,604,604,604,604,604,638,1672,638,1672,638,1672,604,604,604,604,638,1672,604,604,636,20000,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1672,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1672,604,604,638,1672,638,1672,638}, //AnalysIR Batch Export (IRremote) - RAW
						        {8990,4494,634,1674,604,604,604,604,634,1674,634,1674,604,604,604,604,604,604,634,1674,604,604,604,604,634,1674,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,634,1674,634,1674,604,604,604,604,604,604,604,604,604,604,634,1674,604,604,634,1674,604,604,604,604,634,1674,604,604,634,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,634,1674,634,1674,636,40012,8990,4494,634,1674,604,604,604,604,634,1674,634,1674,604,604,604,604,604,604,634,1674,604,604,604,604,634,1674,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,634,1674,634,1674,604,604,604,604,604,604,604,604,604,604,634,1674,634,1674,634,1674,604,604,604,604,634,1674,604,604,634,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,634,1674,604,604,604,604,604,604,604,604,604,604,604,604,604,604,634,1674,604,604,634,1674,634,1674,634}, //AnalysIR Batch Export (IRremote) - RAW
						        {8988,4492,638,1670,602,602,602,602,638,1670,638,1670,602,602,602,602,602,602,638,1670,602,602,602,602,638,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,638,1670,602,602,602,602,602,602,602,602,602,602,638,1670,602,602,638,1670,602,602,602,602,638,1670,602,602,642,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,638,1670,640,40016,8988,4492,638,1670,602,602,602,602,638,1670,638,1670,602,602,602,602,602,602,638,1670,602,602,602,602,638,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,638,1670,602,602,602,602,602,602,602,602,602,602,638,1670,638,1670,638,1670,602,602,602,602,638,1670,602,602,642,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,602,602,638,1670,638,1670,638}, //AnalysIR Batch Export (IRremote) - RAW
						        {8988,4492,642,1666,642,570,642,570,642,1666,642,1666,642,570,642,570,642,570,642,1666,642,570,642,570,642,1666,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,1666,642,1666,642,570,642,570,642,570,642,570,642,570,642,1666,642,570,642,1666,642,570,642,570,642,1666,642,570,638,19994,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,1666,642,1666,640,40004,8988,4492,642,1666,642,570,642,570,642,1666,642,1666,642,570,642,570,642,570,642,1666,642,570,642,570,642,1666,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,1666,642,1666,642,570,642,570,642,570,642,570,642,570,642,1666,642,1666,642,1666,642,570,642,570,642,1666,642,570,638,19994,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,1666,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,1666,642,570,642,1666,642,1666,642}, //AnalysIR Batch Export (IRremote) - RAW
							};

    unsigned int Signal_on_1[] = {8988,4492,642,1670,604,604,604,604,642,1670,642,1670,604,604,604,604,604,604,642,1670,604,604,604,604,642,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1670,642,1670,604,604,604,604,604,604,604,604,604,604,642,1670,604,604,642,1670,604,604,604,604,642,1670,604,604,638,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1670,642,1670,640,40012,8988,4492,642,1670,604,604,604,604,642,1670,642,1670,604,604,604,604,604,604,642,1670,604,604,604,604,642,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1670,642,1670,604,604,604,604,604,604,604,604,604,604,642,1670,642,1670,642,1670,604,604,604,604,642,1670,604,604,638,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1670,604,604,642,1670,642,1670,642}; //AnalysIR Batch Export (IRremote) - RAW
    unsigned int Signal_on_3[] = {8988,4492,640,1670,604,604,604,604,640,1670,640,1670,604,604,604,604,604,604,640,1670,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,640,1670,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,640,1670,604,604,604,604,640,1670,604,604,642,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,640,1670,636,40012,8988,4492,640,1670,604,604,604,604,640,1670,640,1670,604,604,604,604,604,604,640,1670,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,640,1670,604,604,604,604,604,604,604,604,604,604,640,1670,640,1670,640,1670,604,604,604,604,640,1670,604,604,642,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,640,1670,640,1670,640}; //AnalysIR Batch Export (IRremote) - RAW
    unsigned int Signal_on_5[] = {8984,4492,642,1666,604,604,604,604,642,1666,642,1666,604,604,604,604,604,604,642,1666,604,604,604,604,642,1666,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1666,642,1666,604,604,604,604,604,604,604,604,604,604,642,1666,604,604,642,1666,604,604,604,604,642,1666,604,604,638,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1666,642,1666,636,40008,8984,4492,642,1666,604,604,604,604,642,1666,642,1666,604,604,604,604,604,604,642,1666,604,604,604,604,642,1666,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1666,642,1666,604,604,604,604,604,604,604,604,604,604,642,1666,642,1666,642,1666,604,604,604,604,642,1666,604,604,638,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1666,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1666,604,604,642,1666,642,1666,642}; //AnalysIR Batch Export (IRremote) - RAW
    unsigned int Signal_on_7[] = {8988,4492,638,1670,604,604,604,604,638,1670,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,638,1670,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,638,1670,604,604,604,604,638,1670,604,604,634,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,638,1670,640,40008,8988,4492,638,1670,604,604,604,604,638,1670,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,638,1670,604,604,604,604,604,604,604,604,604,604,638,1670,638,1670,638,1670,604,604,604,604,638,1670,604,604,634,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,638,1670,638,1670,638}; //AnalysIR Batch Export (IRremote) - RAW
    unsigned int Signal_on_9[] = {8988,4492,640,1668,644,568,644,568,640,1668,640,1668,644,568,644,568,644,568,640,1668,644,568,644,568,640,1668,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,640,1668,640,1668,644,568,644,568,644,568,644,568,644,568,640,1668,644,568,640,1668,644,568,644,568,640,1668,644,568,640,20000,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,640,1668,640,1668,640,40016,8988,4492,640,1668,644,568,644,568,640,1668,640,1668,644,568,644,568,644,568,640,1668,644,568,644,568,640,1668,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,640,1668,640,1668,644,568,644,568,644,568,644,568,644,568,640,1668,640,1668,640,1668,644,568,644,568,640,1668,644,568,640,20000,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,644,568,640,1668,644,568,644,568,644,568,644,568,644,568,644,568,644,568,640,1668,644,568,640,1668,640,1668,640}; //AnalysIR Batch Export (IRremote) - RAW
    unsigned int Signal_on_11[] = {8988,4492,636,1674,602,602,602,602,636,1674,636,1674,602,602,602,602,602,602,636,1674,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,636,1674,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,636,1674,602,602,602,602,636,1674,602,602,638,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,636,1674,636,40012,8988,4492,636,1674,602,602,602,602,636,1674,636,1674,602,602,602,602,602,602,636,1674,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,636,1674,602,602,602,602,602,602,602,602,602,602,636,1674,636,1674,636,1674,602,602,602,602,636,1674,602,602,638,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,636,1674,636,1674,636}; //AnalysIR Batch Export (IRremote) - RAW
    unsigned int Signal_on_13[] = {8988,4492,638,1672,604,604,604,604,638,1672,638,1672,604,604,604,604,604,604,638,1672,604,604,604,604,638,1672,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1672,638,1672,604,604,604,604,604,604,604,604,604,604,638,1672,604,604,638,1672,604,604,604,604,638,1672,604,604,636,20000,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1672,638,1672,636,40008,8988,4492,638,1672,604,604,604,604,638,1672,638,1672,604,604,604,604,604,604,638,1672,604,604,604,604,638,1672,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1672,638,1672,604,604,604,604,604,604,604,604,604,604,638,1672,638,1672,638,1672,604,604,604,604,638,1672,604,604,636,20000,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1672,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1672,604,604,638,1672,638,1672,638}; //AnalysIR Batch Export (IRremote) - RAW
    unsigned int Signal_on_15[] = {8990,4494,634,1674,604,604,604,604,634,1674,634,1674,604,604,604,604,604,604,634,1674,604,604,604,604,634,1674,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,634,1674,634,1674,604,604,604,604,604,604,604,604,604,604,634,1674,604,604,634,1674,604,604,604,604,634,1674,604,604,634,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,634,1674,634,1674,636,40012,8990,4494,634,1674,604,604,604,604,634,1674,634,1674,604,604,604,604,604,604,634,1674,604,604,604,604,634,1674,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,634,1674,634,1674,604,604,604,604,604,604,604,604,604,604,634,1674,634,1674,634,1674,604,604,604,604,634,1674,604,604,634,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,634,1674,604,604,604,604,604,604,604,604,604,604,604,604,604,604,634,1674,604,604,634,1674,634,1674,634}; //AnalysIR Batch Export (IRremote) - RAW
    unsigned int Signal_on_17[] = {8988,4492,638,1670,602,602,602,602,638,1670,638,1670,602,602,602,602,602,602,638,1670,602,602,602,602,638,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,638,1670,602,602,602,602,602,602,602,602,602,602,638,1670,602,602,638,1670,602,602,602,602,638,1670,602,602,642,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,638,1670,640,40016,8988,4492,638,1670,602,602,602,602,638,1670,638,1670,602,602,602,602,602,602,638,1670,602,602,602,602,638,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,638,1670,602,602,602,602,602,602,602,602,602,602,638,1670,638,1670,638,1670,602,602,602,602,638,1670,602,602,642,20002,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,638,1670,602,602,638,1670,638,1670,638}; //AnalysIR Batch Export (IRremote) - RAW
    unsigned int Signal_on_19[] = {8988,4492,642,1666,642,570,642,570,642,1666,642,1666,642,570,642,570,642,570,642,1666,642,570,642,570,642,1666,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,1666,642,1666,642,570,642,570,642,570,642,570,642,570,642,1666,642,570,642,1666,642,570,642,570,642,1666,642,570,638,19994,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,1666,642,1666,640,40004,8988,4492,642,1666,642,570,642,570,642,1666,642,1666,642,570,642,570,642,570,642,1666,642,570,642,570,642,1666,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,1666,642,1666,642,570,642,570,642,570,642,570,642,570,642,1666,642,1666,642,1666,642,570,642,570,642,1666,642,570,638,19994,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,1666,642,570,642,570,642,570,642,570,642,570,642,570,642,570,642,1666,642,570,642,1666,642,1666,642}; //AnalysIR Batch Export (IRremote) - RAW

	int sizeOFF = sizeof(Signal_off_0)/sizeof(int);
    int sizeON = sizeof(Signal_on_1)/sizeof(int);
    
    printf("%d\r\n", sizeOFF);
    printf("%d\r\n", sizeON);
    
    int cnt;
    int min = 0;
    int max = 0;
    int delta = 0;
    int sample = 0;
    
    /*
    per ogniuno dei 10 messaggi presi tramite analysIR, controllo la durata dei segnali alto e basso in ogni posizione.
    mi salvo localmente il massimo e il minimo di questi, e alla fine mostro la differenza per ogniuno di questi intervalli
    scopo della funzione è controllare quanto grande può essere la differenza temporale tra un dato e un altro, per capire 
    quanto possono essere "errati" i segnali rispetto allo standard e nonostante questo essere ricevuti correttamente
    */
    
    for(cnt = 0; cnt < sizeOFF; cnt++)
	{
		min = 0;
		max = 0;
		for(sample = 0; sample < 10; sample++)
	    {
	    	if(min == 0)	
	    		min = signal_off[sample][cnt];
	    		
	    	if(max == 0)	
	    		max = signal_off[sample][cnt];
	    		
	    	if(signal_off[sample][cnt] < min)
	    		min = signal_off[sample][cnt];
	    		
	    	if(signal_off[sample][cnt] > max)
	    		max = signal_off[sample][cnt];
		}
		printf("%d\r\n", max - min);
	}
    
}


#define ASTRELBSP_DEF_PREAMBLE_ON_TIME_US                9000
#define ASTRELBSP_DEF_PREAMBLE_OFF_TIME_US               4500
#define ASTRELBSP_DEF_BIT_ON_TIME_US                      600
#define ASTRELBSP_DEF_BIT0_OFF_TIME_US                    600
#define ASTRELBSP_DEF_BIT1_OFF_TIME_US                   1610
#define ASTRELBSP_DEF_PAUSE_TIME_US                     20000
#define ASTRELBSP_DEF_END_TIME_US                       40000

//fornito un frame proveniente da analysIR, lo converte in una sequenza leggibile
void ConvertFromAnalysIR()
{
	//uint8_t v[] = {8988,4492,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,638,1670,638,1670,604,604,604,604,638,1670,638,1670,604,604,604,604,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,638,1670,604,604,604,604,638,1670,604,604,638,20006,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,40012,8988,4492,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,638,1670,638,1670,604,604,604,604,638,1670,638,1670,604,604,604,604,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,638,1670,604,604,604,604,638,1670,604,604,638,20006,604,604,638,1670,604,604,638,1670,638,1670,604,604,604,604,638,1670,604,604,604,604,638,1670,638,1670,604,604,604,604,638,1670,604,604,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,638,1670,638,1670,604,604,604,604,604,604,638,1670,638,1670,638,1670,636,40012,8988,4492,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,638,1670,638,1670,604,604,604,604,638,1670,638,1670,604,604,604,604,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,638,1670,638,1670,638,1670,604,604,604,604,638,1670,604,604,638,20006,638,1670,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,638,1670,604,604,604,604,638,1670,604,604,638,1670,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,638,1670,638,1670,636,40012,8988,4492,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,638,1670,638,1670,604,604,604,604,638,1670,638,1670,604,604,604,604,638,1670,604,604,604,604,638,1670,604,604,604,604,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638,1670,604,604,638,1670,604,604,638,20006,638,1670,638,1670,604,604,638,1670,638,1670,638,1670,604,604,638,1670,638,1670,638,1670,604,604,638,1670,638,1670,638,1670,604,604,638,1670,638,1670,638,1670,604,604,638,1670,604,604,638,1670,604,604,638,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,638}; //AnalysIR Batch Export (IRremote) - RAW
	
	//TIMER OFF
	//uint8_t v[] = {8988,4492,640,1670,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,640,1670,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,640,1670,602,602,602,602,640,1670,602,602,642,19998,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,640,1670,636,40008,8988,4492,640,1670,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,640,1670,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,602,602,602,602,602,602,602,602,602,602,640,1670,640,1670,640,1670,602,602,602,602,640,1670,602,602,642,19998,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,640,1670,640,1670,640}; //AnalysIR Batch Export (IRremote) - RAW

	//TIMER ON	
	//uint8_t v[] = {8990,4494,640,1670,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,640,1670,604,604,604,604,640,1670,640,1670,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,640,1670,604,604,604,604,640,1670,604,604,642,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,640,1670,640,40008,8990,4494,640,1670,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,640,1670,604,604,604,604,640,1670,640,1670,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,640,1670,604,604,604,604,640,1670,604,604,642,19998,640,1670,640,1670,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,604,604,640,1670,604,604,640,1670,640,1670,640,40008,8990,4494,640,1670,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,640,1670,604,604,604,604,640,1670,640,1670,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,640,1670,640,1670,640,1670,604,604,604,604,640,1670,604,604,642,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,640,1670,640}; //AnalysIR Batch Export (IRremote) - RAW

	//sleep 3	
    //uint8_t v[] = {8988,4492,640,1668,638,566,638,566,640,1668,638,566,638,566,638,566,640,1668,640,1668,638,566,638,566,640,1668,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,640,1668,638,566,638,566,638,566,638,566,638,566,640,1668,638,566,640,1668,638,566,638,566,640,1668,638,566,640,20000,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,640,1668,640,1668,640,40012,8988,4492,640,1668,638,566,638,566,640,1668,638,566,638,566,638,566,640,1668,640,1668,638,566,638,566,640,1668,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,640,1668,638,566,638,566,638,566,638,566,638,566,640,1668,640,1668,640,1668,638,566,638,566,640,1668,638,566,640,20000,640,1668,638,566,638,566,638,566,638,566,638,566,640,1668,638,566,640,1668,638,566,638,566,640,1668,638,566,640,1668,638,566,640,1668,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,640,1668,638,566,640,1668,640,40012,8988,4492,640,1668,638,566,638,566,640,1668,638,566,638,566,638,566,640,1668,640,1668,638,566,638,566,640,1668,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,640,1668,638,566,638,566,638,566,638,566,638,566,638,566,638,566,638,566,640,1668,638,566,640,1668,638,566,640,20000,640,1668,640,1668,638,566,640,1668,640,1668,640,1668,638,566,640,1668,640,1668,640,1668,638,566,640,1668,640,1668,640,1668,638,566,640,1668,640,1668,640,1668,638,566,640,1668,638,566,640,1668,638,566,640,1668,638,566,638,566,638,566,638,566,638,566,638,566,640,1668,640,1668,640}; //AnalysIR Batch Export (IRremote) - RAW

	//sanificazione / depurazione
	//uint8_t v[] = {8988,4492,642,1666,604,604,604,604,642,1666,642,1666,604,604,604,604,604,604,642,1666,604,604,604,604,642,1666,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1666,604,604,642,1666,604,604,604,604,642,1666,604,604,638,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1666,642,1666,640,40012,8988,4492,642,1666,604,604,604,604,642,1666,642,1666,604,604,604,604,604,604,642,1666,604,604,604,604,642,1666,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1666,642,1666,642,1666,604,604,604,604,642,1666,604,604,638,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1666,604,604,604,604,604,604,604,604,604,604,604,604,604,604,642,1666,604,604,642,1666,642,1666,642}; //AnalysIR Batch Export (IRremote) - RAW
	uint8_t v[] = {8988,4492,640,1670,604,604,604,604,640,1670,640,1670,604,604,604,604,604,604,640,1670,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,640,1670,604,604,604,604,604,604,640,1670,604,604,640,1670,604,604,604,604,640,1670,604,604,638,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,640,1670,640,1670,636,40012,8988,4492,640,1670,604,604,604,604,640,1670,640,1670,604,604,604,604,604,604,640,1670,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,640,1670,604,604,604,604,604,604,640,1670,640,1670,640,1670,604,604,604,604,640,1670,604,604,638,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,640,1670,640,1670,640}; //AnalysIR Batch Export (IRremote) - RAW
	//uint8_t v[] = {8988,4492,636,1674,604,604,604,604,636,1674,636,1674,604,604,604,604,604,604,636,1674,604,604,604,604,636,1674,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1674,604,604,604,604,604,604,636,1674,604,604,636,1674,604,604,604,604,636,1674,604,604,638,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1674,604,604,636,1674,636,1674,636,40012,8988,4492,636,1674,604,604,604,604,636,1674,636,1674,604,604,604,604,604,604,636,1674,604,604,604,604,636,1674,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1674,604,604,604,604,604,604,636,1674,636,1674,636,1674,604,604,604,604,636,1674,604,604,638,20002,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1674,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,636,1674,636,1674,636,1674,636}; //AnalysIR Batch Export (IRremote) - RAW
	//uint8_t v[] = {8988,4492,636,1674,602,602,602,602,636,1674,636,1674,602,602,602,602,602,602,636,1674,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,636,1674,602,602,602,602,636,1674,602,602,636,20004,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,636,1674,636,40008,8988,4492,636,1674,602,602,602,602,636,1674,636,1674,602,602,602,602,602,602,636,1674,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,636,1674,636,1674,636,1674,602,602,602,602,636,1674,602,602,636,20004,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,602,602,602,602,602,602,602,602,602,602,602,602,636,1674,602,602,636,1674,636,1674,636}; //AnalysIR Batch Export (IRremote) - RAW



	int i;
	int cnt = 0;
	int size = sizeof(v) / sizeof(uint8_t);
	printf("size = %d\n", size);
	
	int DATASIZE = size / 2;
	int8_t data[DATASIZE];
	for(i = 0; i < DATASIZE; i++)
		data[i] = -1;
	
	for(i = 0; i < size; i+=2)
	{
		if(i >= size-1)
			break;
		
		/*if(i == 556)
		{
			int a = 1;
		}*/
		
		if(IsPreamble(&v[i]))
		{
			data[cnt++] = 3;
		}
		
		else if(IsOne(&v[i]))
		{
			data[cnt++] = 1;
		}
		
		else if(IsZero(&v[i]))
		{
			data[cnt++] = 0;
		}
		else if(IsPause(&v[i]))
		{
			data[cnt++] = 4;
		}
		else if(IsEnd(&v[i]))
		{
			data[cnt++] = 5;
		}
		else
		{
			printf("ERRORE");
			return;
		}
		//printf("%d\n", i);
	}
	
	//for(i = i; i < DATASIZE; i++)
	//	printf("%d: %d \n", i, data[i]);
	
	for(i = i; i < DATASIZE; i++)
		if(data[i] == -1)
		{
			printf("carattere non riconosciuto");
			return;
		}
	
	printMyArray(data);
	printf("\n");
	printMyArray(&data[70]);
	printf("\n");
	printMyArray(&data[140]);
	printf("\n");
	printMyArray(&data[210]);	
}


void ConvertFromAnalysIRUsingFile()
{
	FILE *fp = NULL;
	int c;
	uint8_t v[500];
	int dataCnt = 0;
	
	fp = fopen("data.txt", "r");
		
	if(fp == NULL)
	{
		printf("non ho trovato il file data.txt\n");
		return;
	}
	
	int a;
	
	int retVal = 0;
	
	while(retVal != -1)
	{
		retVal = fscanf(fp, "%d%c", &v[dataCnt], &c);
		dataCnt++;
	}
	
	fclose(fp);
	
	//uint8_t v[] = {8988,4492,640,1670,604,604,604,604,640,1670,640,1670,604,604,604,604,604,604,640,1670,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,640,1670,604,604,604,604,604,604,640,1670,604,604,640,1670,604,604,604,604,640,1670,604,604,638,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,640,1670,640,1670,636,40012,8988,4492,640,1670,604,604,604,604,640,1670,640,1670,604,604,604,604,604,604,640,1670,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,640,1670,604,604,604,604,604,604,640,1670,640,1670,640,1670,604,604,604,604,640,1670,604,604,638,19998,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,640,1670,640,1670,640,1670,640}; //AnalysIR Batch Export (IRremote) - RAW
	
	int i;
	int cnt = 0;
	int size = dataCnt - 1;
	//int size = sizeof(v) / sizeof(uint8_t);
	printf("size = %d\n", size);
	
	int DATASIZE = size / 2;
	int8_t data[DATASIZE];
	for(i = 0; i < DATASIZE; i++)
		data[i] = -1;
	
	for(i = 0; i < size; i+=2)
	{
		if(i >= size-1)
			break;
		
		if(i == 276) 
		{
			int a = 1;
		}
		//printf("v[%d] = %d\n", i, v[i]);
		//printf("v[%d] = %d\n", i+1, v[i+1]);
		
		if(IsPreamble(&v[i]))
		{
			data[cnt++] = 3;
		}
		
		else if(IsOne(&v[i]))
		{
			data[cnt++] = 1;
		}
		
		else if(IsZero(&v[i]))
		{
			data[cnt++] = 0;
		}
		else if(IsPause(&v[i]))
		{
			data[cnt++] = 4;
		}
		else if(IsEnd(&v[i]))
		{
			data[cnt++] = 5;
		}
		else
		{
			printf("ERRORE");
			return;
		}
		//printf("%d\n", i);
	}
	
	//for(i = i; i < DATASIZE; i++)
	//	printf("%d: %d \n", i, data[i]);
	
	for(i = i; i < DATASIZE; i++)
		if(data[i] == -1)
		{
			printf("carattere non riconosciuto");
			return;
		}
	
	printMyArray(data);
	printf("\n");
	printMyArray(&data[70]);
	printf("\n");
	printMyArray(&data[140]);
	printf("\n");
	printMyArray(&data[210]);	
	
	
}


void printMyArray(int8_t* v)
{
	int i;
	uint8_t tmp = 0;
	uint8_t mask = 0x01;
	
	printf("%d\n", v[0]);	//preambolo
	
	for(i = 1; i < 1+8; i++)
		printf("%d ", v[i]);
		
	for(i = 1; i < 1+8; i++)
	{
		if(v[i] == 1)
			tmp |= mask;
		mask <<= 1;
	}
	printf ("0x%2X", tmp);
	
	
	
	
	printf("\n");
	
	for(i = 9; i < 9+8; i++)
		printf("%d ", v[i]);
	
	tmp = 0;
	mask = 0x01;
	for(i = 9; i < 9+8; i++)
	{
		if(v[i] == 1)
			tmp |= mask;
		mask <<= 1;
	}
	printf ("0x%2X", tmp);
	
	printf("\n");
	
	for(i = 17; i < 17+8; i++)
		printf("%d ", v[i]);
		
	tmp = 0;
	mask = 0x01;
	for(i = 17; i < 17+8; i++)
	{
		if(v[i] == 1)
			tmp |= mask;
		mask <<= 1;
	}
	printf ("0x%2X", tmp);	
	
	
	printf("\n");
	
	for(i = 25; i < 25+8; i++)
		printf("%d ", v[i]);
		
	tmp = 0;
	mask = 0x01;
	for(i = 25; i < 25+8; i++)
	{
		if(v[i] == 1)
			tmp |= mask;
		mask <<= 1;
	}
	printf ("0x%2X", tmp);
	
	printf("\n");
	
	printf("%d\n", v[33]);
	printf("%d\n", v[34]);
	printf("%d\n", v[35]);
	printf("%d\n", v[36]);
	
	for(i = 37; i < 37+8; i++)
		printf("%d ", v[i]);
		
	tmp = 0;
	mask = 0x01;
	for(i = 37; i < 37+8; i++)
	{
		if(v[i] == 1)
			tmp |= mask;
		mask <<= 1;
	}
	printf ("0x%2X", tmp);
	
	printf("\n");
	
	for(i = 45; i < 45+8; i++)
		printf("%d ", v[i]);
		
	tmp = 0;
	mask = 0x01;
	for(i = 45; i < 45+8; i++)
	{
		if(v[i] == 1)
			tmp |= mask;
		mask <<= 1;
	}
	printf ("0x%2X", tmp);
	
	printf("\n");
	
	for(i = 53; i < 53+8; i++)
		printf("%d ", v[i]);
		
	tmp = 0;
	mask = 0x01;
	for(i = 53; i < 53+8; i++)
	{
		if(v[i] == 1)
			tmp |= mask;
		mask <<= 1;
	}
	printf ("0x%2X", tmp);
	
	printf("\n");
	
	for(i = 61; i < 61+8; i++)
		printf("%d ", v[i]);
	
	tmp = 0;
	mask = 0x01;
	for(i = 61; i < 61+8; i++)
	{
		if(v[i] == 1)
			tmp |= mask;
		mask <<= 1;
	}
	printf ("0x%2X", tmp);
	
	printf("\n");
		
	printf("%d\n", v[69]);	//end
}


int IsPreamble(uint8_t* v)
{
	if(v[0] > 0.90 * ASTRELBSP_DEF_PREAMBLE_ON_TIME_US && v[0] < 1.10 * ASTRELBSP_DEF_PREAMBLE_ON_TIME_US)
	{
		if(v[1] > 0.90 * ASTRELBSP_DEF_PREAMBLE_OFF_TIME_US && v[1] < 1.10 * ASTRELBSP_DEF_PREAMBLE_OFF_TIME_US)
			return 1;
		return 0;
	}
	return 0;
}

int IsOne(uint8_t* v)
{
	if(v[0] > 0.90 * ASTRELBSP_DEF_BIT_ON_TIME_US && v[0] < 1.105 * ASTRELBSP_DEF_BIT_ON_TIME_US)
	{
		if(v[1] > 0.90 * ASTRELBSP_DEF_BIT1_OFF_TIME_US && v[1] < 1.105 * ASTRELBSP_DEF_BIT1_OFF_TIME_US)
			return 1;
		return 0;
	}
	return 0;
}

int IsZero(uint8_t* v)
{
	if(v[0] > 0.90 * ASTRELBSP_DEF_BIT_ON_TIME_US && v[0] < 1.105 * ASTRELBSP_DEF_BIT_ON_TIME_US)
	{
		if(v[1] > 0.90 * ASTRELBSP_DEF_BIT0_OFF_TIME_US && v[1] < 1.105 * ASTRELBSP_DEF_BIT0_OFF_TIME_US)
			return 1;
		return 0;
	}
	return 0;
}

int IsPause(uint8_t* v)
{
	if(v[0] > 0.90 * ASTRELBSP_DEF_BIT_ON_TIME_US && v[0] < 1.10 * ASTRELBSP_DEF_BIT_ON_TIME_US)
	{
		if(v[1] > 0.90 * ASTRELBSP_DEF_PAUSE_TIME_US && v[1] < 1.105 * ASTRELBSP_DEF_PAUSE_TIME_US)
			return 1;
		return 0;
	}
	return 0;
}

int IsEnd(uint8_t* v)
{
	if(v[0] > 0.90 * ASTRELBSP_DEF_BIT_ON_TIME_US && v[0] < 1.10 * ASTRELBSP_DEF_BIT_ON_TIME_US)
	{
		if(v[1] > 0.90 * ASTRELBSP_DEF_END_TIME_US && v[1] < 1.105 * ASTRELBSP_DEF_END_TIME_US)
			return 1;
		return 0;
	}
	return 0;
}


