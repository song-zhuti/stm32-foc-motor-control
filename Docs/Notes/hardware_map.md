# Hardware Map — STM32 BLDC Project

本文件用于记录项目的 **硬件连接关系与引脚映射**。

本文件只描述：

- MCU
- 电机驱动板
- 电机连接
- 编码器连接
- 用户输入
- ADC 通道映射
- 控制引脚

本文件 **不记录软件结构**。  
软件结构请参考：

Docs/Notes/project_structure.md

本文件 **不记录开发任务和开发日志**。  
开发记录请参考：

Docs/Notes/Plain next.md

---

# 1 MCU

MCU：

STM32F103C8

---

# 2 Driver Board

Driver Board：

SimpleFOCmini

Driver Chip：

MS8313

---

# 3 Motor

Motor：

BLDC Motor

---

# 4 Motor Driver Control

Driver 控制引脚：

IN1 → PA10  
IN2 → PA9  
IN3 → PA8  

Enable：

EN → PB12（planned）

---

# 5 Motor Phase Output

Driver 输出：

OUT1 → Motor U  
OUT2 → Motor V  
OUT3 → Motor W  

---

# 6 Encoder

Encoder：

AS5600 Magnetic Encoder

当前使用模式：

OUT 模拟输出

---

## Encoder Power

VDD → 3.3V  
GND → GND  

---

## Encoder Signal

OUT → PB1  
PGO → PB11  

I2C 当前未使用：

SCL → 未使用  
SDA → 未使用  

---

# 7 User Input

Joystick：

Joystick Y → PA4  
Joystick X → PA5  

Key：

Key → PA3  

---

# 8 ADC Channel Mapping

| DMA Slot | ADC Channel | Pin | Signal |
|---------|-------------|-----|-------|
| 0 | ADC_Channel_4 | PA4 | Joystick Y |
| 1 | ADC_Channel_5 | PA5 | Joystick X |
| 2 | ADC_Channel_9 | PB1 | AS5600 OUT |

---

# 9 DMA Buffer Mapping


adc_buf[0] → Joystick Y
adc_buf[1] → Joystick X
adc_buf[2] → AS5600 OUT


---

# 10 Debug Interface

当前调试方式：

- 串口调试
- OLED 显示
- LED 状态指示