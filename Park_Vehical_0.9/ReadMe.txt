整体工程文件在Park_Vehical文件夹内，直接打开Park_Vehical.ino文件即可打开工程。

Configuration.h 文件包含了必要的硬件参数，如：引脚信息，LCD1602的尺寸，步进电机的运动方向等；
	同时也包含了部分常量，如：LCD1602的常用字符串等。

InstructionConfiguration.h 文件包含了驱动整体事件流程的指令。

Function.hpp 文件包含了所有在Park_Vehical.ino 文件中使用到的自定义函数。包括但不限于电机执行。

