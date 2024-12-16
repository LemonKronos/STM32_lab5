/*
 * UARTCommunicate.h
 *
 *  Created on: Dec 12, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_UARTCOMMUNICATE_H_
#define INC_UARTCOMMUNICATE_H_

#include "main.h"
#include "CommandParser.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "stm32f1xx_hal.h"

extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc1;
extern uint8_t cmd_flag;
extern uint32_t ADC_value;
uint32_t ADC_old;
uint8_t failed;
extern uint8_t timer_flag;
char cmd[20];
char output[20];     // New string to store the formatted value

typedef enum{
	UART_IDLE,
	UART_CHECK,
	UART_SEND,
	UART_WAIT
}UC_state;
UC_state uc_state;

void UART_communication();
void formatADCValue(uint32_t ADC_value, char *output);
#endif /* INC_UARTCOMMUNICATE_H_ */
