// extern "C"
// {
// #include "pa_MainApp.h"
// #include "../../drv/pa_CommonDrv.h"
// #include "../../service/ssd1306/pa_oled.h"
// #include "../../service/pa_Keypad/pa_Keypad.h"
// #include "../../service/st7789/lcd.h"

// #include "stdio.h"
// 	//////////////////////////////
// }


// void hhh(unsigned char x, unsigned char y) {
// 	{
// 		char buffer[30] = { 0 };
// 		sprintf(buffer, "%d %d ", x, y);
// 		OLED_ShowString(0, 1, buffer, 8);
// 	}
	
// }

// void pa_setupApp()
// {

// 	pa_CommonInit();
// 	// pa_TFT_initGpio();
// 	// TFTSPI_CS_L ;
// 	// TFTSPI_SCK_L;
// 	// TFTSPI_SDI_L;
// 	// TFTSPI_DC_L ;
// 	// TFTSPI_RST_L;
// 	pa_spiInit();
// 	LCD_Init();//LCD初始化
// 	LCD_Fill(0,0,200,200,GREEN);
// 	// pa_IIC_init();
// 	// ST7735_initGpio();
// 	// ST7735_Init();

// 	// OLED_Init(Protocal_IIC);
// 	// OLED_Clear();
// 	// OLED_ShowString(0, 0, "helloWorld!", 8);
// 	// // pa_delayMs(1000);
// 	// OLED_Init(Protocal_SPI);
// 	// OLED_Clear();
// 	// OLED_ShowString(0, 0, "helloWorld!", 8);

// 	pa_Keypad::instance.init(GpioInputMode_pullup);
// 	pa_Keypad::instance.keypadCallback = hhh;
// }
// char flag = 1;
// void pa_loopApp()
// {
// 	pa_Keypad::instance.loop();
// 	MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
// 	// ST7735_FillRectangle(0,0,20, 20, 0x07E0); 
// 	// ST7735_FillScreen(0x0000);
// 	flag=!flag;
// 	if(flag){
// 	    LCD_Fill(0,0,200,200,GREEN);
// 	}else{
// 	    LCD_Fill(0,0,200,200,RED);
// 	}
// 	// int a=100;
// 	// while(a){
// 	//     a--;
// 	//     int b=100;
// 	//     while(b){
// 	//         b--;
// 	//     }
// 	// }
// 	//pa_delayMs(1000);
// }