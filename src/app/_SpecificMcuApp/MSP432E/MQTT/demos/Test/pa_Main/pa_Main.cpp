#include "pa_Main.h"
#ifdef _SpecificMcuApp_MSP432E_MQTT_demo_Test
//from pa_CommonLib
#include "pa_CommonLib/src/drv/pa_CommonDrv/pa_CommonDrv.h"
#include "pa_CommonLib/src/service/graphic/lvgl/lvgl.h"
#include "pa_CommonLib/src/service/graphic/lvgl/pa_Lvgl/pa_Lvgl.h"
#include "pa_CommonLib/src/util/pa_DataProcessor/pa_DataProcessor.h"
//in project
#include "../GUIs/MainGUI/MainGUI.h"
#include "../GUIs/RobotArmPage/RobotArmPage.h"
#include "../pa_UsedDevice/pa_UsedDevice.h"
#include "../../../lib/client_cbs/client_cbs.h"

// #include "../../../RobotArmApp/RobotArmApp.h"
#include "pa_CommonLib/src/service/sensors/attitude/bno055/bno055.h"

#include "pa_CommonLib/src/app/_SpecificMcuApp/MSP432E/MQTT/lib/pa_Mqtt/pa_Mqtt.h"
// RobotArmApp &robotArm = RobotArmApp::instance;
using namespace pa_UsedDevice;

void tim_100us_tick();
void tim_1ms_tick();
int cnt = 0;
int run = 0;

// int encoder1 = 0;
// int encoder1_delta = 0;
// int encoder2 = 0;
// int encoder2_delta = 0;
// extern TIM_HandleTypeDef htim3, htim4, htim5;
//

namespace TimTasks
{
    bool flag_1s = false;
    void loop()
    {
        if (flag_1s)
        {
            flag_1s = false;
            char buf[20];
            pa_snprintf(buf, 20, "l f: %d %d\r\n", 1, 1);
            pa_Debug(buf);
            pa_Debug("1s is ticked\r\n");
        }
    }
} // namespace TimTasks

void pa_Main()
{
    pa_setTimerCallback(tim_100us_tick, tim_1ms_tick);
    /*************
     * 
     * screen init
     * 
     * ***********/
    pa_spiInit();

    touch.init(240, 320, 210, 3800, 451, 3884, 40);
    ili9341.init(pa_ILI9341::Rotation::Rotation_VERTICAL_2);
    /*************
     * 
     * gui init
     * 
     * ***********/
    lv_init();
    pa_Lvgl_init();
    GUI::initMainGUI();
    /*************
     * 
     * bno055 init
     * 
     * ***********/
    pa_IIC_init();
    pa_BNO055_init();

    // HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, (GPIO_PinState)1);
    run = 0;

    for (;;)
    {

        TimTasks::loop();
        { //lv
            // uint16_t coord[2];
            // pa_touchScreen::instance.readRaw(coord);
            GUI::RobotArmPage_update(1, 1);
            bno055_vector_t v;
            v = pa_BNO055_getVector();
            GUI::updateEncoder(v.x, v.y, v.z, run);

            char *topic = "/simplelink/bno055";
            char dataBuff[30];
            uint16_t dataBuffLen = 6; //pa_snprintf(dataBuff, 30, "%d %d %d", v.x, v.y, v.z);
            int16_t vx = v.x * 5;
            int16_t vy = v.y * 5;
            int16_t vz = v.z * 5;
            dataBuff[0] = (char)(vx >> 8);
            dataBuff[1] = (char)(vx);
            dataBuff[2] = (char)(vy >> 8);
            dataBuff[3] = (char)(vy);
            dataBuff[4] = (char)(vz >> 8);
            dataBuff[5] = (char)(vz);
            pa_Mqtt_publish(topic, sizeof(topic), dataBuff, dataBuffLen);
            // GUI::updateEncoder(encoder1, encoder1_delta, encoder2, encoder2_delta);
            // GUI::updateAdc(focMotor1.getCurEularAngle());
            lv_task_handler(); //lvgl刷新显示内容
        }
        pa_delayMs(5);

        // HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_1);
    }
}
void tim_100us_tick()
{
    //    robotArm.onTimerTick();
    // robotArm.onTimerTick();
}
void tim_1ms_tick()
{
    lv_tick_inc(1);
    cnt++;
    if (cnt == 1000)
    {
        cnt = 0;
        TimTasks::flag_1s = true;
        run++;
    }
}
#endif
