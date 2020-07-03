/*=============================================================================
 * Copyright (c) 2020, DANIEL MARQUEZ <DAMF618@GMAIL.COM>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/05/09
 * Version: 1
 *===========================================================================*/

/*=====[Inclusion of own header]=============================================*/

#include "userTasks.h"

/*=====[Inclusions of private function dependencies]=========================*/

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "sapi.h"
#include "fsm_debounce.h"


/*=====[Definitions of private data types]===================================*/

	QueueHandle_t cola_1;				//Recurso 1
	tLedTecla boton1, boton2;
	SemaphoreHandle_t mutex_1;
	char message[MESSAGE_FULL_LENGTH];

void ejercicio1_set_up(){

	fsmButtonInit( &boton1,TECLA1_TAREA_B,INDEX_1);
	fsmButtonInit( &boton2,TECLA2_TAREA_B,INDEX_2);

	cola_1 = xQueueCreate( 1, sizeof(message));
	while( cola_1 == NULL )
	    {
	        /* Queue was not created. */
		 	 uartWriteString( UART_USB, "ERROR, la cola no fue creada" );
	    }
}

void Message_Construction1( )
{
	char aux[MESSAGE_FULL_LENGTH]=MSG1;

	xQueueSend( cola_1 , aux,  portMAX_DELAY  );
}


void Tarea_A( void* taskParmPtr )
{
	TickType_t xPeriodicity =  1000 / portTICK_RATE_MS;		// Tarea periodica cada 1000 ms
	TickType_t xLastWakeTime = xTaskGetTickCount();
	while( 1 )
	{
		gpioWrite( LED_TAREA_A , ON );
		Message_Construction1();
		vTaskDelay(LED_TIMING/portTICK_RATE_MS);
		gpioWrite( LED_TAREA_A , OFF );
		vTaskDelayUntil( &xLastWakeTime, xPeriodicity );
	}
}

void Tarea_B( void* taskParmPtr )
{

	TickType_t xPeriodicity =  DEBOUNCE_TIME / portTICK_RATE_MS;		// Tarea periodica cada 1000 ms
	TickType_t xLastWakeTime = xTaskGetTickCount();
	while( 1 )
	{
		fsmButtonUpdate( &boton1,cola_1);
		fsmButtonUpdate( &boton2,cola_1);
		vTaskDelayUntil( &xLastWakeTime, xPeriodicity );
	}
}

void Tarea_C( void* taskParmPtr )
{
	TickType_t xPeriodicity =  500 / portTICK_RATE_MS;		// Tarea periodica cada 1000 ms
	TickType_t xLastWakeTime = xTaskGetTickCount();
	char aux[MESSAGE_FULL_LENGTH];
	while( 1 )
	{
		xQueueReceive( cola_1, aux,portMAX_DELAY );	//Si existe un dato solicito el recurso de UART
		uartWriteString( UART_USB, aux );
		uartWriteString( UART_USB, END_CHAR );
		vTaskDelayUntil( &xLastWakeTime, xPeriodicity );
	}
}
