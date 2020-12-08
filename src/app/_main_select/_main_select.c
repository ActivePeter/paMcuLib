#include "_main_select.h"
#include "pa_Defines.h"
#ifdef RobotArmApp_demo_Test
#include "../RobotArmApp/demos/Test/pa_Main/pa_Main.h"
void main_select()
{
    pa_Main();
}
#endif

#ifdef SvpwmFoc_demo_Test
#include "../SvpwmFoc/demos/Test/pa_Main/pa_Main.h"
void main_select()
{
    pa_Main();
}
#endif

#ifdef _SpecificMcuApp_MSP432E_MQTT_demo_Test
#include "../_SpecificMcuApp/MSP432E/MQTT/demos/Test/pa_Main/pa_Main.h"
void main_select()
{
    pa_Main();
}
#endif