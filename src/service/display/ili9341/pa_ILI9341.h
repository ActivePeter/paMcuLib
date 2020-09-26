#include "pa_CommonLib/src/pa_Defines.h"

#ifdef DISPLAY_USE_ILI9341

#ifndef __ILI9341_H__
#define __ILI9341_H__
extern "C"
{
#include "../../../drv/pa_CommonDrv.h"
}
class pa_ILI9341
{

  enum Rotation
  {
    Rotation_VERTICAL_1 = 0,
    Rotation_HORIZONTAL_1,
    Rotation_VERTICAL_2,
    Rotation_HORIZONTAL_2
  };

public:
  pa_ILI9341();
  static pa_ILI9341 instance;
  void init();
  void flush(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t Colour);
  void burst(uint16_t Colour, uint32_t Size);

private:
  short LCD_WIDTH;
  short LCD_HEIGHT;

  const short BURST_MAX_SIZE = 500;

  void reset();
  void enable();
  
  void writeCommand(uint8_t Command);
  void writeData(uint8_t Command);
  void setAddress(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2);
  void setRotation(uint8_t Rotation);

  void setCS(uint8_t state);
  void setDC(uint8_t state);
  void setRST(uint8_t state);
};

#endif // __ILI9341_H__

#endif