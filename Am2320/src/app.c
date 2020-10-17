/*
 * am2320.c
 *
 *  Created on: 10 oct. 2020
 *      Author: pablo
 */

#include "sapi.h"
#include "app.h"

#define TEST_TIMEOUT 1000

char buf[AM2320_DATA_SIZE];
uint8_t data=0;

AM2320_config_t sensorConfig;
app_config_t appConfig;


void app_info(const char *str){
	if(appConfig.info){
		uartWriteString( appConfig.infoUart,str);
	}
}

void app_sendBT(const char *str){
	uartWriteString( appConfig.btUart,str);
}

bool_t app_getByteBT(uint8_t *buf){
	return uartReadByte( appConfig.btUart, buf );
}

bool_t app_bleTest(){

	bool_t check;


	app_info( "Testeo si el modulo esta conectado enviando: AT\r\n" );
	app_sendBT("AT\r\n" );

	if( waitForReceiveStringOrTimeoutBlocking( appConfig.btUart,"OK\r\n", strlen("OK\r\n"),TEST_TIMEOUT) ){
		check = TRUE;
		app_info("Modulo conectado correctamente.\r\n");

	}
	else{
		check = FALSE;
	    app_info("No funciona.\r\n");
	}

	return check;
}

/*
 * Setea el modo inicial de la app.
 * Inicia parámetros de comunicación BT y con una PC.
 * Inicia las configuraciones por defecto del sensor.
 */
bool_t app_init(app_mode_t mode ,uint32_t baudRate,uartMap_t btUart,uartMap_t infoUart){

	am2320_setDefaultConfig(&sensorConfig);
	am2320_init(&sensorConfig);

	appConfig.mode = mode;
	// Config bluetooth uart
	appConfig.btUart = btUart;
	appConfig.baudRate = baudRate;
	uartConfig( btUart, baudRate );

	if(infoUart != NULL) {
		appConfig.infoUart = infoUart;
		appConfig.info = TRUE;
		uartConfig(infoUart,baudRate);
	}


	return app_bleTest();
}

app_mode_t app_getMode(){
	return appConfig.mode;
}

void app_setMode(app_mode_t mode){
	appConfig.mode = mode;
}

/*
 * Lee y transmite a la aplicación el tipo de dato de entrada.
 */
bool_t app_sendData(AM2320_data_t datatype){

	if(am2320_getDataString(&sensorConfig,datatype,buf)){
		app_sendBT(buf);
		return TRUE;
	}
	else{
		app_info("readERROR\n");
		return FALSE;
	}

}

void app_update(){
	if(app_getMode() == APPMODE_ONESHOT){
		if( app_getByteBT(&data) ){
			if( data == 't' ) {
				gpioToggle(LED2);
				app_sendData(AM2320_DATA_T);
			}
			if( data == 'h' ) {
				gpioToggle(LED1);
				app_sendData(AM2320_DATA_H);

			}
			if( data == 'a' ) {
				gpioToggle(LEDB);
				app_sendData(AM2320_DATA_ALL);
			}
			if( data == 'c' ) {
				app_setMode(APPMODE_CONT_ALL);
			}
		}
	}
	else{
		switch(app_getMode()){
		case APPMODE_CONT_T:
			gpioToggle(LED2);
			app_sendData(AM2320_DATA_T);
			break;
		case APPMODE_CONT_H:
			gpioToggle(LED1);
			app_sendData(AM2320_DATA_H);
			break;
		case APPMODE_CONT_ALL:
			gpioToggle(LEDB);
			app_sendData(AM2320_DATA_ALL);
			break;
		}

		if( app_getByteBT(&data) ) {
					if( data == 't' ) {
						app_setMode(APPMODE_CONT_T);
					}
					if( data == 'h' ) {
						app_setMode(APPMODE_CONT_H);
					}
					if( data == 'a' ) {
						app_setMode(APPMODE_CONT_ALL);
					}
					if( data == 'c' ) {
						app_setMode(APPMODE_ONESHOT);
					}
				}
	}
}


