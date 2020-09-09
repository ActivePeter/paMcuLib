// #define OLED_CS_Port GPIO_PORT_P4
// #define OLED_CS_Pin GPIO_PIN1

// #define OLED_DC_Port GPIO_PORT_P4
// #define OLED_DC_Pin GPIO_PIN2

// #define OLED_RST_Port GPIO_PORT_P4
// #define OLED_RST_Pin GPIO_PIN0

// // D0                         4 线 ISP 接口模式：时钟线（CLK）
// // D1                         4 线 ISP 接口模式：串行数据线（MOSI）
// void OLED_initSpiGpio(){
//     GPIO_setAsOutputPin(OLED_CS_Port, OLED_CS_Pin);   
//     GPIO_setAsOutputPin(OLED_DC_Port, OLED_DC_Pin);   
//     GPIO_setAsOutputPin(OLED_RST_Port, OLED_RST_Pin); 
// }

// void OLED_setCS(char state){
//     if(state){
//         MAP_GPIO_setOutputHighOnPin(OLED_CS_Port, OLED_CS_Pin);
//     }else{
//         MAP_GPIO_setOutputLowOnPin(OLED_CS_Port, OLED_CS_Pin);
//     }
// }

// void OLED_setDC(char state){
//     if(state){
//         MAP_GPIO_setOutputHighOnPin(OLED_DC_Port, OLED_DC_Pin);
//     }else{
//         MAP_GPIO_setOutputLowOnPin(OLED_DC_Port, OLED_DC_Pin);
//     }
// }
// void OLED_setRST(char state){
//     if(state){
//         MAP_GPIO_setOutputHighOnPin(OLED_RST_Port, OLED_RST_Pin);
//     }else{
//         MAP_GPIO_setOutputLowOnPin(OLED_RST_Port, OLED_RST_Pin);
//     }
// }