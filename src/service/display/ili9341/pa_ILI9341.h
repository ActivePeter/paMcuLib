#include "../../../drv/pa_CommonDrv/pa_CommonDrv.h"

#ifdef DISPLAY_USE_ILI9341

#ifndef __ILI9341_H__
#define __ILI9341_H__

class pa_ILI9341
{

public:
  enum Rotation
  {
    Rotation_VERTICAL_1 = 0,
    Rotation_HORIZONTAL_1,
    Rotation_VERTICAL_2,
    Rotation_HORIZONTAL_2
  };
  pa_ILI9341();
  static pa_ILI9341 instance;
  void init(Rotation Rotation);
  void flush(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t Colour);
  void burst(uint16_t Colour, uint32_t Size);
  void setAddress(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2);

  void setCS(uint8_t state);
  void setDC(uint8_t state);
  void setRST(uint8_t state);
  unsigned char pa_ILI9341_burst_buffer[500];

private:
  short LCD_WIDTH;
  short LCD_HEIGHT;

  const short BURST_MAX_SIZE = 500;

  void reset();
  void enable();

  void writeCommand(uint8_t Command);
  void writeData(uint8_t Command);

  void setRotation(Rotation Rotation);
};

#endif // __ILI9341_H__

#endif