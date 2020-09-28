
#include "pa_Defines.h"

#ifdef INPUT_USE_TOUCHSCREEN

#ifndef __PA_TOUCHSCREEN_H__
#define __PA_TOUCHSCREEN_H__

extern "C"
{
#include "../../../drv/pa_CommonDrv/pa_CommonDrv.h"
}
class pa_touchScreen
{

public:
  static pa_touchScreen instance;
  pa_touchScreen();
  void init(uint16_t screenWidth, uint16_t screenHeight);
  uint8_t readCoordinates(uint16_t Coordinates[2]);
  uint8_t isPressed();
  struct ConfigModel
  {
    uint16_t SampleCount;
    uint16_t X_OFFSET;
    uint16_t Y_OFFSET;
    float X_MAGNITUDE;
    float Y_MAGNITUDE;
    uint16_t X_TRANSLATION;
    uint16_t Y_TRANSLATION;
  };
  //不要修改此处的数据。因为只是个默认值
  ConfigModel config = {
      1000, //SampleCount
      13,   //X_OFFSET
      15,   //Y_OFFSET
      1.16, //X_MAGNITUDE
      1.16, //Y_MAGNITUDE
      //CONVERTING 16bit Value to Screen coordinates
      // 65535/273 = 240!
      // 65535/204 = 320!
      273, //X_TRANSLATION  (will be replaced
      204  //Y_TRANSLATION   (will be replaced
  };
  void Hardware_SetCS(uint8_t state);
private:
  enum CMDs
  {
    CMD_RDY = 0X90,
    CMD_RDX = 0XD0
  };

  void Hardware_Init();
  uint8_t Hardware_ReadIRQ();
  

  uint16_t spiRead();
  void spiWrite(uint8_t value);
};

#endif
#endif // __PA_TOUCHSCREEN_H__