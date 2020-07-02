/*=============================================================================
 * Copyright (c) 2020, DANIEL MARQUEZ <DAMF618@GMAIL.COM>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/05/09
 * Version: 1
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __USER_TASKS_H__
#define __USER_TASKS_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "sapi.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/
#define LED_TAREA_A LEDB
#define TECLA1_TAREA_B TEC1
#define TECLA2_TAREA_B TEC2
#define MSG1 "LED ON "
#define INDEX_1 49
#define INDEX_2 50
#define LED_TIMING 500
#define END_CHAR "\r\n"
/*=====[Prototypes (declarations) of public functions]=======================*/
void ejercicio1_set_up();
void Tarea_A( void* taskParmPtr );
void Tarea_B( void* taskParmPtr );
void Tarea_C( void* taskParmPtr );
/*=====[Prototypes (declarations) of private functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __USER_TASKS_H__ */
