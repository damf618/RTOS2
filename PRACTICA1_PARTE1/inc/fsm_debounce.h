/*
 * fsm_debounce.h
 *
 *  Created on: Jun 30, 2020
 *      Author: daniel
 */

#ifndef FSM_DEBOUNCE_H_
#define FSM_DEBOUNCE_H_
/*=====[Inclusions of public function dependencies]==========================*/
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "sapi.h"

#define DEBOUNCE_TIME 40

/*=====[C++ - begin]=========================================================*/
#ifdef __cplusplus
extern "C" {
#endif


typedef enum
{
    STATE_BUTTON_UP,
    STATE_BUTTON_DOWN,
    STATE_BUTTON_FALLING,
    STATE_BUTTON_RISING
} fsmButtonState_t;

typedef struct
{
	gpioMap_t tecla;					//Tecla para antirebote
	gpioMap_t led_a;					//Led Asociado a la Tecla

	char index;

	TickType_t tiempo_medido;			//variables
	fsmButtonState_t fsmButtonState;	//Estado Actual
	TickType_t tiempo_down;				//Aux Tiempo en Down
	TickType_t tiempo_up;				//Aux Tiempo en High

} tLedTecla;

void fsmButtonError( tLedTecla* config );
void fsmButtonInit( tLedTecla* config ,gpioMap_t button,char index);
void fsmButtonUpdate( tLedTecla* config, QueueHandle_t cola );

TickType_t get_Time(tLedTecla* config);

/*=====[C++ - end]===========================================================*/
#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/
#endif /* FSM_DEBOUNCE_H_ */
