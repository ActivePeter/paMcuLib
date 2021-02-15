#include "../pa_SDRAM.h"
#if drv_sdram
#if mcu_stm32_h7
extern SDRAM_HandleTypeDef hsdram1;
namespace SDRAM
{
    namespace drv
    {

        uint8_t
        sendCommand(
            uint32_t CommandMode,
            uint32_t Bank,
            uint32_t RefreshNum,
            uint32_t RegVal)
        {
            uint32_t CommandTarget;
            FMC_SDRAM_CommandTypeDef Command;

            if (Bank == 1)
                CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
            else if (Bank == 2)
                CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;

            Command.CommandMode = CommandMode;
            Command.CommandTarget = CommandTarget;
            Command.AutoRefreshNumber = RefreshNum;
            Command.ModeRegisterDefinition = RegVal;
            if (HAL_SDRAM_SendCommand(&hsdram1, &Command, 0x1000) == HAL_OK)
                return 1;
            else
            {
                while (1)
                {
                }
            }
        }

        void setRate()
        {
            //SDRAM刷新周期是64ms，行数是8192行，时钟频率是180MHz/2=90MHz
            //所有COUNT = (64ms/8192)/(1/90us)-20 = 64000*90/8192-20 = 683
            if (HAL_SDRAM_ProgramRefreshRate(&hsdram1, 683) != HAL_OK)
            {
                while (1)
                {
                }
            } //步骤8：设置刷新速率
        }

    } // namespace drv
} // namespace SDRAM
#endif
#endif