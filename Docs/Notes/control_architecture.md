# Control Architecture — STM32 BLDC Project

本文件描述项目的 **控制系统架构**。

本文件用于记录：

- 采样链路
- 控制链路
- 控制周期
- PWM 输出
- 控制算法结构

本文件 **不记录硬件连接**。  
硬件连接请参考：

Docs/Notes/hardware_map.md

本文件 **不记录软件目录结构**。  
软件结构请参考：

Docs/Notes/project_structure.md

---

# 1 控制系统目标

本项目目标是建立一个可扩展的 BLDC 控制架构。

当前阶段：

基础控制实验阶段

长期目标：

实现完整的 **FOC (Field Oriented Control)** 控制系统。

---

# 2 控制系统整体结构

系统分为三个主要部分：


Sensor Layer
↓
Control Layer
↓
Actuator Layer


---

## Sensor Layer（传感层）

负责采集所有传感器数据。

当前包含：

- ADC 采样
- 编码器角度

数据来源：

- Joystick
- AS5600 Encoder

主要功能：

- 采样
- 滤波
- 数据缓存

---

## Control Layer（控制层）

负责计算控制量。

当前阶段：

- 角度读取
- 基础处理

未来扩展：

- 角度处理
- 速度计算
- 控制环

---

## Actuator Layer（执行层）

负责驱动电机。

当前阶段：

GPIO 控制验证

下一阶段：

PWM 控制

最终目标：

FOC PWM 控制。

---

# 3 数据流

当前系统数据流：


Sensor
↓
ADC Sampling
↓
DMA Transfer
↓
Filter
↓
Application Logic
↓
Debug Output


未来控制系统数据流：


Sensor
↓
ADC Sampling
↓
DMA
↓
Angle Calculation
↓
Control Algorithm
↓
PWM Output
↓
Motor


---

# 4 控制周期设计

当前系统：

- ADC 连续采样
- DMA 中断更新数据
- 主循环读取数据

当前主循环：


while(1)
{
read sensor data
display debug info
delay
}


当前系统 **不是实时控制系统**。

---

# 5 未来控制循环

未来控制系统建议使用：

**定时器驱动控制循环**

例如：

TIM1 / TIM3 控制周期


Timer Interrupt
↓
Sensor Update
↓
Control Calculation
↓
PWM Update


---

# 6 控制模块规划

未来控制系统建议拆分为以下模块：

Encoder Module

负责：

- 角度读取
- 角度连续化

---

Motor Module

负责：

- 电机状态
- 控制命令

---

PWM Module

负责：

- PWM 初始化
- PWM 输出

---

Control Module

负责：

- 控制算法
- 控制周期调度

---

# 7 控制算法发展路线

控制系统建议按以下阶段开发：

阶段 1

GPIO 电机驱动验证

阶段 2

PWM 电机驱动

阶段 3

角度读取稳定

阶段 4

速度计算

阶段 5

简单控制

阶段 6

FOC 控制

---

# 8 当前控制架构阶段

当前系统属于：

**传感器验证阶段**

当前完成：

- ADC 采样
- DMA 数据搬运
- 编码器模拟读取
- 基础显示

下一阶段：

- 独立 Encoder 模块
- 建立 PWM 驱动
- 建立 Motor 控制模块

---

# 9 未来 FOC 架构预留

未来 FOC 控制架构：


Current Sampling
↓
Clarke Transform
↓
Park Transform
↓
Current Control (PI)
↓
Inverse Park
↓
SVPWM
↓
Motor


该架构将在后续阶段逐步实现。