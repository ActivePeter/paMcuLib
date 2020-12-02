#include "../pa_PWM.h"

#ifdef STM32_H7
extern TIM_HandleTypeDef htim3;
namespace pa_PWM
{
#define PWMCount 1999
    /*
    * 0 tim3,ch2
    * 1 tim3,ch3
    * 2 tim3,ch4
    */
    void initPWM(char index)
    {
        switch (index)
        {
        case 0:
            HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
            break;
        case 1:
            HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
            break;
        case 2:
            HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
        default:
            break;
        }
    }
    /*
    * 0 tim3,ch2
    * 1 tim3,ch3
    * 2 tim3,ch4
    */
    void setPWMDuty(char index, float duty)
    {
        int value = duty * PWMCount;
        if (value < 0)
            value = 0;
        if (value > PWMCount)
            value = PWMCount;
        switch (index)
        {
        case 0: //pc7
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, value);
            /* code */
            break;
        case 1: //pc8
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, value);
            /* code */
            break;
        case 2: //pc9
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, value);
            /* code */
            break;
        }
    }
} // namespace pa_PWM
#endif