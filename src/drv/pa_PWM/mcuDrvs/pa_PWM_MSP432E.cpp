extern "C"{
    #include "../pa_PWM.h"
}

#ifdef MSP432E
namespace pa_PWM
{
    void initPWMs(){

    }
    void setPWMDuty(char index,float duty){
        
    }
} // namespace PWM
#endif