#ifndef NEXTION_INT_H
#define NEXTION_INT_H



#define     NEXTION_COMMAND_MAX_LENGTH          70
#define     NEXTION_COMMAND_END                 0xFF, 0xFF, 0xFF
#define     NEXTION_COMMAND_END_LENGTH          3


typedef struct
{
    char CompName[20];
    uint8_t CompID;
    char CompPage[10];

} Nextion;



void Nextion_Init(UART_HandleTypeDef *huart);
void Nextion_AddComp(Nextion *nex, char *_objname, uint8_t _id, char *_page);
void Nextion_SendCommand(UART_HandleTypeDef *huart, uint8_t *command);
void Nextion_EndCommand(UART_HandleTypeDef *huart);
void Nextion_SetText(UART_HandleTypeDef *huart, Nextion *nex, char *text);
void Nextion_SetVal(UART_HandleTypeDef *huart, Nextion *nex, uint32_t val);





#endif // NEXTION_INT_H
