# pa_CommonLibTest
最近在建立一个以方便移植为目的的各类外设的通用库。

github地址：[https://github.com/ActivePeter/pa_CommonLibTest](https://github.com/ActivePeter/pa_CommonLibTest)

------

## 已经适配的单片机：

demo项目汇总：[https://github.com/pa-CommonLib-series](https://github.com/pa-CommonLib-series)

1. #### stm32h743，之前用的h750 结果发现flash不够

2. #### stm32f407，没有太大的性能要求可以选择这个

3. #### msp432e，因为一些学习需求所以适配了这个板子

4. ###### 后期计划适配：k210

------

## 如何使用：

1.fork这个项目。

2.建立一个你的单片机项目。（由于是一个层级结构的目录。所以它不支持keil，可以使用ccs,cubeide，gcc等编译工具）

3.将你的单片机项目变为仓库

4.使用指令将此库作为子模块加入你的单片机项目仓库

```git
git submodule add https://github.com/ActivePeter/pa_CommonLib.git（这个路径可以换成你fork后的路径）
```

## 我的使用了这个库的项目：

1. 绘图机械臂](https://github.com/ActivePeter/RobotArmDrawer)

------

## 设计：

​	每一种外设都有分层。逻辑和驱动分开。

​	驱动层函数。使用宏定义来分别指定不同板子的型号。

------

## 语言：

​	c/c++

------

## 已有功能：

#### 	驱动层：

​		spi，iic，ms、us延时,

#### 	服务层：

​		1.ssd1306（iic，spi）

![image-20200822231413580](http://tuchuang.hanbaoaaa.xyz/image-20200822231413580.png)

​		2.矩阵按键已添加。可以设置行列数量

​		3.st7789（240*240）

![image-20200829145209488](http://tuchuang.hanbaoaaa.xyz/image-20200829145209488.png)

​		4.ti系列芯片：（主要是为了ti邀请赛做准备的）

​			ads1112，

​			ads112c04