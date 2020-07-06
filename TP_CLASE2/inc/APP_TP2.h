/*=============================================================================
/** TP2 RTOS 2
 *  AUTORES: GORRIN ALEJANDRO
 *  		 MARQUEZ DANIEL
 *  		 MONZON LUCAS
 *
 */
/*===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef APP_TP2_H_
#define APP_TP2_H_

/*=====[Inclusions of public function dependencies]==========================*/

#include "FreeRTOS.h"
#include "task.h"
#include "sapi.h"

#include <UART.h>

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/
// Structure with all the data needed to generate a new instance of the FULL APP
typedef struct{
	UART_PERIPH_t UART;
}APP_t;

/*=====[Prototypes (declarations) of public functions]=======================*/

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* APP_TP2_H_ */
