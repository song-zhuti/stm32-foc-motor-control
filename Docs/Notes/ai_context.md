# AI Context — STM32 BLDC Project
If you are an AI assistant analyzing this project,
please read this file first before answering any question.
本文件用于在新的 AI 聊天窗口中 **快速恢复项目上下文**。

本文件只描述：

- 项目背景
- AI参与开发的规则
- AI开发工作流程
- 项目文档入口

本文件 **不包含项目具体实现细节**。

# 1 项目概述

项目名称：

STM32 BLDC 控制实验项目

项目目标：

基于以下硬件建立一个可持续扩展的 BLDC 控制实验平台：

- MCU：STM32F103C8
- Driver Board：SimpleFOCmini
- Driver Chip：MS8313
- Motor：BLDC
- Encoder：AS5600

当前阶段目标：

- 建立稳定的嵌入式工程结构
- 完成 ADC + DMA 采样架构
- 完成编码器角度读取
- 将电机驱动从 GPIO 升级为 PWM
- 为后续 FOC 控制做准备

项目性质：

学习型嵌入式开发项目。

---

# 2 文档入口

AI 在分析项目之前，应优先阅读以下文档：

软件结构：

Docs/Notes/project_structure.md

硬件连接：

Docs/Notes/hardware_map.md

开发任务与开发记录：

Docs/Notes/Plain next.md

---

# 3 AI开发规则

AI 参与开发时必须遵守以下规则。

## 规则 1

AI **不要直接给出完整实现代码**。

AI需要：

- 给出设计思路
- 指出需要修改的文件
- 指出需要修改的位置
- 提供分步骤实现建议

开发者自行实现代码。

---

## 规则 2

开发必须 **分步骤进行**。

AI需要提供：

步骤1  
步骤2  
步骤3  

并明确说明：

- 修改位置
- 修改内容
- 验证方法

---

## 规则 3

main.c 的职责：

- 初始化系统
- 调用模块
- 调试输出

业务逻辑 **必须放在模块内部**。

---

## 规则 4

模块内部变量优先使用：

static

避免全局变量污染。

---

## 规则 5

模块之间必须通过 **接口函数通信**。

禁止跨模块直接访问内部变量。

---

## 规则 6

Notes 目录 **非必要不要新增文件**。

开发记录统一写入：

Docs/Notes/Plain next.md

## 规则 7

任务记录规则：

开发任务统一记录在：

Docs/Notes/Plain next.md

任务格式规则：

未完成任务：

- [ ] 任务内容

完成任务：

删除 `[ ]` 标记，仅保留任务文本。

示例：

未完成：

- [ ] 独立 Encoder 模块

完成后：

- 独立 Encoder 模块

---

# 4 AI开发工作流

AI参与开发时建议遵循以下流程：

步骤1  
分析模块职责

步骤2  
设计模块接口

步骤3  
建立代码骨架

步骤4  
分步骤实现功能

步骤5  
编译验证

步骤6  
进入下一开发阶段

AI主要职责：

- 架构指导
- 代码审查
- 开发规划
- 问题定位与解决