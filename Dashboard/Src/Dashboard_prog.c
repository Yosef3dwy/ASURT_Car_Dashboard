#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

#include "main.h"

#include "Dashboard_int.h"
#include "Dashboard_config.h"

#include "Nextion_int.h"
#include "Nextion_config.h"
// #includes ----------------------------

extern UART_HandleTypeDef NEXTION_UART_HANDLE;
extern TIM_HandleTypeDef  DASHBOARD_LABSTOPWATCH_TIMER_HANDLE; // For the Lap StopWatch
extern TIM_HandleTypeDef  DASHBOARD_BUTTONS_DEBOUNCE_TIMER_HANDLE;


extern CAN_HandleTypeDef  hcan;

Nextion Lap_Time;
Nextion Last_Lap;
Nextion Best_Lap;

Nextion ERPM_Slider;
Nextion Temp_Slider;
Nextion Throttle_Slider;
Nextion Brake_Slider;
Nextion Battery_Perc;




void Dashboard_Init(void)
{
    Nextion_AddComp(&Lap_Time, "Lap_Time", 18, "Racer_Mode");
    Nextion_AddComp(&Last_Lap, "Last_Lap", 19, "Racer_Mode");
    Nextion_AddComp(&Best_Lap, "Best_Lap", 20, "Racer_Mode");


    Nextion_AddComp(&ERPM_Slider, "RPM_Slider",  1, "Racer_Mode");
    Nextion_AddComp(&Temp_Slider, "Temp_Slider",  5, "Racer_Mode");
    Nextion_AddComp(&Throttle_Slider, "Thrott_Slider",  24, "Racer_Mode");
    Nextion_AddComp(&Brake_Slider, "Brake_Slider",  25, "Racer_Mode");
    Nextion_AddComp(&Battery_Perc, "Battery_Perc",  21, "Racer_Mode");




    // CAN Filter-----------------------------------------------------
//    CAN_FilterTypeDef canfilterconfig;
//
//    canfilterconfig.FilterActivation     = CAN_FILTER_ENABLE;
//    canfilterconfig.FilterFIFOAssignment = CAN_FilterFIFO0;
//    canfilterconfig.FilterScale          = CAN_FILTERSCALE_32BIT;
//    canfilterconfig.FilterMode		     = CAN_FILTERMODE_IDMASK;
//    canfilterconfig.FilterBank           = 0;
//    canfilterconfig.FilterMaskIdLow	     = 0x000;
//    canfilterconfig.FilterMaskIdHigh     = 0x0F9 << 5;
//    canfilterconfig.FilterIdLow          = 0x000;
//    canfilterconfig.FilterIdHigh         = 0x020 << 5;
//
//    HAL_CAN_ConfigFilter(&hcan, &canfilterconfig);
    //----------------------------------------------------------------
}



//=============================================================================================================================================================
//===============================================Start: Lap Timer==============================================================================================
//=============================================================================================================================================================




/*RTOS Task that will be executed every 10msec to increase the (Lap Timer) on the dashboard with 0.01sec

-->>Note<<-- 
    This function will be suspended directly after creation and will start executing once a GPIO_PIN is hit
*/
StopWatch Lap_Timer = {0};
char Global_u8Array_Tx_Buffer[30] = {0};
void LabTimer_CallBack_ISR()
{
	Lap_Timer.mili_Sec += 1;
    
	Lap_Timer.Sec_dec_1 = Lap_Timer.mili_Sec % 10;
    Lap_Timer.Sec_dec_2 = (Lap_Timer.mili_Sec % 100) / 10;
    
    Lap_Timer.Seconds = Lap_Timer.mili_Sec / 100 ;
    Lap_Timer.Sec_dig_1 = Lap_Timer.Seconds % 10;
    Lap_Timer.Sec_dig_2 = (Lap_Timer.Seconds / 10) % 6;
    
    Lap_Timer.Minutes = Lap_Timer.Seconds / 60;
    Lap_Timer.Min_d1 = Lap_Timer.Minutes % 10;
    Lap_Timer.Min_d2 = Lap_Timer.Minutes / 10;
        
    
    
    sprintf(Global_u8Array_Tx_Buffer, "%u%u:%u%u.%u%u", Lap_Timer.Min_d2, Lap_Timer.Min_d1, Lap_Timer.Sec_dig_2, Lap_Timer.Sec_dig_1, Lap_Timer.Sec_dec_2, Lap_Timer.Sec_dec_1);

	Nextion_SetText(&NEXTION_UART_HANDLE, &Lap_Time, Global_u8Array_Tx_Buffer);
}
//---------------------------------------------------------------------------------------------------------------------




char Global_u8Array_Tx_BestLap_Buffer[30] = {0};
uint8_t  BestLap_Flag = 0;
uint32_t BestLap_Centi_Sec = 0;
void LabTimerStoped()
{
	sprintf(Global_u8Array_Tx_Buffer, "%u%u:%u%u.%u%u", Lap_Timer.Min_d2, Lap_Timer.Min_d1, Lap_Timer.Sec_dig_2, Lap_Timer.Sec_dig_1, Lap_Timer.Sec_dec_2, Lap_Timer.Sec_dec_1);

	if((BestLap_Flag == 0) || (BestLap_Centi_Sec > Lap_Timer.mili_Sec))
	{
		BestLap_Centi_Sec = Lap_Timer.mili_Sec;
	  	sprintf(Global_u8Array_Tx_BestLap_Buffer, "%u%u:%u%u.%u%u", Lap_Timer.Min_d2, Lap_Timer.Min_d1, Lap_Timer.Sec_dig_2, Lap_Timer.Sec_dig_1, Lap_Timer.Sec_dec_2, Lap_Timer.Sec_dec_1);
   	    Nextion_SetText(&NEXTION_UART_HANDLE, &Best_Lap, Global_u8Array_Tx_BestLap_Buffer);

		BestLap_Flag = 1;
	}
	Nextion_SetText(&NEXTION_UART_HANDLE, &Lap_Time, "00:00.00");
	Nextion_SetText(&NEXTION_UART_HANDLE, &Last_Lap, Global_u8Array_Tx_Buffer);
}




uint8_t StopWatch_State = STOPWATCH_STOPED;
void LabTimer_Buttons_Callback(TIM_HandleTypeDef *htim, uint16_t GPIO_Pin)
{
    HAL_NVIC_DisableIRQ(EXTI_COUNT_STOP_PIN_IRQ);
    HAL_NVIC_DisableIRQ(EXTI_CONTINUE_PAUSE_IRQ);

	if((GPIO_Pin == EXTI_COUNT_STOP_BUTTON) && (StopWatch_State == STOPWATCH_STOPED))
	{
    	//-------------------------------------------------------------------

    	Lap_Timer.mili_Sec = 0; Lap_Timer.Seconds = 0; Lap_Timer.Minutes = 0;

		StopWatch_State = STOPWATCH_COUNTING;
		HAL_TIM_Base_Start_IT(&DASHBOARD_LABSTOPWATCH_TIMER_HANDLE);

		//-------------------------------------------------------------------
		HAL_TIM_Base_Start_IT(&DASHBOARD_BUTTONS_DEBOUNCE_TIMER_HANDLE);
	}
	else if((GPIO_Pin == EXTI_COUNT_STOP_BUTTON) && ((StopWatch_State == STOPWATCH_COUNTING) || (StopWatch_State == STOPWATCH_PAUSED)))
	{
    	//-------------------------------------------------------------------

		StopWatch_State = STOPWATCH_STOPED;
		HAL_TIM_Base_Stop_IT(&DASHBOARD_LABSTOPWATCH_TIMER_HANDLE);
		LabTimerStoped();

   	    //-------------------------------------------------------------------
		HAL_TIM_Base_Start_IT(&DASHBOARD_BUTTONS_DEBOUNCE_TIMER_HANDLE);
	}
	else if((GPIO_Pin == EXTI_CONTINUE_PAUSE_BUTTON) && (StopWatch_State == STOPWATCH_COUNTING))
	{
		//-------------------------------------------------------------------

		StopWatch_State = STOPWATCH_PAUSED;
		HAL_TIM_Base_Stop_IT(&DASHBOARD_LABSTOPWATCH_TIMER_HANDLE);

		//-------------------------------------------------------------------
		HAL_TIM_Base_Start_IT(&DASHBOARD_BUTTONS_DEBOUNCE_TIMER_HANDLE);
	}
	else if((GPIO_Pin == EXTI_CONTINUE_PAUSE_BUTTON) && (StopWatch_State == STOPWATCH_PAUSED))
	{
		//-------------------------------------------------------------------

		StopWatch_State = STOPWATCH_COUNTING;
		HAL_TIM_Base_Start_IT(&DASHBOARD_LABSTOPWATCH_TIMER_HANDLE);

		//-------------------------------------------------------------------
		HAL_TIM_Base_Start_IT(&DASHBOARD_BUTTONS_DEBOUNCE_TIMER_HANDLE);
	}

}



void Debouncing_CallBack(TIM_HandleTypeDef *htim)
{
    HAL_TIM_Base_Stop_IT(&DASHBOARD_BUTTONS_DEBOUNCE_TIMER_HANDLE);

    __HAL_GPIO_EXTI_CLEAR_FLAG(EXTI_COUNT_STOP_BUTTON);
    __HAL_GPIO_EXTI_CLEAR_FLAG(EXTI_CONTINUE_PAUSE_BUTTON);

    HAL_NVIC_EnableIRQ(EXTI_COUNT_STOP_PIN_IRQ);
    HAL_NVIC_EnableIRQ(EXTI_CONTINUE_PAUSE_IRQ);
}
//=============================================================================================================================================================
//===============================================End: Lap Timer================================================================================================
//=============================================================================================================================================================




//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------




//=============================================================================================================================================================
//===============================================Start: Parsing CAN Message====================================================================================
//=============================================================================================================================================================


CAN_RxHeaderTypeDef CANRxHeader;
uint8_t Received_CAN_Message[8] = {0};
uint32_t ERPM_Val = 0;
uint16_t MotorTemp_Val = 0;
uint8_t Thrott_Pos = 0;
uint8_t Brake_Pos = 0;
uint16_t Battery = 0;
uint8_t  Batt_int = 0;
uint8_t  Batt_Deci = 0;

char test_Buffer[30] = {0};

void CAN_Message(CAN_HandleTypeDef *hcan)
{
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CANRxHeader, (uint8_t*)&Received_CAN_Message);

	switch(CANRxHeader.StdId)
	{
		case 0x20: //ERPM, "From the Motor Controller"

			ERPM_Val = (Received_CAN_Message[0]) | (Received_CAN_Message[1] << 8) | (Received_CAN_Message[2] << 16) | (Received_CAN_Message[3] << 24);
			ERPM_Val = (float)(ERPM_Val/200.0) * 100.0; // Maping ERPM value to percentage scale.

			Nextion_SetVal(&NEXTION_UART_HANDLE, &ERPM_Slider, ERPM_Val);
			break;

		case 0x22: //Motor Temp, "From the Motor Controller"

			MotorTemp_Val = (Received_CAN_Message[0]) | (Received_CAN_Message[1] << 8);
			MotorTemp_Val = (float)(MotorTemp_Val/200.0) * 100.0; // Maping MotrTemp value to percentage scale.

			Nextion_SetVal(&NEXTION_UART_HANDLE, &Temp_Slider, MotorTemp_Val);
			break;

		case 0x24: //Throttle & Break Position, "From the Motor Controller"

			Thrott_Pos = Received_CAN_Message[0];
			Thrott_Pos = (float)(Thrott_Pos/200.0) * 100.0;
			Brake_Pos  = Received_CAN_Message[1];
			Brake_Pos  = (float)(Brake_Pos/200.0) * 100.0;

			Nextion_SetVal(&NEXTION_UART_HANDLE, &Throttle_Slider, Thrott_Pos);
			Nextion_SetVal(&NEXTION_UART_HANDLE, &Brake_Slider, Brake_Pos);
			break;

		case 0x50: //Testing from IC ECU "battery level" on CAN

			Battery = (Received_CAN_Message[2] << 8) | Received_CAN_Message[3];

			Batt_int = Battery / 100;
			Batt_Deci = Battery % 100;

			sprintf(test_Buffer, "%u.%u", Batt_int, Batt_Deci);
			Nextion_SetText(&NEXTION_UART_HANDLE, &Battery_Perc, test_Buffer);

			break;


		/* Battery level case:
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 *
		 */
	}
}


//=============================================================================================================================================================
//===============================================End: Parsing CAN Message======================================================================================
//=============================================================================================================================================================

