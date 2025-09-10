#ifndef PROX_INT_H
#define PROX_INT_H





typedef struct
{
	uint8_t count;
	uint16_t curr;
	uint16_t prev;
	uint32_t Acculmulated_Overflow_Count;
	uint32_t Actual_Overflow_Count;
	uint8_t velocity;

	double time;
	double After_Filtering; // Testing
}Prox_Wheel_Velcoity;



#define				FRONT_LEFT			0
#define				FRONT_RIGHT			1
#define				REAR_LEFT			2
#define				REAR_RIGHT			3

#define 			WINDOW_SIZE		 	5




int moving_average(int new_value);
void PROX_INIT();
void PROX_ResetVelocity(TIM_HandleTypeDef *htim);
void PROX_ICUCallBack_ISR(TIM_HandleTypeDef *htim);




#endif
