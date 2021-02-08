#include "../Tk032rb422.h"
#ifdef DISPLAY_USE_Tk032rb422
#ifdef MODULE

#define Tk032rb422_SPI_CS_Pin GPIO_PIN_2
#define Tk032rb422_SPI_CS_GPIO_Port GPIOE
#define Tk032rb422_RST_Pin GPIO_PIN_3
#define Tk032rb422_RST_GPIO_Port GPIOE
#define Tk032rb422_T_INPUT_Pin GPIO_PIN_4
#define Tk032rb422_T_INPUT_GPIO_Port GPIOE
#define Tk032rb422_SPI_SDA_T_SCL_Pin GPIO_PIN_6
#define Tk032rb422_SPI_SDA_T_SCL_GPIO_Port GPIOB
#define Tk032rb422_SPI_DCLK_T_SDA_Pin GPIO_PIN_7
#define Tk032rb422_SPI_DCLK_T_SDA_GPIO_Port GPIOB
void Tk032rb422::initHardWare(void)
{
}

void Tk032rb422::SPI_DCLK(int state)
{
    HAL_GPIO_WritePin(Tk032rb422_SPI_CS_GPIO_Port, Tk032rb422_SPI_CS_Pin, (GPIO_PinState)state);
}

void Tk032rb422::SPI_SDA(int state)
{
    Hal_GPIO_WritePin(Tk032rb422_SPI_SDA_T_SCL_GPIO_Port, Tk032rb422_SPI_SDA_T_SCL_Pin, (GPIO_PinState)state);
}

void Tk032rb422::SPI_CS(int state)
{
    Hal_GPIO_WritePin(Tk032rb422_SPI_CS_GPIO_Port, Tk032rb422_SPI_CS_Pin, (GPIO_PinState)state);
}

void Tk032rb422::Tk032rb422_setReset(int state)
{
    Hal_GPIO_WritePin(Tk032rb422_RST_GPIO_Port, Tk032rb422_RST_Pin, (GPIO_PinState)state);
}

#endif
#endif