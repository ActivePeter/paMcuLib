#ifndef __TFT_drv_H__
#define __TFT_drv_H__	
extern "C"
{
#include "../../drv/pa_CommonDrv.h"
}
#ifdef MSP432P
#define TFTSPI_CS_Port GPIO_PORT_P3
#define TFTSPI_CS_Pin GPIO_PIN3

#define TFTSPI_SCK_Port GPIO_PORT_P1
#define TFTSPI_SCK_Pin GPIO_PIN5

#define TFTSPI_SDI_Port GPIO_PORT_P1
#define TFTSPI_SDI_Pin GPIO_PIN6

#define TFTSPI_DC_Port GPIO_PORT_P4
#define TFTSPI_DC_Pin GPIO_PIN1

#define TFTSPI_RST_Port GPIO_PORT_P3
#define TFTSPI_RST_Pin GPIO_PIN2

#define TFTSPI_CS_H     MAP_GPIO_setOutputHighOnPin(TFTSPI_CS_Port, TFTSPI_CS_Pin);      /*!< CS管脚 */
#define TFTSPI_SCK_H    MAP_GPIO_setOutputHighOnPin(TFTSPI_SCK_Port, TFTSPI_SCK_Pin);     /*!< SCL管脚 */
#define TFTSPI_SDI_H    MAP_GPIO_setOutputHighOnPin(TFTSPI_SDI_Port, TFTSPI_SDI_Pin);     /*!< SDI管脚 */
#define TFTSPI_DC_H     MAP_GPIO_setOutputHighOnPin(TFTSPI_DC_Port, TFTSPI_DC_Pin);     /*!< DC管脚 */
#define TFTSPI_RST_H    MAP_GPIO_setOutputHighOnPin(TFTSPI_RST_Port, TFTSPI_RST_Pin);     /*!< RST管脚 */

#define TFTSPI_CS_L     MAP_GPIO_setOutputLowOnPin(TFTSPI_CS_Port, TFTSPI_CS_Pin);        /*!< CS管脚 */
#define TFTSPI_SCK_L    MAP_GPIO_setOutputLowOnPin(TFTSPI_SCK_Port, TFTSPI_SCK_Pin);     /*!< SCL管脚 */
#define TFTSPI_SDI_L    MAP_GPIO_setOutputLowOnPin(TFTSPI_SDI_Port, TFTSPI_SDI_Pin);    /*!< SDI管脚 */
#define TFTSPI_DC_L     MAP_GPIO_setOutputLowOnPin(TFTSPI_DC_Port, TFTSPI_DC_Pin);        /*!< DC管脚 */
#define TFTSPI_RST_L    MAP_GPIO_setOutputLowOnPin(TFTSPI_RST_Port, TFTSPI_RST_Pin);     /*!< RST管脚 */
#endif

#ifdef ESP32

#define TFTSPI_CS_Port 15
#define TFTSPI_DC_Port 12
#define TFTSPI_RST_Port 4

#define TFTSPI_CS_H     digitalWrite(TFTSPI_CS_Port, HIGH);//MAP_GPIO_setOutputHighOnPin(TFTSPI_CS_Port, TFTSPI_CS_Pin);      /*!< CS管脚 */
#define TFTSPI_DC_H     digitalWrite(TFTSPI_DC_Port, HIGH);//MAP_GPIO_setOutputHighOnPin(TFTSPI_DC_Port, TFTSPI_DC_Pin);     /*!< DC管脚 */
#define TFTSPI_RST_H    digitalWrite(TFTSPI_RST_Port, HIGH);//MAP_GPIO_setOutputHighOnPin(TFTSPI_RST_Port, TFTSPI_RST_Pin);     /*!< RST管脚 */

#define TFTSPI_CS_L     digitalWrite(TFTSPI_CS_Port, LOW);//MAP_GPIO_setOutputLowOnPin(TFTSPI_CS_Port, TFTSPI_CS_Pin);        /*!< CS管脚 */
#define TFTSPI_DC_L     digitalWrite(TFTSPI_DC_Port, LOW);//MAP_GPIO_setOutputLowOnPin(TFTSPI_DC_Port, TFTSPI_DC_Pin);        /*!< DC管脚 */
#define TFTSPI_RST_L    digitalWrite(TFTSPI_RST_Port, LOW);//MAP_GPIO_setOutputLowOnPin(TFTSPI_RST_Port, TFTSPI_RST_Pin);     /*!< RST管脚 */
#endif

void pa_TFT_initGpio();


#endif