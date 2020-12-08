
#include "pa_UsedDevice.h"
#ifdef _SpecificMcuApp_MSP432E_MQTT_demo_Test
namespace pa_UsedDevice
{
    pa_ILI9341 &ili9341 = pa_ILI9341::instance;
    pa_touchScreen &touch = pa_touchScreen::instance;
} // namespace pa_UsedDevice
#endif