#include "RgbConfig.h"

RgbConfig::RgbConfig(uint16_t HBP1, uint16_t VBP1,
                     uint16_t HSW1, uint16_t VSW1,
                     uint16_t HFP1, uint16_t VFP1)
{
    this->HBP = HBP1;
    this->VBP = VBP1;
    this->HSW = HSW1;
    this->VSW = VSW1;
    this->HFP = HFP1;
    this->VFP = VFP1;
}
