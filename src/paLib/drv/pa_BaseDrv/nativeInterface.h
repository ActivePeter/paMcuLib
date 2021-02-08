#include "_all_config.h"
#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"
#include "stdarg.h"
#include <stdio.h>
#include <stdlib.h>

#if mcu_stm32_h7
#include "stm32h7xx_hal.h"
#include "cmsis_os.h"
#elif mcu_esp32_arduino
#include "esp32-hal.h"
#endif

#ifdef __cplusplus
}
#endif
