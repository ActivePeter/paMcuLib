1. ## 先确保vscode 安装了我的两个插件

   [ActivePeter/SubmoduleHelper-vscode: I'm going to write a vscode extension available to choose needed submodules and auto load them, just like some package manager. (github.com)](https://github.com/ActivePeter/SubmoduleHelper-vscode)

   [ActivePeter/MacroDefineHelper-vscode: Iterate through the macro helper configuration file in the directory and generate a configuration tree. Then generate a series of macros in head files. 遍历目录中的宏助手配置文件并生成配置树，再根据配置树生成一系列宏 (github.com)](https://github.com/ActivePeter/MacroDefineHelper-vscode)

2. ## 创建 你的单片机项目

3. ## 将单片机项目转化为git仓库

4. ## 在项目根目录创建 submodule_helper.json

   拷贝 通用库的结构信息，root_folder可以根据喜好来修改，

   ```json
   {
       "root_folder": "./components/",
       "submodules_structure": {
           "paLibSubs": [
               {
                   "used": 1,
                   "git": "https://github.com/paMcuLib/paMcuLibCoreHead.git",
                   "rename": "paCoreHead"
               },
               {
                   "used": 1,
                   "git": "https://github.com/ActivePeter/paMcuLibCore_Esp32.git",
                   "rename": "paCoreSrc"
               },
               {
                   "used": 1,
                   "git": "https://github.com/ActivePeter/paMcuLib_Base.git",
                   "rename": "paBase"
               }
           ],
           "paLibSubs/paMods/display": [
               {
                   "used": 0,
                   "rename": "SSD1306",
                   "git": "https://github.com/paMcuLib/ssd1306_paMcuLib.git"
               },
               {
                   "used": 1,
                   "rename": "ILI9341",
                   "git": "https://github.com/paMcuLib/ili9341_paMcuLib.git"
               }
           ],
           "paLibSubs/paMods/input": [
               {
                   "used": 1,
                   "rename": "xpt2046",
                   "git": "https://github.com/paMcuLib/xpt2046_paMcuLib.git"
               }
           ]
       }
   }
   ```

   需要将paCoreSrc那一项的链接改为对应的平台，如果还没有适配过，你需要在paMcuLib或自己的仓库中创建一个对应平台的仓库

   格式： paMcuLibCore_XXXX.git

   #### 目前已有：

   stm32 esp32

   [paMcuLib/paMcuLibCore_stm32 (github.com)](https://github.com/paMcuLib/paMcuLibCore_stm32)

   [paMcuLib/paMcuLibCore_Esp32: esp32 impelemention of paMcuLibCore (github.com)](https://github.com/paMcuLib/paMcuLibCore_Esp32)

5. ## 使用submodule helper加载一系列子模块

6. ## 找到项目的入口文件，创建c++入口程序

   ![image-20210614162846529](https://hanbaoaaa.xyz/tuchuang/images/2021/06/14/image-20210614162846529.png)

   ```c++
   #ifndef __MAINAPP_H__
   #define __MAINAPP_H__
   
   #ifdef __cplusplus
   extern "C"
   {
   #endif
   
       void mainAppEntry();
   
   #ifdef __cplusplus
   }
   #endif
   
   #endif // __MAINAPP_H__
   ```

   ```c++
   #include "MainApp.h"
   // #include "freertos/FreeRTOS.h"
   // #include "freertos/task.h"
   
   #include "paMods/display/SSD1306/pa_oled.h"
   #include "paCoreHead/paIIC.h"
   #include "paCoreHead/paBase.h"
   #include "main.h"
   
   void mainAppEntry()
   {
   
       _G_paIIC.init(0);
       OLED_Init(0);
       // OLED_On();
       OLED_ShowString(0, 0, "121", 12);
       while (1)
       {
           // ESP_LOGI("App", "hello world!");
           _G_paBase.output("hello world");
           // vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
           HAL_Delay(1000);
       }
   }
   ```

   在main.c中注入

   ![image-20210614163028863](https://hanbaoaaa.xyz/tuchuang/images/2021/06/14/image-20210614163028863.png)

   ![image-20210614163041512](https://hanbaoaaa.xyz/tuchuang/images/2021/06/14/image-20210614163041512.png)

7. ## 开始基于paMcuLib通用库的开发

### 注意点：

1. 跟硬件层相关的在paCoreHead和paCoreSrc里。

   paCoreHead只存储硬件平台抽象的函数定义。具体的声明对应不同的平台在paCoreSrc中进行声明

2. 目前还有好多平台和外设没适配，欢迎大家来进行适配

3. 执行update前先确保你本地的代码变更已经存储到远程，以免被删除

4. 要向通用库增加新的内容或修改原有内容，建议和开发者一起交流下，交换意见并确认下方案

5. 之后我会写一份整体的架构思路，以确保使用这个之前对整体的框架了解清晰

