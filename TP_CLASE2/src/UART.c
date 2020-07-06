/** TP2 RTOS 2
 *  AUTORES: GORRIN ALEJANDRO
 *  		 MARQUEZ DANIEL
 *  		 MONZON LUCAS
 *
 */

/*==================[inclusiones]============================================*/

// Includes de FreeRTOS
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"

// sAPI header
#include "sapi.h"

// Alocacion de Memoria
#include "qmpool.h"

// Configuracion TP2
#include <UART.h>
#include <APP_TP2.h>

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

//TODO Verificar Funcion de Interrupcion Recepcion y Envio

//Interrupt processing for the arrive of a UART Character
static void onRx(  void *taskParmPtr )
{
	APP_t * aux = (APP_t *)taskParmPtr;
	// Lectura de dato y borrado de flag de interrupcion por UART
	char datareceived=0;
	datareceived = uartRxRead( aux->UART.Uart_Port );
/*	BaseType_t uartupdate = pdFALSE;
	//Verificacion para ceder el CPU a la tarea de interrupcion
	xQueueSendFromISR( aux->prim_handler.UARTQUEUE, &datareceived, &uartupdate );
	portYIELD_FROM_ISR( uartupdate );
*/
}


/*TODO Implementar Interrupcion por Transmision*/
static void onTx(  void *taskParmPtr )
{

}


/*==================[declaraciones de funciones externas]====================*/

// It sets the parameters for the UART configuration.
void UARTInit(APP_t * App_tp2 ,uartMap_t Uart, uint32_t baud_rate ){
	App_tp2->UART.Uart_Port =Uart;
	App_tp2->UART.Baud_Rate =baud_rate;
	uartConfig( App_tp2->UART.Uart_Port , App_tp2->UART.Baud_Rate );						//UART Port and Baud Rate Configuration
	uartCallbackSet(App_tp2->UART.Uart_Port, UART_RECEIVE, onRx, App_tp2);			// Set of a callback for the event of receiving an UART character
	uartCallbackSet(App_tp2->UART.Uart_Port, UART_TRANSMITER_FREE, onTx, App_tp2);
	uartInterrupt(App_tp2->UART.Uart_Port, TRUE);									// Enabling UART_USB Interruptions

}


/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[fin del archivo]========================================*/


