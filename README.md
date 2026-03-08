# stm32-foc-motor-control
STM32 brushless motor control project using FOC algorithm

# STM32 FOC Motor Control

基于 **STM32F103C8** 的 **BLDC 电机 FOC 控制实验项目**。

该项目用于学习和实现 **FOC（Field Oriented Control）算法**，并逐步构建一个结构清晰、模块化的 **电机控制框架**。

---

# Hardware Platform

* **MCU**：STM32F103C8
* **Motor Type**：BLDC
* **Development Environment**：Keil / VSCode
* **Debug**：ST-Link

使用外设：

* ADC（信号采样）
* DMA（高速数据搬运）
* TIM（PWM 输出）
* GPIO（按键 / 控制）
* OLED（调试显示）

---

# Project Structure

```
Hardware/
    AD.c                ADC采样驱动
    CountSensor.c       传感器接口
    foc.c               FOC控制算法
    Key.c               按键输入
    LED.c               LED控制
    OLED.c              OLED显示
    Periph_Init.c       外设初始化
    mathoperation.c     数学运算函数

Library/
    STM32 标准外设库

Start/
    启动文件
    CMSIS 核心文件

System/
    Delay.c             延时函数

User/
    main.c              主程序
    stm32f10x_it.c      中断服务函数
```

---

# Branch Strategy

```
main                        稳定版本
dev                         日常开发
feature/algorithm-sandbox   算法实验分支
```

开发流程：

```
feature → dev → main
```

说明：

* `main`：稳定运行版本
* `dev`：主开发分支
* `feature/*`：功能开发或算法实验

---

# Current Features

当前已经实现：

* ADC 连续采样
* DMA 数据搬运
* DMA 中断处理
* 数据滤波处理
* 主循环调试输出
* 基础电机控制结构

---

# Planned Features

接下来计划实现：

* ADC采样系统优化
* 角度捕获算法
* 菜单状态机
* 摇杆输入控制
* BLDC PWM控制
* 完整FOC算法

最终目标：

构建一个 **结构清晰、模块化的 STM32 电机控制框架**。

---

# Purpose

该项目主要用于：

* 学习 STM32 外设驱动
* 实践 FOC 电机控制算法
* 构建模块化嵌入式工程
* 探索 BLDC 控制系统设计
