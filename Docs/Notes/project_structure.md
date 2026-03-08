# 当前项目整体结构

## 1. 项目目标
基于 STM32F103C8 + SimpleFOCmini + AS5600 的 BLDC 控制实验项目。

当前项目目标：
- 实现 BLDC 基础驱动
- 实现编码器角度读取
- 建立 PWM 电机驱动结构
- 为后续 FOC 控制做准备

---

## 2. 当前项目硬件组成

### MCU
- STM32F103C8

### Driver Board
- SimpleFOCmini

### Driver Chip
- MS8313

### Motor
- BLDC Motor

### Encoder
- AS5600
- 当前使用 OUT 模拟输出方式

### User Input
- 摇杆（ADC）
- 按键（GPIO）

### Debug
- 串口
- OLED（如使用）

---

## 3. 当前软件功能模块

### 3.1 系统初始化
负责 GPIO、ADC、DMA、TIM、USART 等基础外设初始化。

### 3.2 ADC采样模块
负责：
- 摇杆 X/Y 采样
- AS5600 OUT 采样
- DMA 数据搬运
- 数据缓存与滤波

### 3.3 编码器模块（当前功能已实现，后续准备独立）
负责：
- 读取 AS5600 OUT 电压
- 转换角度值
- 后续扩展角度连续化与速度计算

### 3.4 输入模块
负责：
- 摇杆输入
    - Joystick X → PA5
    - Joystick Y → PA4
- 按键输入
    - Key → PA3

### 3.5 电机驱动模块
负责：
- 控制 SimpleFOCmini 输入端
- 当前 GPIO 驱动已验证
- 后续改为 TIM1 PWM 驱动

### 3.6 调试模块
负责：
- 串口打印
- OLED 显示
- LED 状态指示

---

## 4. 当前工程目录职责

### User
主程序入口与中断入口：
- main.c
- stm32f10x_it.c
- 配置与调度逻辑

### Hardware
当前主要功能实现层，包含：
- 外设初始化
- ADC采样
- 输入驱动
- 显示驱动
- 电机控制相关
- 数学/算法相关

### System
通用系统支持：
- 延时
- 公共基础功能

### Start
启动文件与底层系统文件

### Library
STM32 标准外设库

### Docs
项目文档、原理图、手册、备忘与硬件映射

---

## 5. 当前 ADC 通道分配

| DMA槽位 | ADC通道 | 引脚 | 信号 |
|--------|--------|------|------|
| 0 | ADC_Channel_1 | PA1 | Joystick Y |
| 1 | ADC_Channel_2 | PA2 | Joystick X |
| 2 | ADC_Channel_9 | PB1 | AS5600 OUT |

### DMA Buffer 对应关系
- adc_buf[0] -> Joystick Y
- adc_buf[1] -> Joystick X
- adc_buf[2] -> AS5600 OUT

---

## 6. 当前电机控制引脚

### Driver Control Signals
- IN1 -> PA10
- IN2 -> PA9
- IN3 -> PA8
- EN  -> 待定

### Motor Phase Output
- OUT1 -> Motor U
- OUT2 -> Motor V
- OUT3 -> Motor W

---

## 7. 当前开发状态

### 已完成
- GitHub 仓库建立与同步
- 文档目录建立
- ADC + DMA 基本架构建立
- 摇杆 ADC 采样
- AS5600 OUT 模拟输出读取
- 电机 GPIO 驱动验证
- 工程可构建可下载

### 正在进行
- 整理项目结构
- 明确模块职责
- 准备将电机驱动改为 PWM 输出

### 下一步
- 独立 encoder 模块
- 独立 motor / pwm 模块
- 完成 TIM1 PWM 输出
- 建立角度与速度处理流程

---

## 8. 当前工程结构是否足够

结论：
当前目录结构可以支撑本项目继续开发，不需要立即大规模重构。

策略：
- 保留当前目录结构
- 新功能尽量模块化新增
- 不再继续把逻辑堆到 main.c
- 通过文档和职责划分保持工程清晰