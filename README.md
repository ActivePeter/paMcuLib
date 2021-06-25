# paMcuLib

![pamculib](https://hanbaoaaa.xyz/tuchuang/images/2021/06/25/pamculib.png)

这是一个我用来封装我用过的单片机，并且统一模块接口的库

为了实现更好的移植性和模块性，我还开发两个vscode插件 

用于根据配置加载子模块 还有 生成宏定义配置树

## 当前支持的平台

esp32 stm32

## 当前适配的常用硬件设施

base(delay, log)，gpio，spi，iic

## 当前库适配的模块

*paLibSubs/paMods/display* 显示

ssd1306 ili9341

*paLibSubs/paMods/input* 输入

xpt2046（一般配合ili9341用

## 项目结构设计

使用我的vscode插件 [submodule helper]()进行子模块结构的组织 和 子模块的加载

submodule helper 会根据下面这样的一个**json模板文件**加载所有子模块

### [在这里可以获取到最新的模板](./latest_module.md)

![image-20210615141640784](https://hanbaoaaa.xyz/tuchuang/images/2021/06/15/image-20210615141640784.png)

这个文件里的root_folder是任意设置的，意味着你可以把子我的paMcuLib的所有模块放在任意路径下，只要不破坏他们之间的相对位置关系就行。

![image-20210615142319505](https://hanbaoaaa.xyz/tuchuang/images/2021/06/15/image-20210615142319505.png)

这是paMcuLib主体部分，分为 **paCoreHead** **paCoreSrc** **paBase** 三部分

**paCoreHead** 用于组织和规范驱动层抽象的接口规范，还有向用户层提供相应外设的include的头文件

**paCoreSrc** 为具体的驱动实现，根据不同的平台，需要做不同的适配，目前只适配了esp32 stm32，的一些功能，也可以参考已经适配的项目自行适配，或申请加入开发组一起适配

​	**注意：**这个仓库对应的链接是需要根据你使用的平台进行修改的

**paBase**  一些平台无关的基本类型以及基本的头文件include

分为：ForUser ForCore ForMods  

使用时可以清晰的区分开

## [大致的使用流程](./start.md)

