# Project Structure — STM32 BLDC Project

本文件描述项目的软件工程结构。

内容包括：

- 工程目录职责
- 代码模块职责
- 重要源文件定义
- 模块之间的关系

本文件 **不记录硬件连接信息**。  
硬件连接请参考：

Docs/Notes/hardware_map.md

本文件 **不记录开发日志或开发计划**。  
开发记录请参考：

Docs/Notes/Plain next.md

---

# 1 项目软件目标

本项目的软件目标：

建立一个结构清晰、可扩展的嵌入式控制工程。

软件层目标：

- 建立稳定的工程目录结构
- 明确模块职责
- 建立统一模块接口风格
- 为后续电机控制与 FOC 算法提供基础架构

---

# 2 工程目录结构

当前工程目录：


Hardware
Library
Start
System
User
Docs


---

# 3 目录职责

## User

职责：

系统入口层。

包含：

- main 函数
- 中断入口
- 模块调度

典型文件：


main.c
stm32f10x_it.c


规则：

- main.c 只负责初始化和模块调用
- 不在 main.c 中堆积业务逻辑

---

## Hardware

职责：

功能模块实现层。

包含：

- 外设初始化
- ADC 采样
- 输入设备
- 显示驱动
- 电机控制
- 算法相关代码

该目录中的代码应：

- 每个功能独立模块
- 提供清晰接口

---

## System

职责：

系统通用工具层。

例如：

- 延时函数
- 系统辅助函数

该目录中的代码应：

- 尽量通用
- 与具体业务模块解耦

---

## Start

职责：

系统启动与底层支持。

包含：

- 启动文件
- 系统时钟初始化
- Cortex 内核支持

该目录中的代码 **一般不修改**。

---

## Library

职责：

STM32 标准外设库。

该目录为：

第三方库代码。

原则：

- 不在此目录修改代码
- 如需修改，应通过封装模块实现

---

## Docs

职责：

项目文档与开发记录。

包含：

- 软件结构说明
- 硬件连接说明
- 控制系统设计
- 开发记录

---

# 4 重要源文件职责

## main.c

职责：

- 系统初始化
- 调用各功能模块
- 调试输出

原则：

main.c 不实现具体业务逻辑。

---

## stm32f10x_it.c

职责：

- 中断入口
- 调用各模块中断处理函数

原则：

中断处理逻辑尽量简单。

复杂逻辑应交由模块函数完成。

---

## AD.c / AD.h

职责：

ADC 采样模块。

负责：

- ADC 初始化
- DMA 配置
- 数据缓存
- 数据滤波

提供接口：

- 获取 ADC 数据
- 获取滤波结果

---

## Encoder.c / Encoder.h

职责：

编码器模块。

负责：

- 读取编码器信号
- 转换角度
- 后续扩展角速度计算

---

## Periph_Init.c

职责：

底层外设初始化。

包含：

- GPIO
- ADC
- DMA
- TIM
- USART

---

## Delay.c

职责：

系统延时函数。

提供：

- us 延时
- ms 延时

---

# 5 模块设计原则

为了保证工程可持续开发，需要遵守以下原则：

---

## 模块独立

每个模块应：

- 只负责一个功能
- 提供清晰接口

---

## 接口访问

模块之间通过：

函数接口通信。

禁止：

直接访问模块内部变量。

---

## main.c 简洁原则

main.c 只负责：

- 初始化
- 模块调用
- 调试输出

---

## 模块变量管理

模块内部变量优先使用：

static

避免全局变量污染。
# 6 模块命名规范

为了保持工程长期可维护性，需要统一模块命名风格。

模块命名遵循以下规则：

---

## 1 文件命名

模块文件使用：


module_name.c
module_name.h


示例：


adc.c
encoder.c
motor.c
pwm.c
key.c


一个模块只允许：

- 一个 `.c`
- 一个 `.h`

---

## 2 函数命名

模块接口函数使用：


Module_Function()


示例：


Encoder_Init()
Encoder_Update()
Encoder_GetAngle()

Ad_Init()
Ad_GetValue()

Motor_SetState()
Motor_Stop()

Pwm_Init()
Pwm_SetDuty()


规则：

- 首字母大写
- 使用模块名前缀
- 使用动词描述行为

---

## 3 模块内部函数

模块内部函数使用：


static


并使用小写命名：


static void update_filter(...)
static void calc_angle(...)


规则：

- 内部函数不对外暴露
- 使用 `static`

---

## 4 变量命名

模块内部变量：


static type variable_name


示例：


static uint16_t adc_buf[3];
static float angle;


避免：

- 使用全局变量
- 在多个模块之间共享变量

---

## 5 模块接口原则

模块只通过 **接口函数通信**。

禁止：

- 直接访问模块内部变量
- 跨模块访问静态变量

例如：

正确：


angle = Encoder_GetAngle();


错误：


angle = encoder_internal_angle;


---

## 6 模块划分建议

当前项目建议逐步拆分为以下模块：


adc
encoder
motor
pwm
key
oled
control


职责：

| 模块 | 职责 |
|-----|------|
| adc | ADC采样 |
| encoder | 编码器处理 |
| motor | 电机状态管理 |
| pwm | PWM驱动 |
| key | 按键输入 |
| oled | OLED显示 |
| control | 控制算法 |

---

## 7 main.c 使用规则

main.c 只负责：

- 系统初始化
- 模块初始化
- 模块调度
- 调试输出

不在 main.c 中实现：

- 算法逻辑
- 设备驱动
- 数据处理