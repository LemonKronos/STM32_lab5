/*
 * CommandParser.c
 *
 *  Created on: Dec 12, 2024
 *      Author: TRONG DAT
 */

#include "CommandParser.h"

CP_state cp_state = IDLE;

void command_parser_fsm(){
	switch(cp_state){
	case IDLE:
		cp_state = READ;
		break;

	case READ:
		if(temp == '!'){
			cp_state = CMD;
			cmd_index = 0;
			memset(cmd, 0, sizeof(cmd));
		}
		break;

	case CMD:
		if(temp != '#'){
			cmd[cmd_index] = temp;
			cmd_index++;
		}
		else{
			cmd_flag = 1;
			cp_state = IDLE;
		}
		HAL_UART_Transmit(&huart2, &temp, 1, 50);
		break;
	default:
		cp_state = IDLE;
		break;
	}
}























