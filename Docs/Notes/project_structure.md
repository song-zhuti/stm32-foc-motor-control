# Hardware Map — STM32 BLDC Project

本文件用于记录项目的 **硬件连接关系与引脚映射**。

本文件只描述：

- MCU 与驱动板
- 电机连接
- 编码器连接
- 输入设备连接
- ADC 通道映射
- 控制引脚映射

本文件 **不记录软件结构**。  
软件结构请参考：

Docs/Notes/project_structure.md

本文件 **不记录开发任务和开发日志**。  
开发记录请参考：

Docs/Notes/Plain next.md

---

# 1 核心硬件

## MCU

STM32F103C8

## Driver Board

SimpleFOCmini

## Driver Chip

MS8313

## Motor

BLDC Motor

## Encoder

AS5600 Magnetic Encoder

当前使用方式：

**OUT 模拟输出模式**

I2C 暂未使用。

---

# 2 电机驱动连接

## Driver Control Input

- IN1 → PA10
- IN2 → PA9
- IN3 → PA8
- EN  → PB12（planned）

## Motor Phase Output

- OUT1 → Motor U
- OUT2 → Motor V
- OUT3 → Motor W

---

# 3 编码器连接

## AS5600 Power

- VDD → 3.3V
- GND → GND

## AS5600 Signal

- OUT → PB1
- PGO → PB11

当前说明：

- 当前使用 OUT 模拟电压输出
- 后续可扩展为 I2C 读取
- 当前 SCL / SDA 未接入软件功能

## I2C Signal（当前未使用）

- SCL → 未使用
- SDA → 未使用

---

# 4 用户输入连接

## Joystick

- Joystick Y → PA4
- Joystick X → PA5

## Key

- Key → PA3

---

# 5 ADC 通道映射

## ADC Channel Mapping

| DMA槽位 | ADC通道 | 引脚 | 信号 |
|--------|--------|------|------|
| 0 | ADC_Channel_4 | PA4 | Joystick Y |
| 1 | ADC_Channel_5 | PA5 | Joystick X |
| 2 | ADC_Channel_9 | PB1 | AS5600 OUT |

---

## DMA Buffer Mapping

- adc_buf[0] → Joystick Y
- adc_buf[1] → Joystick X
- adc_buf[2] → AS5600 OUT

---

# 6 调试与状态信号

## LED / Status

- 状态灯：由软件控制，具体引脚以当前代码实现为准

## USART

- 串口调试功能已存在
- 具体 TX / RX 引脚以当前代码实现为准

---

# 7 当前未使用或待确认信号

## Driver Status Pins

- FAULT → 未使用
- SLEEP → 未使用
- RESET → 未使用

## Planned Signals

- EN → PB12（planned）

---

# 8 使用说明

当以下内容发生变化时，必须同步更新本文件：

- PWM 控制引脚变更
- ADC 采样引脚变更
- 编码器接线变更
- Driver 板控制信号变更
- Key / Joystick 接线变更