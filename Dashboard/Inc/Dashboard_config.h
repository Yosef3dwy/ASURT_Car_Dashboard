#ifndef DASHBOARD_CONFIG_H
#define DASHBOARD_CONFIG_H



#define         DASHBOARD_BUTTONS_DEBOUNCE_TIMER_HANDLE       htim3
#define         DASHBOARD_LABSTOPWATCH_TIMER_HANDLE           htim4


#define         DASHBOARD_BUTTONS_DEBOUNCE_TIMER_NO 	      TIM3
#define         DASHBOARD_LABSTOPWATCH_TIMER_NO		          TIM4


#define			EXTI_COUNT_STOP_BUTTON			GPIO_PIN_0
#define			EXTI_COUNT_STOP_PIN_IRQ			EXTI0_IRQn
//                                                  ^
//							  change this number according to your choosen GPIO_PIN of (EXTI_COUNT_STOP_BUTTON)

#define			EXTI_CONTINUE_PAUSE_BUTTON		GPIO_PIN_1
#define			EXTI_CONTINUE_PAUSE_IRQ			EXTI1_IRQn
//                                                  ^
//							  change this number according to your choosen GPIO_PIN of (EXTI_CONTINUE_PAUSE_BUTTON)


//#define			MaxMotor_RPM					9000
//#define			Num_Motor_Poles					4
//#define			ERPM_MaxScale					MaxMotor_RPM * Num_Motor_Poles
#define			ERPM_MaxScale					4294967295 // testing

#define			MaxTemp							65535

#define			MaxPos							255


#endif
