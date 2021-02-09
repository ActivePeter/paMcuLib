#ifdef __cplusplus
#ifndef __PA_LTDC_H__
#define __PA_LTDC_H__

#include "all_config.h"

#if drv_ltdc

class RgbConfig;

#include "paLib/service/display/_RgbScreen/RgbConfig.hpp"
//class RgbConfig;
void Ltdc_init(RgbConfig rgbConfig);
#endif

#endif // __PA_LTDC_H__
#endif
