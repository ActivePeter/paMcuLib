#include "GT911_drv.h"
#if using_GT911
#include "paLib/drv/pa_Gpio/pa_Gpio.h"
namespace GT911
{
    void GT911_INT_Input(void)
    {
        Gpio_setMode(GT911_int_gpio, GpioMode_Input_Float, GpioSpeed_Medium);
    }

    void GT911_INT_Output(void)
    {
        Gpio_setMode(GT911_int_gpio, GpioMode_Output_PP, GpioSpeed_Medium);
        // Gpio_write(GT911_int_gpio, 0);
    }

    void GT911_RST_Control(bool high_or_low)
    {
        Gpio_write(GT911_rst_gpio, high_or_low);
    }
    void GT911_INT_Control(bool high_or_low)
    {
        Gpio_write(GT911_int_gpio, high_or_low);
    }

    void hardwareInit()
    {
        Gpio_setMode(GT911_rst_gpio, GpioMode_Output_PP, GpioSpeed_Medium);
    }

    GT911_Status_t GT911_I2C_Init(void)
    {
        return GT911_OK;
    }

    GT911_Status_t GT911_I2C_Write(uint8_t Addr, uint8_t *write_data, uint16_t write_length)
    {
        iic_status status = pa_IIC_directly_write(GT911_iic_id, Addr, write_length, write_data);
        if (status == iic_succ)
        {
            return GT911_Status_t::GT911_OK;
        }
        else
        {
            return GT911_Error;
        }
        // uint8_t Address = Addr << 1;
        // switch (HAL_I2C_Master_Transmit(&hi2c1, Address, write_data, write_length, HAL_MAX_DELAY))
        // {
        // case HAL_OK:
        //     return GT911_OK;
        //     break;
        // case HAL_ERROR:
        //     return GT911_Error;
        //     break;
        // case HAL_BUSY:
        // case HAL_TIMEOUT:
        //     return GT911_NotResponse;
        //     break;
        // }
        // return GT911_Error;
    }

    GT911_Status_t GT911_I2C_Read(uint8_t Addr, uint8_t *read_data, uint16_t read_length)
    {
        uint8_t Address = Addr << 1;
        iic_status status = pa_IIC_directly_read(GT911_iic_id, Addr, read_length, read_data);
        if (status == iic_succ)
        {
            return GT911_Status_t::GT911_OK;
        }
        else
        {
            return GT911_Error;
        }
        // switch (HAL_I2C_Master_Receive(&hi2c1, Address, read_data, read_length, HAL_MAX_DELAY))
        // {
        // case HAL_OK:
        //     return GT911_OK;
        //     break;
        // case HAL_ERROR:
        //     return GT911_Error;
        //     break;
        // case HAL_BUSY:
        // case HAL_TIMEOUT:
        //     return GT911_NotResponse;
        //     break;
        // }
        // return HAL_ERROR;
    }
} // namespace GT911
#endif
