/*
 * app.h
 *
 *  Created on: 16 oct. 2020
 *      Author: pablo
 */

#ifndef MYPROGRAMS_AM2320_INC_APP_H_
#define MYPROGRAMS_AM2320_INC_APP_H_

#include "sapi.h"
#include "am2320.h"
#include <string.h>


typedef enum{
	APPMODE_ONESHOT,
	APPMODE_CONT_T,
	APPMODE_CONT_H,
	APPMODE_CONT_ALL
}app_mode_t;

typedef struct{
	uartMap_t 	btUart;
	uartMap_t 	infoUart;
	uint32_t 	baudRate;
	bool_t	  	info;
	app_mode_t	mode;
}app_config_t;

bool_t app_getByteBT(uint8_t *buf);
void app_sendBT(const char *str);
void app_info(const char *str);
bool_t app_sendData(AM2320_data_t datatype);

bool_t app_bleTest();

app_mode_t app_getMode();
void app_setMode(app_mode_t mode);

bool_t app_init(app_mode_t mode ,uint32_t baudRate,uartMap_t btUart,uartMap_t infoUart);
void app_update();

#endif /* MYPROGRAMS_AM2320_INC_APP_H_ */
