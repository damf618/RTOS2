/* Copyright 2018, Eric Pernia.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "sapi.h"
#include "fsm_debounce.h"
#include "FreeRTOS.h"
#include "userTasks.h"

void Message_Construction2( tLedTecla* boton, QueueHandle_t cola)
{
	char aux[MESSAGE_FULL_LENGTH];
	uint32_t data;
	data=get_Time(boton);
	sprintf(aux, "TEC%1d  T%04d",boton->index,data);
	xQueueSend( cola , aux,  portMAX_DELAY  );
}


/* Accion del evento de tecla pulsada */
void buttonPressed( tLedTecla* config )
{
	config->tiempo_down = xTaskGetTickCount();
}

/* Accion de el evento de tecla liberada */
void buttonReleased( tLedTecla* config, QueueHandle_t cola  )
{
	config->tiempo_up = xTaskGetTickCount();
	config->tiempo_medido = (config->tiempo_up - config->tiempo_down)/portTICK_RATE_MS;
	Message_Construction2(config, cola);

}

TickType_t get_Time(tLedTecla* config){
	TickType_t aux=config->tiempo_medido;
	config->tiempo_medido=0;
	if(aux>=0){
		return aux;
	}
	else{
		return 0;
	}
}

void fsmButtonError( tLedTecla* config )
{
	config->fsmButtonState = BUTTON_UP;
}

void fsmButtonInit( tLedTecla* config, gpioMap_t button, char index )
{
	config->tecla = button;
	config->index = index;
	config->fsmButtonState = BUTTON_UP;  // Set initial state
}


// FSM Update Sate Function
void fsmButtonUpdate( tLedTecla* config, QueueHandle_t cola )
{

    switch( config->fsmButtonState )
    {
        case STATE_BUTTON_UP:
            /* CHECK TRANSITION CONDITIONS */
            if( !gpioRead( config->tecla ) )
            {
            	config->fsmButtonState = STATE_BUTTON_FALLING;
            }
            break;

        case STATE_BUTTON_FALLING:
            /* ENTRY */

            /* CHECK TRANSITION CONDITIONS */
        	vTaskDelay(DEBOUNCE_TIME/portTICK_RATE_MS);
        	if( !gpioRead( config->tecla ) )
        	{
        		config->fsmButtonState = STATE_BUTTON_DOWN;

        		/* ACCION DEL EVENTO !*/
        		buttonPressed(config);
        	}
        	else
        	{
        		config->fsmButtonState = STATE_BUTTON_UP;
        	}
        	/* LEAVE */
        	break;

        case STATE_BUTTON_DOWN:
        	/* CHECK TRANSITION CONDITIONS */
        	if( gpioRead( config->tecla ) )
        	{
        		config->fsmButtonState = STATE_BUTTON_RISING;
        	}
        	break;

        case STATE_BUTTON_RISING:
        	/* ENTRY */

        	/* CHECK TRANSITION CONDITIONS */

        	vTaskDelay(DEBOUNCE_TIME/portTICK_RATE_MS);
        	if( gpioRead( config->tecla ))
        	{
        		config->fsmButtonState = STATE_BUTTON_UP;

        		/* ACCION DEL EVENTO ! */
        		buttonReleased(config,cola);
        	}
        	else
        	{
        		config->fsmButtonState = STATE_BUTTON_DOWN;
        	}
        	/* LEAVE */
        	break;

        default:
        	fsmButtonError(config);
        	break;
    }
}
