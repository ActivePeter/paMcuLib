extern "C"
{
#include "pa_MainApp.h"
#include "../../drv/pa_CommonDrv.h"
#include "../../service/tftTest/pa_TFT18.h"
#include "../../service/ssd1306/pa_oled.h"
#include "../../service/pa_Keypad/pa_Keypad.h"
#include "stdio.h"
	//////////////////////////////
}


void hhh(unsigned char x, unsigned char y) {
	{
		char buffer[30] = { 0 };
		sprintf(buffer, "%d %d ", x, y);
		OLED_ShowString(0, 1, buffer, 8);
	}
	
}

void pa_setupApp()
{

	pa_CommonInit();
	// pa_TFT_initGpio();
	// TFTSPI_CS_L ;
	// TFTSPI_SCK_L;
	// TFTSPI_SDI_L;
	// TFTSPI_DC_L ;
	// TFTSPI_RST_L;
	pa_spiInit();
	pa_IIC_init();
	// ST7735_initGpio();
	// ST7735_Init();
	// TFTSPI_Init(0);        //LCD閸掓繂顫愰崠锟�  0:濡亜鐫�  1閿涙氨鐝仦锟�
	// TFTSPI_CLS(u16GREEN);   //閽冩繆澹婄仦蹇撶

	OLED_Init(Protocal_IIC);
	OLED_Clear();
	OLED_ShowString(0, 0, "helloWorld!", 8);
	// pa_delayMs(1000);
	OLED_Init(Protocal_SPI);
	OLED_Clear();
	OLED_ShowString(0, 0, "helloWorld!", 8);

	pa_Keypad::instance.init(GpioInputMode_pullup);
	pa_Keypad::instance.keypadCallback = hhh;
	// TFTSPI_P16x16Str(0,0,"sssss",u16RED,u16BLUE);		//鐎涙顑佹稉鍙夋▔缁€锟�
	// TFTSPI_P8X16Str(0,1,"Long Qiu i.s.t.",u16WHITE,u16BLACK);		//鐎涙顑佹稉鍙夋▔缁€锟�
}
char flag = 1;
void pa_loopApp()
{
	pa_Keypad::instance.loop();
	MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
	// ST7735_FillRectangle(0,0,20, 20, 0x07E0); 
	// ST7735_FillScreen(0x0000);
	// flag=!flag;
	// if(flag){
	//     TFTSPI_CLS(u16GREEN);
	// }else{
	//     TFTSPI_CLS(u16BLUE);
	// }
	// int a=100;
	// while(a){
	//     a--;
	//     int b=100;
	//     while(b){
	//         b--;
	//     }
	// }
	//pa_delayMs(1000);
}