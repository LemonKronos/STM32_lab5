/*
 * UARTCommunicate.c
 *
 *  Created on: Dec 12, 2024
 *      Author: TRONG DAT
 */
#include "UARTCommunicate.h"
#include "main.h"

UC_state uc_state = UART_IDLE;
char output[20] = "EMPTY";

void UART_communication(){
	switch(uc_state){
	case UART_IDLE:
		if(cmd_flag == 1){
			uc_state = UART_CHECK;
			cmd_flag = 0;
		}
		break;

	case UART_CHECK:
		if(cmd[0] == 'R' && cmd[1] == 'T' && cmd[2] == 'S'){
			uc_state = UART_SEND;
		}
		else if(cmd[0] == 'O' && cmd[1] == 'K'){
			uc_state = UART_IDLE;
		}
		else{
			uc_state = UART_IDLE;
		}
		break;

	case UART_SEND:
		ADC_value = HAL_ADC_GetValue(&hadc1);
		ADC_old = ADC_value;
		failed = 0;
		formatADCValue(ADC_value, output);
		HAL_UART_Transmit(&huart2, (void *)output, sizeof(output), 1000);

		uc_state = UART_WAIT;
		break;

	case UART_WAIT:
		if(timer_flag == 1){
			timer_flag = 0;
			if(cmd[0] == 'O' && cmd[1] == 'K'){
				HAL_GPIO_TogglePin(TEST_GPIO_Port, TEST_Pin);
				uc_state = UART_IDLE;
			}
			else if(failed < 3){
				failed++;
				formatADCValue(ADC_old, output);
				HAL_UART_Transmit(&huart2, (void *)output, sizeof(output), 1000);
				HAL_GPIO_TogglePin(TEST_GPIO_Port, TEST_Pin);
				uc_state = UART_WAIT;
			}
			else uc_state = UART_IDLE;
		}
		break;

	default:
		uc_state = UART_IDLE;
		break;
	}
}

// Function to convert ADC value to formatted string
void formatADCValue(uint32_t ADC_value, char *output) {
    // Convert ADC value to string and format it
    snprintf(output, 50, "!ADC=%luV#", ADC_value);
}
