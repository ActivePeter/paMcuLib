# pa_CommonLibTest
> 最近在建立一个以方便移植为目的的各类外设的通用库。
>
> github地址：[https://github.com/ActivePeter/pa_CommonLibTest](https://github.com/ActivePeter/pa_CommonLibTest)
>
> ------
>
> ## Part1  已经适配的单片机：
>
> > demo项目汇总：[https://github.com/pa-CommonLib-series](https://github.com/pa-CommonLib-series)
> >
> > > 1. #### stm32h743，之前用的h750 结果发现flash不够
> > >
> > > 2. #### stm32f407，没有太大的性能要求可以选择这个
> > >
> > > 3. #### msp432e，因为一些学习需求所以适配了这个板子
> > >
> > >
>
> ------
>
> ## Part2  如何使用：
>
> > 1.fork这个项目。
> >
> > 2.建立一个你的单片机项目。（由于是一个层级结构的目录。所以它不支持keil，可以使用ccs,cubeide，gcc等编译工具）
> >
> > 3.将你的单片机项目变为仓库
> >
> > 4.使用指令将此库作为子模块加入你的单片机项目仓库
>
> ```git
> git submodule add https://github.com/ActivePeter/pa_CommonLib.git（这个路径可以换成你fork后的路径）
> ```
>
> ## Part3  我的使用了这个库的项目：
>
> > 1. 绘图机械臂](https://github.com/ActivePeter/RobotArmDrawer)
> >
>
> ------
>
> ## Part4  设计：
>
> > ​	每一种外设都有分层。逻辑和驱动分开。
> >
> > ​	驱动层函数。使用宏定义来分别指定不同板子的型号。
> >
>
> ------
>
> ## Part5  语言：
>
> > ​	c/c++
> >
>
> ------
>
> ## Part6  已有功能：
>
> > ### 	6.1驱动层：
> >
> > > ###### 6.1.1.pa_HardwareIIC
> > >
> > > ​			c写法。固定外设
> > >
> > > ###### 6.1.2.pa_HardwareSPI
> > >
> > > ​			c写法。固定外设。一些外设比较多的后期考虑加入速度切换选项
> > >
> > > ###### 6.1.3.pa_CommonDrv
> > >
> > > ​			最常用的一些函数：
> > >
> > > ​				pa_millis（系统运行时。毫秒
> > >
> > > ​				void pa_CommonInit();  （通用外设的启动。
> > >
> > > ​				void pa_delayMs(unsigned int ms);  （毫秒延时。有rtos就直接用rtos的延时
> > >
> > > ​				void pa_delayUs(unsigned int us);   （一般用不到
> > >
> > > ​				void pa_setTimerCallback(void (*CallBack_100us)(void), void (*CallBack_1ms)(void));   
> > >
> > > ​				（设置定时器应用层回调函数。一些需要高频稳定调用的
> > >
> > > ###### 6.1.5.pa_PWM
> > >
> > > ​			c写法。放在pa_PWM 的 namespace内
> > >
> > > ###### 6.1.4通用枚举		
> > >
> > > ```c
> > > typedef enum
> > > {
> > > 
> > >   Protocal_SPI = 1,
> > > 
> > >   Protocal_IIC
> > > 
> > > } Protocal;
> > > 
> > > 
> > > 
> > > typedef enum
> > > 
> > > {
> > > 
> > >   GpioInputMode_pullup = 1,
> > > 
> > >   GpioInputMode_pulldown,
> > > 
> > >   GpioInputMode_hang,
> > > 
> > > } GpioInputMode;
> > > 
> > > 
> > > 
> > > typedef enum
> > > 
> > > {
> > > 
> > >   GpioPortOrPin_Port = 1,
> > > 
> > >   GpioPortOrPin_Pin,
> > > 
> > > } GpioPortOrPin;
> > > 
> > > 
> > > 
> > > typedef enum
> > > 
> > > {
> > > 
> > >   Direction_Increase = 1,
> > > 
> > >   Direction_Decrease,
> > > 
> > > } Direction;
> > > ```
> >
> > ------
> >
> > ### 6.2 工具层：
> >
> > > ##### 6.2.1pa_DataProcessor
> > >
> > > ​			pa_snprintf,   对于freertos的gcc  32比较友好
> > >
> > > ##### 6.2.2pa_Math
> > >
> > > ​			目前没多少东西
> > >
> > > ```c
> > > extern "C"
> > > {
> > > #include "math.h"
> > > }
> > > #ifndef PI
> > > #define PI 3.1415926535898
> > > #endif
> > > 
> > > #ifndef PI_3
> > > #define PI_3 1.0471975511965
> > > #endif
> > > 
> > > #ifndef PI_2_3
> > > #define PI_2_3 2.09439510239319549
> > > #endif
> > > ```
> >
> > ------
> >
> > ### 	6.3 服务层：
> >
> > > #### 6.3.1 显示：
> > >
> > > > ##### 6.3.1.1.ssd1306（iic，spi）
> > > >
> > > > ![image-20200822231413580](http://tuchuang.hanbaoaaa.xyz/image-20200822231413580.png)
> > > >
> > > > ###### 6.3.1.2.st7789（240*240）
> > > >
> > > > ![image-20200829145209488](http://tuchuang.hanbaoaaa.xyz/image-20200829145209488.png)
> > > >
> > > > ​		
> > > >
> > > > ##### 6.3.1.3.ili9341
> > > >
> > > > ![image-20201108051418581](http://tuchuang.hanbaoaaa.xyz/image-20201108051418581.png)
> > >
> > > ------
> > >
> > > #### 6.3.2   输入：
> > >
> > > > ##### 6.3.2.1、pa_Keypad，非阻塞。c++单例
> > > >
> > > > ##### 6.3.2.2、pa_touchScreen  c++单例。为ili9341带的那个。一般常用的一个芯片 xpt2046，软件模拟spi。需要5根线
> > >
> > > ------
> > >
> > > #### 6.3.3  ti系列芯片：（主要是为了ti邀请赛做准备的）
> > >
> > > > ##### ads1112，(没怎么用过)
> > > >
> > > > ##### ads112c04  （所有的寄存器都使用类内枚举表达。分类清晰。
> > >
> > > #### 6.3.4  图形 ：目前只有一个lvgl ，对容量要求比较高。128k的h750顶不住
> > >
> > > #### 6.3.5  传感器：
> > >
> > > > ##### 6.3.5.1 姿态传感器
> > > >
> > > > ##### {
> > > >
> > > > ##### 	as5048a,  spi 绝对值角度传感器，用于电机闭环
> > > >
> > > > ##### 	bno055,  自带滤波的i2c输出的陀螺仪，比6050好使。缺点是软件模拟iic不好调
> > > >
> > > > }
> > > >
> > > > ##### 6.3.5.2 距离传感器
> > > >
> > > > ##### {
> > > >
> > > > ##### 	VL53L0X   激光测距 ，单例模式
> > > >
> > > > ##### }
> > > >
> > > > ##### 6.3.5.3  其他
> > > >
> > > > ##### {
> > > >
> > > > ##### 	GY906  红外测温
> > > >
> > > > ##### }
> >
> > ### 6.4  应用层
> >
> > > #### 6.4.1步进电机机械臂算法
> > >
> > > #### 6.4.2svpwm foc 无刷控制算法