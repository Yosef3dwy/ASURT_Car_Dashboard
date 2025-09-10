#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "main.h"
#include "stdint.h"

#include "Nextion_int.h"
#include "Nextion_config.h"



uint8_t TransmitBuffer[NEXTION_COMMAND_MAX_LENGTH] = {0};
uint16_t TransmitBufferLength = 0;
char END[NEXTION_COMMAND_END_LENGTH]               = {NEXTION_COMMAND_END};




//-----------------------------------------------------------------------------------------------------------------------------
//void Nextion_Init(UART_HandleTypeDef *huart) // This function will be removed if I didn't think of something to do with it
//{
//    TransmitBufferLength = (uint16_t)sprintf((char *)TransmitBuffer, "baud=%d", NEXTION_UART_BAUDRATE);
//    Nextion_SendCommand(huart, (uint8_t *)TransmitBuffer);
//
//    // Crulial delay to allow Nextion to change baudrate
//    HAL_Delay(100);
//
//    huart->Init.BaudRate = NEXTION_UART_BAUDRATE;
//    if (HAL_UART_Init(huart) != HAL_OK)
//    {
//      Error_Handler();
//    }
//}
//-----------------------------------------------------------------------------------------------------------------------------






void Nextion_AddComp(Nextion *nex, char *_objname, uint8_t _id, char *_page)
{
	strcpy(nex->CompName, _objname);
    nex->CompID = _id;
	strcpy(nex->CompPage, _page);
}


void Nextion_SendCommand(UART_HandleTypeDef *huart, uint8_t *command)
{
	HAL_UART_Transmit(huart, command, TransmitBufferLength, 1000);
    Nextion_EndCommand(huart);
}

void Nextion_EndCommand(UART_HandleTypeDef *huart)
{
	HAL_UART_Transmit(huart, (const uint8_t *)END, NEXTION_COMMAND_END_LENGTH, 1000);
}


void Nextion_SetText(UART_HandleTypeDef *huart, Nextion *nex, char *text)
{
    TransmitBufferLength = (uint8_t)sprintf((char *)TransmitBuffer, "%s.txt=\"%s\"", nex->CompName, text);
    Nextion_SendCommand(huart, TransmitBuffer);
}


void Nextion_SetVal(UART_HandleTypeDef *huart, Nextion *nex, uint32_t val)
{
    TransmitBufferLength = (uint8_t)sprintf((char *)TransmitBuffer, "%s.val=%lu", nex->CompName, val);
    Nextion_SendCommand(huart, TransmitBuffer);
}
