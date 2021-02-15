#include "GT911.h"
#include "GT911_drv.h"
#if using_GT911

#define GOODIX_ADDRESS 0x5D //0x14

// Write only registers
#define GOODIX_REG_COMMAND 0x8040
#define GOODIX_REG_ESD_CHECK 0x8041
#define GOODIX_REG_PROXIMITY_EN 0x8042

// Read/write registers
// The version number of the configuration file
#define GOODIX_REG_CONFIG_DATA 0x8047
// X output maximum value (LSB 2 bytes)
#define GOODIX_REG_MAX_X 0x8048
// Y output maximum value (LSB 2 bytes)
#define GOODIX_REG_MAX_Y 0x804A
// Maximum number of output contacts: 1~5 (4 bit value 3:0, 7:4 is reserved)
#define GOODIX_REG_MAX_TOUCH 0x804C

// Module switch 1
// 7:6 Reserved, 5:4 Stretch rank, 3 X2Y, 2 SITO (Single sided ITO touch screen), 1:0 INT Trigger mode */
#define GOODIX_REG_MOD_SW1 0x804D
// Module switch 2
// 7:1 Reserved, 0 Touch key */
#define GOODIX_REG_MOD_SW2 0x804E

// Number of debuffs fingers press/release
#define GOODIX_REG_SHAKE_CNT 0x804F

// X threshold
#define GOODIX_REG_X_THRESHOLD 0x8057

//Configuration update fresh
#define GOODIX_REG_CONFIG_FRESH 0x8100

// ReadOnly registers (device and coordinates info)
// Product ID (LSB 4 bytes, GT9110: 0x06 0x00 0x00 0x09)
#define GOODIX_REG_ID 0x8140
// Firmware version (LSB 2 bytes)
#define GOODIX_REG_FW_VER 0x8144

// Current output X resolution (LSB 2 bytes)
#define GOODIX_READ_X_RES 0x8146
// Current output Y resolution (LSB 2 bytes)
#define GOODIX_READ_Y_RES 0x8148
// Module vendor ID
#define GOODIX_READ_VENDOR_ID 0x814A

#define GOODIX_READ_COORD_ADDR 0x814E

#define GOODIX_POINT1_X_ADDR 0x8150
#define GOODIX_POINT1_Y_ADDR 0x8152

/* Commands for REG_COMMAND */
//0: read coordinate state
#define GOODIX_CMD_READ 0x00
// 1: difference value original value
#define GOODIX_CMD_DIFFVAL 0x01
// 2: software reset
#define GOODIX_CMD_SOFTRESET 0x02
// 3: Baseline update
#define GOODIX_CMD_BASEUPDATE 0x03
// 4: Benchmark calibration
#define GOODIX_CMD_CALIBRATE 0x04
// 5: Off screen (send other invalid)
#define GOODIX_CMD_SCREEN_OFF 0x05
namespace GT911
{
    static uint8_t GT911_Config[] = {
        0x81, 0x00, 0x04, 0x58, 0x02, 0x0A, 0x0C, 0x20, 0x01, 0x08, 0x28, 0x05, 0x50, // 0x8047 - 0x8053
        0x3C, 0x0F, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x8054 - 0x8060
        0x00, 0x89, 0x2A, 0x0B, 0x2D, 0x2B, 0x0F, 0x0A, 0x00, 0x00, 0x01, 0xA9, 0x03, // 0x8061 - 0x806D
        0x2D, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, // 0x806E - 0x807A
        0x59, 0x94, 0xC5, 0x02, 0x07, 0x00, 0x00, 0x04, 0x93, 0x24, 0x00, 0x7D, 0x2C, // 0x807B - 0x8087
        0x00, 0x6B, 0x36, 0x00, 0x5D, 0x42, 0x00, 0x53, 0x50, 0x00, 0x53, 0x00, 0x00, // 0x8088	- 0x8094
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x8095 - 0x80A1
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x80A2 - 0x80AD
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, // 0x80AE - 0x80BA
        0x0C, 0x0E, 0x10, 0x12, 0x14, 0x16, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, // 0x80BB - 0x80C7
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x80C8 - 0x80D4
        0x02, 0x04, 0x06, 0x08, 0x0A, 0x0F, 0x10, 0x12, 0x16, 0x18, 0x1C, 0x1D, 0x1E, // 0x80D5 - 0x80E1
        0x1F, 0x20, 0x21, 0x22, 0x24, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, // 0x80E2 - 0x80EE
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x80EF - 0x80FB
        0x00, 0x00, 0xD6, 0x01};                                                      // 0x80FC - 0x8100
    static GT911_Status_t CommunicationResult;
    static uint8_t TxBuffer[200];
    static uint8_t RxBuffer[200];
    /* Private function prototypes -----------------------------------------------*/
    static void GT911_Reset(void);
    static void GT911_CalculateCheckSum(void);
    static GT911_Status_t GT911_SetCommandRegister(uint8_t command);
    static GT911_Status_t GT911_GetProductID(uint32_t *id);
    static GT911_Status_t GT911_SendConfig(void);
    static GT911_Status_t GT911_GetStatus(uint8_t *status);
    static GT911_Status_t GT911_SetStatus(uint8_t status);
    /* API Implementation --------------------------------------------------------*/
    GT911_Status_t GT911_Init(GT911_Config_t config)
    {
        hardwareInit();
        //	Set X resolution
        GT911_Config[1] = config.X_Resolution & 0x00FF;
        GT911_Config[2] = (config.X_Resolution >> 8) & 0x00FF;
        //	Set Y resolution
        GT911_Config[3] = config.Y_Resolution & 0x00FF;
        GT911_Config[4] = (config.Y_Resolution >> 8) & 0x00FF;
        //  Set touch number
        GT911_Config[5] = config.Number_Of_Touch_Support;
        //  set reverse Y
        GT911_Config[6] = 0;
        GT911_Config[6] |= config.ReverseY << 7;
        //  set reverse X
        GT911_Config[6] |= config.ReverseX << 6;
        //  set switch X2Y
        GT911_Config[6] |= config.SwithX2Y << 3;
        //  set Sito
        GT911_Config[6] |= config.SoftwareNoiseReduction << 2;

        //Reset chip
        GT911_Reset();
        //Get product ID
        uint32_t productID = 0;
        CommunicationResult = GT911_GetProductID(&productID);
        if (CommunicationResult != GT911_OK)
        {
            return CommunicationResult;
        }
        if (productID == 0)
        {
            return GT911_NotResponse;
        }
        //Reset chip
        GT911_Reset();
        CommunicationResult = GT911_SendConfig();
        if (CommunicationResult != GT911_OK)
        {
            return CommunicationResult;
        }
        GT911_SetCommandRegister(0x00);
        return GT911_OK;
    }

    GT911_Status_t GT911_ReadTouch(TouchCordinate_t *cordinate, uint8_t *number_of_cordinate)
    {
        uint8_t StatusRegister;
        GT911_Status_t Result = GT911_NotResponse;
        Result = GT911_GetStatus(&StatusRegister);
        if (Result != GT911_OK)
        {
            return Result;
        }
        if ((StatusRegister & 0x80) != 0)
        {
            *number_of_cordinate = StatusRegister & 0x0F;
            if (*number_of_cordinate != 0)
            {
                for (uint8_t i = 0; i < *number_of_cordinate; i++)
                {
                    TxBuffer[0] = ((GOODIX_POINT1_X_ADDR + (i * 8)) & 0xFF00) >> 8;
                    TxBuffer[1] = (GOODIX_POINT1_X_ADDR + (i * 8)) & 0xFF;
                    GT911_I2C_Write(GOODIX_ADDRESS, TxBuffer, 2);
                    GT911_I2C_Read(GOODIX_ADDRESS, RxBuffer, 6);
                    cordinate[i].x = RxBuffer[0];
                    cordinate[i].x = (RxBuffer[1] << 8) + cordinate[i].x;
                    cordinate[i].y = RxBuffer[2];
                    cordinate[i].y = (RxBuffer[3] << 8) + cordinate[i].y;
                }
            }
            GT911_SetStatus(0);
        }
        return GT911_OK;
    }

    //Private functions Implementation ---------------------------------------------------------*/
    static void GT911_Reset(void)
    {
        GT911_INT_Output();

        GT911_RST_Control(0);
        // GT911_Delay(20);
        GT911_INT_Control(0);
        GT911_Delay(5);
        GT911_RST_Control(1);
        GT911_Delay(10);
        GT911_INT_Input();
        GT911_Delay(10);
    }

    static void GT911_CalculateCheckSum(void)
    {
        GT911_Config[184] = 0;
        for (uint8_t i = 0; i < 184; i++)
        {
            GT911_Config[184] += GT911_Config[i];
        }
        GT911_Config[184] = (~GT911_Config[184]) + 1;
    }

    static GT911_Status_t GT911_SetCommandRegister(uint8_t command)
    {
        TxBuffer[0] = (GOODIX_REG_COMMAND & 0xFF00) >> 8;
        TxBuffer[1] = GOODIX_REG_COMMAND & 0xFF;
        TxBuffer[2] = command;
        return GT911_I2C_Write(GOODIX_ADDRESS, TxBuffer, 3);
    }

    static GT911_Status_t GT911_GetProductID(uint32_t *id)
    {
        TxBuffer[0] = (GOODIX_REG_ID & 0xFF00) >> 8;
        TxBuffer[1] = GOODIX_REG_ID & 0xFF;
        GT911_Status_t Result = GT911_NotResponse;
        Result = GT911_I2C_Write(GOODIX_ADDRESS, TxBuffer, 2);
        if (Result == GT911_OK)
        {
            Result = GT911_I2C_Read(GOODIX_ADDRESS, RxBuffer, 4);
            if (Result == GT911_OK)
            {
                memcpy(id, RxBuffer, 4);
            }
        }
        return Result;
    }

    static GT911_Status_t GT911_SendConfig(void)
    {
        GT911_CalculateCheckSum();
        TxBuffer[0] = (GOODIX_REG_CONFIG_DATA & 0xFF00) >> 8;
        TxBuffer[1] = GOODIX_REG_CONFIG_DATA & 0xFF;
        memcpy(&TxBuffer[2], GT911_Config, sizeof(GT911_Config));
        return GT911_I2C_Write(GOODIX_ADDRESS, TxBuffer, sizeof(GT911_Config) + 2);
    }

    static GT911_Status_t GT911_GetStatus(uint8_t *status)
    {
        TxBuffer[0] = (GOODIX_READ_COORD_ADDR & 0xFF00) >> 8;
        TxBuffer[1] = GOODIX_READ_COORD_ADDR & 0xFF;
        GT911_Status_t Result = GT911_NotResponse;
        Result = GT911_I2C_Write(GOODIX_ADDRESS, TxBuffer, 2);
        if (Result == GT911_OK)
        {
            Result = GT911_I2C_Read(GOODIX_ADDRESS, RxBuffer, 1);
            if (Result == GT911_OK)
            {
                *status = RxBuffer[0];
            }
        }
        return Result;
    }

    static GT911_Status_t GT911_SetStatus(uint8_t status)
    {
        TxBuffer[0] = (GOODIX_READ_COORD_ADDR & 0xFF00) >> 8;
        TxBuffer[1] = GOODIX_READ_COORD_ADDR & 0xFF;
        TxBuffer[2] = status;
        return GT911_I2C_Write(GOODIX_ADDRESS, TxBuffer, 3);
    }
#endif
}