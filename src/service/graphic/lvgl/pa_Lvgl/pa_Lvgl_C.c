
#include "pa_Lvgl.h"
#ifdef GRAPHIC_USE_LVGL
//全局宏//////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "pa_CommonLib/src/service/graphic/lvgl/lvgl.h"
void pa_Lvgl_disp_flush_C(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    pa_Lvgl_disp_flush(disp, area, color_p);
}
bool pa_Lvgl_touchpad_read_C(lv_indev_t *indev, lv_indev_data_t *data)
{
    pa_Lvgl_touchpad_read(indev, data);
    return false;
}

void pa_Lvgl_init_C()
{
    static lv_disp_buf_t disp_buf;
    static lv_color_t buf[LV_HOR_RES_MAX * LV_VER_RES_MAX / 10]; /*Declare a buffer for 1/10 screen size*/
    static lv_indev_drv_t indev_drv;                             /*Descriptor of a input device driver*/
    static lv_disp_drv_t disp_drv;                               /*Descriptor of a display driver*/

    lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * LV_VER_RES_MAX / 10); /*Initialize the display buffer*/

    lv_disp_drv_init(&disp_drv);              /*Basic initialization*/
    disp_drv.flush_cb = pa_Lvgl_disp_flush_C; /*Set your driver function*/
    disp_drv.buffer = &disp_buf;              /*Assign the buffer to the display*/
    lv_disp_drv_register(&disp_drv);          /*Finally register the driver*/

    lv_indev_drv_init(&indev_drv);               /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;      /*Touch pad is a pointer-like device*/
    indev_drv.read_cb = pa_Lvgl_touchpad_read_C; /*Set your driver function*/
    lv_indev_drv_register(&indev_drv);           /*Finally register the driver*/
}
//全局宏//////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif