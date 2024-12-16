/*
 * CommandParser.h
 *
 *  Created on: Dec 12, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_COMMANDPARSER_H_
#define INC_COMMANDPARSER_H_

#include "main.h"
#include "string.h"

extern uint8_t temp;
extern uint8_t cmd_flag;
extern UART_HandleTypeDef huart2;

char cmd[20];
uint8_t cmd_index;
typedef enum{
	IDLE,
	READ,
	CMD
}CP_state;
CP_state cp_state;

void command_parser_fsm();

#endif /* INC_COMMANDPARSER_H_ */
