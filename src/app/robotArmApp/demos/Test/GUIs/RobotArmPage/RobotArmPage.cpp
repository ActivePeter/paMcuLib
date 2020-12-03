#include "../MainGUI/MainGUI.h"
#ifdef RobotArmApp_demo_Test

#include "pa_CommonLib/src/service/graphic/lvgl/lvgl.h"

extern "C"
{
#include "stdio.h"
}

namespace GUI
{
    lv_obj_t *robotArmPage;
    static void menuBtn_robotArmPage_event_handler(lv_obj_t *obj, lv_event_t event)
    {
        if (event == LV_EVENT_PRESSED)
        {
            switchPage(robotArmPage);
            // lv_obj_set_hidden(curPage, true);
            // lv_obj_set_hidden(menuPage, false);
            // if (lv_obj_is_visible(menuPage))
            // {
            //     lv_obj_set_hidden(menuPage, true);
            // }
            // else
            // {
            //     lv_obj_set_hidden(menuPage, false);
            // }
            // printf("Clicked\n");
        }
    }
    void RobotArmPage_init()
    {
        addMenuBtn(menuBtn_robotArmPage_event_handler, "RobotArm");
        initPage(robotArmPage);
    }

} // namespace GUI
#endif
