#include "pa_Defines.h"
#ifdef GRAPHIC_USE_LVGL
//全局宏//////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PA_LVGL_H__
#define __PA_LVGL_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "pa_CommonLib/src/service/graphic/lvgl/lvgl.h"
    extern uint16_t Global_Touch_X;
    extern uint16_t Global_Touch_Y;
    void pa_Lvgl_init();
    void pa_Lvgl_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
    void pa_Lvgl_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data);

#ifdef __cplusplus
}
#endif

#endif // __PA_LVGL_H__
//全局宏//////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif