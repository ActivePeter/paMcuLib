extern "C"
{
#include "pa_MainApp.h"
#include "../../drv/pa_CommonDrv.h"
#include "../../service/tftTest/pa_TFT18.h"
#include "../../service/ssd1306/pa_oled.h"
//////////////////////////////
}
#include "Arduino.h"
// #include <U8g2lib.h>
// U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
void pa_setupApp()
{
    Serial.begin(115200);
//     u8g2.begin();  
    
//   u8g2.clearBuffer();					// clear the internal memory
//   u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
//   u8g2.drawStr(0,10,"Hello World!");	// write something to the internal memory
//   u8g2.sendBuffer();					// transfer internal memory to the display
  delay(1000); 
    pa_CommonInit();
//     // pa_TFT_initGpio();
//     // TFTSPI_CS_L ;
//     // TFTSPI_SCK_L;
//     // TFTSPI_SDI_L;
//     // TFTSPI_DC_L ;
//     // TFTSPI_RST_L;ssssss
//     // pa_spiInit();
//     delay(1000);
    
//     // ST7735_initGpio();
//     // ST7735_Init();
//     // TFTSPI_Init(0);        //LCD闂佸憡甯楃换鍌烇綖閹版澘绀岄柨鐕傛嫹  0:濠碘槅鍨兼禍婊堟儓閿燂拷  1闂佹寧绋掑銊╂偟椤愩倓娌柨鐕傛嫹
//     // TFTSPI_CLS(u16GREEN);   //闂佽棄鍟换鍡樼珶婵犲嫪娌煫鍥ㄦ尵椤旓拷

// //     digitalWrite(5, HIGH);
// //     digitalWrite(12, HIGH);
// // digitalWrite(4, HIGH);
    pa_spiInit();
    // pa_IIC_init();
    OLED_Init(Protocal_SPI);
    OLED_Clear();
    // // OLED_Fill(0,0,30,30,0xf0)
	OLED_ShowString(0, 0, "helloWorld!", 8);
    // TFTSPI_P16x16Str(0,0,"sssss",u16RED,u16BLUE);		//闁诲孩绋掗〃鍫ヮ敄娴ｅ湱鈻旈柛娆忣槹閳绘梻绱掗埀顒勬晸閿燂拷
    // TFTSPI_P8X16Str(0,1,"Long Qiu i.s.t.",u16WHITE,u16BLACK);		//闁诲孩绋掗〃鍫ヮ敄娴ｅ湱鈻旈柛娆忣槹閳绘梻绱掗埀顒勬晸閿燂拷
}
char flag=1;
void pa_loopApp()
{
//     u8g2.clearBuffer();					// clear the internal memory
//   u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
//   u8g2.drawStr(0,10,"Hello World!");	// write something to the internal memory
//   u8g2.sendBuffer();					// transfer internal memory to the display
  delay(1000);
    Serial.println("hhh");
    // MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
    // ST7735_FillRectangle(0,0,20, 20, 0x07E0); 
    // ST7735_FillScreen(0x0000);
    flag=!flag;
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