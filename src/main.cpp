#include <WiFi.h>
extern "C"{
  #include "pa_CommonLib/app/pa_MainApp/pa_MainApp.h"
}

void setup()
{
  
  pa_setupApp();
}

void loop()
{
  pa_loopApp();
}