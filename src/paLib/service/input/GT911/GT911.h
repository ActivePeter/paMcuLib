#ifndef __GT911_H__
#define __GT911_H__
#include "paLib/drv/pa_BaseDrv/pa_BaseDrv.h"
#include "../touch_screen_general_part.h"
#if using_GT911

namespace GT911
{
    typedef enum
    {
        GT911_OK = 0,
        GT911_Error = 1,
        GT911_NotResponse = 2
    } GT911_Status_t;
    typedef struct
    {
        uint16_t X_Resolution;
        uint16_t Y_Resolution;
        uint8_t Number_Of_Touch_Support;
        bool ReverseX;
        bool ReverseY;
        bool SwithX2Y;
        bool SoftwareNoiseReduction;

    } GT911_Config_t;
    /* Exported functions ------------------------------------------------------- */
    GT911_Status_t GT911_Init(GT911_Config_t config);
    GT911_Status_t GT911_ReadTouch(TouchCordinate_t *cordinate, uint8_t *number_of_cordinate);
} // namespace GT911
#endif
#endif // __GT911_H__