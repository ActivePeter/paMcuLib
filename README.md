# paMcuLib

![pamculib](https://hanbaoaaa.xyz/tuchuang/images/2021/06/25/pamculib.png)

- ## Intro（介绍

  这是一个我用来封装我用过的单片机，并且统一模块接口的库

  为了实现更好的移植性和模块性，我还开发两个vscode插件 

  This is a mcu lib like arduino to unify the module's and mcu's interfaces.

  In order to implement better portability and modularity, I also made 2 vscode extensions,

  [ActivePeter/MacroDefineHelper-vscode: Iterate through the macro helper configuration file in the directory and generate a configuration tree. Then generate a series of macros in head files. 遍历目录中的宏助手配置文件并生成配置树，再根据配置树生成一系列宏 (github.com)](https://github.com/ActivePeter/MacroDefineHelper-vscode)

  [ActivePeter/SubmoduleHelper-vscode: I'm going to write a vscode extension available to choose needed submodules and auto load them, just like some package manager. (github.com)](https://github.com/ActivePeter/SubmoduleHelper-vscode)

  

- ## Supported mcus（当前支持的平台

  - esp32 stm32
  - demos
    - [paMcuLib/paMcuLib_esp32_idf_cmake_demo](https://github.com/paMcuLib/paMcuLib_esp32_idf_cmake_demo)
    - [paMcuLib/paMcuLib_stm32f103c8t6_cubeide_demo ](https://github.com/paMcuLib/paMcuLib_stm32f103c8t6_cubeide_demo)

- ## Adapted devices of mcu（当前适配的常用硬件设施

  - base(delay, log)，gpio，spi，iic

- ## Adapted modules（当前库适配的模块

  - ***paLibSubs/paMods/display* 显示**

    ssd1306（iic

    ili9341（spi

  - ***paLibSubs/paMods/input* 输入**

    xpt2046（一般配合ili9341用

- ## Design（项目结构设计

  - ### Before you use this project, you need to understand the structure of this project.

    ### 在开始使用这个项目之前，你应该理解这个项目的结构设计 

  - Use my vscode extension [submodule helper](https://github.com/ActivePeter/SubmoduleHelper-vscode) to manage and load submodules

    使用我的vscode插件 [submodule helper](https://github.com/ActivePeter/SubmoduleHelper-vscode)进行子模块结构的组织 和 子模块的加载

  - submodule helper will load all the submodules according to the  folloing **json file**

    submodule helper 会根据下面这样的一个**json模板文件**加载所有子模块

    - ### [Get latest json templete from here](./latest_module.md) 

      ### [在这里可以获取到最新的模板](./latest_module.md)

      ![image-20210625214927475](https://hanbaoaaa.xyz/tuchuang/images/2021/06/25/image-20210625214927475.png)

    - It's free to change the **“root_folder”**, which means that you can load the modules of paMcuLib to any position in you project. Just don't change the **structure of the templete**. 

      这个文件里的**root_folder**是任意设置的，意味着你可以把子我的paMcuLib的所有模块放在任意路径下，只要不**破坏他们之间的相对位置**关系就行。

    - ![image-20210625215041381](https://hanbaoaaa.xyz/tuchuang/images/2021/06/25/image-20210625215041381.png)

      This is the core part of paMcuLib, which contains by the **paCoreInc** **paCoreSrc**

      这是paMcuLib主体部分，分为 **paCoreInc** **paCoreSrc**  两部分部分

      - **paCoreInc** 

        Used to offer the defination of interfaces to **paCoreSrc** to impletement , and export them to the **user layer**.

        用于组织和规范驱动层抽象的接口规范，还有向用户层提供相应外设的include的头文件

      - **paCoreSrc** 

        Implementation of the interfaces in **paCoreInc**, different MCUs have different implementations.

        为具体的驱动实现，根据不同的平台，需要做不同的适配，目前只适配了esp32 stm32，的一些功能，也可以参考已经适配的项目自行适配，或申请加入开发组一起适配

        ​	**Look out：**the repostory url of **paCoreSrc** should be changed according to your platform

        ​	**注意：**这个仓库对应的链接是需要根据你使用的平台进行修改的

- ## Start Using

  ## [大致的使用流程](./start.md)