/*=============================================================================
/** TP2 RTOS 2
 *  AUTORES: GORRIN ALEJANDRO
 *  		 MARQUEZ DANIEL
 *  		 MONZON LUCAS
 *
 */
/*===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef UART_H_
#define UART_H_

/*=====[Inclusions of public function dependencies]==========================*/

#include "FreeRTOS.h"
#include "task.h"
#include "sapi.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/
typedef struct{
	uartMap_t Uart_Port;
	uint32_t Baud_Rate;
}UART_PERIPH_t;
/*=====[Prototypes (declarations) of public functions]=======================*/

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* UART_H_ */
