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



char* itoa(int value, char* result, int base) {
   // check that the base if valid
   if (base < 2 || base > 36) { *result = '\0'; return result; }

   char* ptr = result, *ptr1 = result, tmp_char;
   int tmp_value;

   do {
      tmp_value = value;
      value /= base;
      *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
   } while ( value );

   // Apply negative sign
   if (tmp_value < 0) *ptr++ = '-';
   *ptr-- = '\0';
   while(ptr1 < ptr) {
      tmp_char = *ptr;
      *ptr--= *ptr1;
      *ptr1++ = tmp_char;
   }
   return result;
}

void ejercicio1_set_up(){
	char aux[30];

	fsmButtonInit( &boton1,TECLA1_TAREA_B);
	fsmButtonInit( &boton2,TECLA2_TAREA_B);

	cola_1 = xQueueCreate( 1, sizeof(aux));
	while( cola_1 == NULL )
	    {
	        /* Queue was not created. */
		 	 uartWriteString( UART_USB, "ERROR, la cola no fue creada" );
	    }
	mutex_1 = xSemaphoreCreateMutex();
	while( mutex_1 == NULL )
	{
	     /* Queue was not created. */
		 uartWriteString( UART_USB, "ERROR, el mutex no fue creado" );
	}
}

void Message_Construction1( )
{
	char aux[10]=MSG1;

	xQueueSend( cola_1 , &aux,  portMAX_DELAY  );
}

void Message_Construction2( tLedTecla* boton, char index)
{
	char aux[20]="TEC_ T____";
	char index_pos=3;
	char time_pos=6;
	char final_pos=11;
	uint8_t precision=3;
	uint8_t i=0;
	uint32_t data;
	char buf [precision];

	if(boton->tiempo_medido>0){
		aux[index_pos]=index;
		data=get_Time(boton);
		itoa(data,buf,10);
		for(i=0;i<=precision;i++)
		{
			aux[time_pos+i]=buf[i];
		}
		xQueueSend( cola_1 , &aux,  portMAX_DELAY  );
	}

}

void Tarea_A( void* taskParmPtr )
{
	char aux[30];
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
		fsmButtonUpdate( &boton1 );
		Message_Construction2( &boton1, INDEX_1);
		fsmButtonUpdate( &boton2 );
		Message_Construction2( &boton2, INDEX_2);

		vTaskDelayUntil( &xLastWakeTime, xPeriodicity );
	}
}

void Tarea_C( void* taskParmPtr )
{
	TickType_t xPeriodicity =  500 / portTICK_RATE_MS;		// Tarea periodica cada 1000 ms
	TickType_t xLastWakeTime = xTaskGetTickCount();
	char aux[30];
	while( 1 )
	{
		xQueueReceive( cola_1, &aux,portMAX_DELAY );	//Si existe un dato solicito el recurso de UART
		xSemaphoreTake( mutex_1, portMAX_DELAY );
		uartWriteString( UART_USB, aux );
		uartWriteString( UART_USB, END_CHAR );
		xSemaphoreGive( mutex_1 );
		vTaskDelayUntil( &xLastWakeTime, xPeriodicity );
	}
}
