# Hardware Map

## MCU
STM32F103C8

## Driver Board
SimpleFOCmini

Driver Chip : MS8313

## Motor
BLDC Motor

## Encoder
AS5600 Magnetic Encoder

---

# Control Interface

## Motor Phase Output

OUT1 -> Motor U
OUT2 -> Motor V
OUT3 -> Motor W

## PWM Control

IN1 : PA10
IN2 : PA9
IN3 : PA8

## Enable Control

EN : PB12 (planned)

## Status Signals

FAULT : 未使用
SLEEP : 未使用
RESET : 未使用

## Encoder
AS5600

## Encoder Interface (current plan)

VDD : 3.3V
GND : GND
OUT : PB10
PGO : 3.3V

SCL : 未使用
SDA : 未使用

## ADC Channel Mapping

| DMA槽位 | ADC通道 | 引脚 | 信号 |
|--------|--------|------|------|
| 0 | ADC_Channel_1 | PA4 | Joystick Y |
| 1 | ADC_Channel_2 | PA5 | Joystick X |
| 2 | ADC_Channel_9 | PB1 | AS5600 OUT |

## Digital Inputs

Key : PB13