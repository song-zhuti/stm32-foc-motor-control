# STM32 FOC Motor Control

基于 **STM32F103C8** 的 **BLDC 电机控制实验项目**。

本项目用于学习与实现 **FOC（Field Oriented Control）算法**，并逐步构建一个 **结构清晰、模块化的电机控制框架**。

---

# Hardware Platform

MCU  
STM32F103C8

Motor  
BLDC Motor

Driver Board  
SimpleFOCmini

Debug  
ST-Link

Development Environment  

Keil  
VSCode

使用外设：

- ADC（信号采样）
- DMA（高速数据搬运）
- TIM（PWM 输出）
- GPIO（按键 / 控制）
- OLED（调试显示）

---

# Project Structure


Hardware/ 硬件驱动与功能模块
Library/ STM32标准外设库
Start/ 启动文件与CMSIS
System/ 系统工具模块
User/ 主程序与中断入口
Docs/ 项目文档


详细结构说明请参考：


Docs/Notes/project_structure.md


---

# Documentation

项目文档位于：


Docs/Notes/


主要文档：

| 文件 | 说明 |
|-----|------|
| ai_context.md | AI开发规则 |
| project_structure.md | 软件工程结构 |
| hardware_map.md | 硬件连接与引脚映射 |
| control_architecture.md | 控制系统架构 |
| Plain next.md | 开发记录与任务 |

---

# Branch Strategy


main 稳定版本
dev 日常开发
feature/algorithm-sandbox 算法实验


开发流程：


feature → dev → main


说明：

main  
稳定运行版本

dev  
主开发分支

feature/*  
功能开发或算法实验

---

# Current Features

当前已经实现：

- ADC 连续采样
- DMA 数据搬运
- DMA 中断处理
- 数据滤波
- OLED 调试显示
- 基础电机控制框架

---

# Planned Features

接下来计划实现：

- ADC采样系统优化
- 编码器角度处理
- 摇杆输入控制
- PWM 电机驱动
- BLDC 控制系统
- 完整 FOC 算法

---

# Project Purpose

该项目主要用于：

- 学习 STM32 外设驱动
- 实践 FOC 电机控制算法
- 构建模块化嵌入式工程
- 探索 BLDC 控制系统设计