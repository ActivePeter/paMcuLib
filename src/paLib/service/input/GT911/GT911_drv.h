#ifndef __GT911_DRV_H__
#define __GT911_DRV_H__
#include "paLib/drv/pa_BaseDrv/pa_BaseDrv.h"
#if using_GT911
#include "GT911.h"
#define GT911_Delay(ms) pa_delayMs(ms)
namespace GT911
{
    void hardwareInit();
    void GT911_INT_Input(void);

    void GT911_INT_Output(void);

    void GT911_RST_Control(bool high_or_low);
    void GT911_INT_Control(bool high_or_low);

    GT911_Status_t GT911_I2C_Init(void);

    GT911_Status_t GT911_I2C_Write(uint8_t Addr, uint8_t *write_data, uint16_t write_length);

    GT911_Status_t GT911_I2C_Read(uint8_t Addr, uint8_t *read_data, uint16_t read_length);
} // namespace GT911
#endif
#endif // __GT911_DRV_H__