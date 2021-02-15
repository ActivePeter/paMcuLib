#include "pa_SDRAM.h"
#if drv_sdram
unsigned char testValue[480 * 800 * 3] __attribute__((section(".RAM_Array")));
namespace SDRAM
{

    using namespace drv;
    void init()
    {

        sendCommand(FMC_SDRAM_CMD_CLK_ENABLE, 1, 1, 0); //步骤3：使能时钟信号，SDCKE0 = 1
        pa_delayMs(1);
        // Delay_us(500);                                              //步骤4：至少延时200us
        sendCommand(FMC_SDRAM_CMD_PALL, 1, 1, 0);             //步骤5：发送全部预充电命令
        sendCommand(FMC_SDRAM_CMD_AUTOREFRESH_MODE, 1, 8, 0); //步骤6：设置自动刷新次数

        uint32_t temp = SDRAM_MODEREG_BURST_LENGTH_1 |          //设置突发长度：1
                        SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |   //设置突发类型：连续
                        SDRAM_MODEREG_CAS_LATENCY_3 |           //设置CAS值：3
                        SDRAM_MODEREG_OPERATING_MODE_STANDARD | //设置操作模式：标准
                        SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;   //设置突发写模式：单点访问
        sendCommand(FMC_SDRAM_CMD_LOAD_MODE, 1, 1, temp);       //步骤7：装载模式寄存器的值

        setRate();
        pa_delayMs(1);
        // testValue[0] = 1;
        memset(testValue, 0, sizeof(testValue));
    }
    char testk = 1;

    void test()
    {
        // static
        // unsigned int *sdram_ptr = testValue; //(unsigned int *)0xC0000000;

        for (int i = 0; i < 480 * 800 * 3; i += 3)
        {
            if (testk == 0)
            {
                // testValue[i] = 0xff;
                // testValue[i + 1] = 0x00;
                // testValue[i + 2] = 0x00;
                TM_SDRAM_Write8(i, 0xff);
                TM_SDRAM_Write8(i + 1, 0x00);
                TM_SDRAM_Write8(i + 2, 0x00);
                // *(testValue + i) = 0xff;
                // *(testValue + i + 1) = 0x00;
                // *(testValue + i + 2) = 0x00;
            }
            else if (testk == 1)
            {
                TM_SDRAM_Write8(i, 0x00);
                TM_SDRAM_Write8(i + 1, 0xff);
                TM_SDRAM_Write8(i + 2, 0x00);
                // testValue[i] = 0x00;
                // testValue[i + 1] = 0xff;
                // testValue[i + 2] = 0x00;
                // *(testValue + i) = 0x00;
                // *(testValue + i + 1) = 0xff;
                // *(testValue + i + 2) = 0x00;
            }
            else
            {
                TM_SDRAM_Write8(i, 0x00);
                TM_SDRAM_Write8(i + 1, 0x00);
                TM_SDRAM_Write8(i + 2, 0xff);
                // testValue[i] = 0x00;
                // testValue[i + 1] = 0x00;
                // testValue[i + 2] = 0xff;
                // *(testValue + i) = 0x00;
                // *(testValue + i + 1) = 0x00;
                // *(testValue + i + 2) = 0xff;
            }
            // if (testk == 0)
            // {
            //     if ((i) % 3 == 0)
            //     {
            //         *sdram_ptr++ = 0x0000ff00;
            //     }
            //     else if (i % 3 == 1)
            //     {
            //         *sdram_ptr++ = 0xff0000ff;
            //     }
            //     else
            //     {
            //         *sdram_ptr++ = 0x00ff0000;
            //     }
            // }
            // else if (testk == 1)
            // {
            //     if (i % 3 == 1)
            //     {
            //         *sdram_ptr++ = 0x0000ff00;
            //     }
            //     else if (i % 3 == 2)
            //     {
            //         *sdram_ptr++ = 0xff0000ff;
            //     }
            //     else
            //     {
            //         *sdram_ptr++ = 0x00ff0000;
            //     }
            // }
            // else
            // {
            //     if (i % 3 == 2)
            //     {
            //         *sdram_ptr++ = 0x0000ff00;
            //     }
            //     else if (i % 3 == 0)
            //     {
            //         *sdram_ptr++ = 0xff0000ff;
            //     }
            //     else
            //     {
            //         *sdram_ptr++ = 0x00ff0000;
            //     }
            // }
        }

        testk++;
        if (testk == 3)
        {
            testk = 0;
        }
    }
} // namespace SDRAM
#endif
