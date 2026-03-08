# AI Context — STM32 BLDC Project

本文件用于在新的 AI 聊天窗口中 **快速恢复项目上下文**。

---

# 1 项目概述

项目：STM32 BLDC 控制实验

硬件：

- MCU：STM32F103C8
- Driver Board：SimpleFOCmini
- Driver Chip：MS8313
- Motor：BLDC
- Encoder：AS5600

当前目标：

- 建立稳定的 BLDC 控制实验环境
- 使用 AS5600 获取角度
- 完成 ADC + DMA 采样架构
- 将电机控制从 GPIO 升级为 PWM
- 为后续 FOC 控制做准备

项目性质：学习型嵌入式开发项目。

---

# 2 关键硬件连接

## Motor Control

IN1 → PA10  
IN2 → PA9  
IN3 → PA8  
EN  → PB12 (planned)

Motor Phase

OUT1 → Motor U  
OUT2 → Motor V  
OUT3 → Motor W

---

## Encoder (AS5600)

VDD → 3.3V  
GND → GND  

OUT → PB10  
PGO → 3.3V

当前使用 **OUT 模拟输出模式**

I2C 暂未使用

---

## Input

Joystick X → PA5  
Joystick Y → PA4  

Key → PA3

---

# 3 ADC 架构

ADC 使用：

ADC + DMA

数据存储：

AD.c 内部数组


data[]


读取接口：


get_ad_data()


规则：

外部模块 **禁止直接访问 ADC 数组**

---

## ADC Channel Mapping

| DMA | ADC Channel | Pin | Signal |
|----|----|----|----|
|0|ADC_Channel_1|PA4|Joystick Y|
|1|ADC_Channel_2|PA5|Joystick X|
|2|ADC_Channel_9|PB1|AS5600 OUT|

---

# 4 软件工程结构


Hardware
Library
Start
System
User
Docs


职责：

User  
主程序入口 / 中断

Hardware  
功能模块

System  
系统工具

Start  
启动文件

Library  
STM32 标准库

Docs  
文档与资料

详细结构见：


Docs/Notes/project_structure.md


---

# 5 当前开发阶段

已完成

- GitHub 仓库建立
- ADC + DMA 基础链路跑通
- 摇杆 ADC 读取
- AS5600 OUT 模式读取
- 电机 GPIO 驱动验证
- 文档体系建立

正在进行

- encoder 模块独立
- 项目结构整理

下一步

- TIM PWM 驱动电机
- 角度处理
- 速度计算

开发记录：


Docs/Notes/Plain next.md


---

# 6 重要文档

硬件连接：


Docs/Notes/hardware_map.md


开发任务：


Docs/Notes/Plain next.md


项目结构：


Docs/Notes/project_structure.md


---

# 7 开发规则

## 1

AI **不要直接给完整实现代码**

需要：

- 给出设计思路
- 指出修改位置
- 让开发者自己实现

---

## 2

开发必须 **分步骤进行**

AI需要提供：

步骤1  
步骤2  
步骤3  

并说明：

- 修改位置
- 修改内容
- 验证方法

---

## 3

main.c 只负责：

- 初始化
- 调度模块
- 调试输出

业务逻辑必须在模块内部。

---

## 4

模块内部变量使用：


static


避免全局污染。

---

## 5

ADC 数据必须通过：


get_ad_data()


禁止直接访问 ADC 数组。

---

## 6

Notes 目录 **非必要不要新增文件**

开发记录统一写入：


Plain next.md


---

# 8 AI 开发工作流

开发流程：

1 分析模块职责  
2 设计模块接口  
3 建立代码骨架  
4 分步骤实现  
5 编译验证  
6 进入下一阶段

AI职责：

- 架构指导
- 代码审查
- 开发规划
- 问题定位