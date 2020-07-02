/*=============================================================================
 * Copyright (c) 2020, DANIEL MARQUEZ <DAMF618@GMAIL.COM>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/05/09
 * Version: 1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "EJERCICIO1.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "sapi.h"
#include "userTasks.h"

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
	boardInit();

	ejercicio1_set_up();

   // Create a task in freeRTOS with dynamic memory
	BaseType_t res= xTaskCreate(
			   Tarea_A,        				// Function that implements the task.
			   (const char *)"Tarea_A",		// Text name for the task.
			   configMINIMAL_STACK_SIZE,	// Stack size in words, not bytes.
			   0,							// Parameter passed into the task.
			   tskIDLE_PRIORITY+1,			// Priority at which the task is created.
			   0 );         				// Pointer to the task created in the system

	   if(res==0){
	   		while(1){
		   printf("Error creando la Tarea_A");
	   		}
	   }

	   	   res= xTaskCreate(
			   Tarea_B,        				// Function that implements the task.
	   		   (const char *)"Tarea_B",		// Text name for the task.
	   		   configMINIMAL_STACK_SIZE,	// Stack size in words, not bytes.
	   		   0,							// Parameter passed into the task.
	   		   tskIDLE_PRIORITY+1,			// Priority at which the task is created.
	   		   0 );         				// Pointer to the task created in the system

	      if(res==0){
	      		while(1){
	   	   printf("Error creando la Tarea_B");
	      		}
	      }

	      res= xTaskCreate(
	      		   Tarea_C,        				// Function that implements the task.
	      		   (const char *)"Tarea_C",		// Text name for the task.
	      		   configMINIMAL_STACK_SIZE*2,	// Stack size in words, not bytes.
	      		   0,							// Parameter passed into the task.
	      		   tskIDLE_PRIORITY+1,			// Priority at which the task is created.
	      		   0 );         				// Pointer to the task created in the system

	         if(res==0){
	         		while(1){
	      	   printf("Error creando la Tarea_C");
	         		}
	         }


   vTaskStartScheduler(); // Initialize scheduler

   while( true ); // If reach heare it means that the scheduler could not start

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;

}
