# Project TODO

本文件用于记录：

- 当前开发任务
- 当前发现的问题
- 各阶段开发计划
- 开发约定与检查清单

Notes 目录中的开发记录 **统一写入本文件**，非必要不要新增 Notes 文件。

---

## 当前硬件

- MCU: STM32F103C8
- Driver Board: SimpleFOCMini
- Driver Chip: MS8313
- Motor: BLDC
- Encoder: AS5600

---

## 当前硬件连接

### Motor Control

- IN1 → PA10
- IN2 → PA9
- IN3 → PA8
- EN → PB12（planned）

### Motor Phase

- OUT1 → Motor U
- OUT2 → Motor V
- OUT3 → Motor W

### Encoder

- VDD → 3.3V
- GND → GND
- OUT → PB1
- PGO → PB11

当前使用 **OUT 模拟模式**

### Input

- Joystick X → PA5
- Joystick Y → PA4
- Key → PA3

---

## 当前已完成

- GitHub 仓库建立
- main / dev / feature/algorithm-sandbox 分支建立
- ADC + DMA + 中断 + 主循环打印基础链路跑通
- .gitignore 初步整理
- 编译产物从 Git 跟踪中移除
- Embedded IDE 下载配置修正，工程可构建可下载
- 摇杆 ADC 读取
- AS5600 OUT 模式读取
- 电机 GPIO 驱动验证
- Docs 文档结构建立

---

## 当前工程结构

- Hardware
- Library
- Start
- System
- User
- Docs

---

## 当前发现的问题

### 代码问题

- [ ] 中断和主循环共享变量未加 `volatile`
- [ ] USART 初始化和 GPIO 配置不一致
- [ ] USART 初始化缺少 `USART_Cmd(...)`
- [ ] ADC 通道注释与实际通道不一致
- [ ] 命名存在拼写问题（如 `filer` / `Perioh`）

### 结构问题

- [ ] BLDC 换相表目前不是完整正确版本
- [ ] AD 模块接口边界保护不足
- [ ] 初始化代码写死较多，改动时牵一发而动全身
- [ ] 工程还未完全按驱动板真实硬件完成引脚核对

---

## 文档待整理

- [✓] SimpleFOCMini 驱动板说明
- [✓] STM32F103C8 数据手册
- [✓] STM32F103 参考手册
- [ ] 电机参数资料
- [ ] 接线说明
- [ ] 同步更新 `hardware_map.md`
- [ ] 同步更新 `project_structure.md`

---

## 当前开发阶段

当前阶段：

**编码器模块整理**

当前目标：

- 独立 encoder 模块
- 梳理 ADC → Angle 的处理流程
- 保持当前工程结构可继续支撑开发

---

## 下一步计划

- [ ] 核对 PWM / ADC / 串口 / 编码器引脚
- [ ] 梳理 AD 模块职责
- [ ] 独立 encoder 模块
- [ ] 再进入 PWM 电机驱动开发
- [ ] 再进入算法开发

---

## 编码器阶段计划

当前使用编码器：**AS5600**

当前模式：**OUT 模拟输出**

当前目标：

- 先实现 OUT 模式读取
- 验证磁铁安装和角度输出
- 后续再学习并实现 I2C 模式

当前优先级：

1. 编码器供电与接线确认
2. OUT 信号读取方式确认
3. 磁铁安装间隙与同心度检查
4. 输出角度稳定性验证
5. 后续再实现 I2C 读取

---

## ADC Channel Mapping

| DMA槽位 | ADC通道 | 引脚 | 信号 |
|--------|--------|------|------|
| 0 | ADC_Channel_4 | PA4 | Joystick Y |
| 1 | ADC_Channel_5 | PA5 | Joystick X |
| 2 | ADC_Channel_9 | PB1 | AS5600 OUT |

### DMA Buffer 对应关系

- adc_buf[0] -> Joystick Y
- adc_buf[1] -> Joystick X
- adc_buf[2] -> AS5600 OUT

---

## ADC 新增通道检查清单

每次新增 ADC 采样通道时，需要同步检查以下内容：

- [ ] GPIO 模拟输入配置
- [ ] `ADC_Channel_x` 配置
- [ ] 规则通道顺序
- [ ] 规则通道总数
- [ ] DMA 传输个数
- [ ] DMA 数组大小
- [ ] 中断中的索引和处理逻辑
- [ ] 主循环中的数据使用
- [ ] 文档更新

---

## 编码器功能完成后的下一步

- [ ] 确认角度范围正确 (0~360°)
- [ ] 确认角度方向正确
- [ ] 测试静止噪声
- [ ] 实现角速度计算
- [ ] 处理角度跨 360° 问题
- [ ] 建立编码器模块 (`encoder.c / encoder.h`)

---

## PWM 驱动阶段计划

目标：

- 使用 TIM1 输出 PWM
- 替换当前 GPIO 电机控制方式
- 为后续 FOC 控制做准备

任务：

- [ ] 梳理 TIM1 PWM 输出引脚配置
- [ ] 完成 PWM 初始化
- [ ] 替换 GPIO 控制逻辑
- [ ] 验证电机可被 PWM 驱动
- [ ] 建立 motor / pwm 模块

---

## 模块接口规范（计划）

目标：

统一项目模块接口风格，减少后期维护混乱。

### 统一命名方向

建议逐步统一为：

- `Ad_` / `ADC_`：采样相关
- `Encoder_`：编码器相关
- `Motor_`：电机相关
- `Key_`：按键相关
- `Pwm_`：PWM相关

### 编码器模块接口目标

- [ ] `Encoder_Init()`
- [ ] `Encoder_Update()`
- [ ] `Encoder_GetAngle()`
- [ ] `Encoder_GetRawAdc()`

### AD 模块接口约定

- [ ] ADC 原始数据只能通过接口获取
- [ ] 外部不直接访问 `data[]`
- [ ] 使用 `get_ad_data()` 读取指定通道数据

### main 函数职责约定

- [ ] main 只负责初始化、模块调用、调试输出
- [ ] 不在 main 中堆积业务逻辑
- [ ] 具体功能必须逐步拆到模块内部

---

## 开发规则

- [ ] AI 不直接给完整实现代码
- [ ] AI 需要先给思路，再给步骤，再逐步实现
- [ ] 每次开发必须明确：
  - 修改位置
  - 修改内容
  - 验证方法
- [ ] 模块内部变量优先使用 `static`
- [ ] Notes 目录非必要不要新增文件