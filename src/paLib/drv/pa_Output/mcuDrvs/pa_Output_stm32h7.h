#ifndef __PA_OUTPUT_STM32H7_H__
#define __PA_OUTPUT_STM32H7_H__

#include "all_config.h"
#if output_use_cdc

#include "paLib/drv/pa_USB/STM32_USB_Device_Library/Class/CDC/usbd_cdc_if.h"
#include "string.h"
#define cdc_print(data) CDC_Transmit_FS((uint8_t *)data, strlen(data));

#endif

#endif // __PA_OUTPUT_STM32H7_H__