#include "sapi.h"        // <= Inclusion de la Biblioteca sAPI
#include "am2320.h"
#include "app.h"


#define UART_BLUETOOTH UART_232
#define UART_PC        UART_USB
#define BAUDRATE 9600

/*==================[declaraciones de funciones externas]====================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------
	boardConfig(); // Inicializar y configurar la plataforma



	app_init(APPMODE_ONESHOT,BAUDRATE,UART_BLUETOOTH,UART_PC);


   // ---------- REPETIR POR SIEMPRE --------------------------
   while(TRUE) {

	   app_update();

	   delay(500); // Espero 500 ms.
   }
   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamente sobre un microcontrolador y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}


/*==================[definiciones de funciones externas]=====================*/

