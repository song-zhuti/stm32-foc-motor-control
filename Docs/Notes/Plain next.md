# Development Log & TODO

本文件用于记录：

- 当前开发阶段
- 当前开发任务
- 当前发现的问题
- 开发计划
- TODO 列表

Notes 目录中的开发记录 **统一写入本文件**。

本文件不记录：

- 软件架构
- 硬件连接
- 项目结构

相关文档：

软件结构：
Docs/Notes/project_structure.md

硬件连接：
Docs/Notes/hardware_map.md

AI上下文：
Docs/Notes/ai_context.md

---

# 当前开发阶段

当前阶段：

**从采样显示工程过渡到控制工程阶段**

目标：

- 保持现有 ADC + DMA + 滤波链路稳定
- 建立控制任务骨架
- 为后续 Encoder / PWM / 第一个闭环做准备
---

# 当前开发任务

当前任务：

1 建立控制任务骨架

目标：

- 明确 TIM3 作为控制节拍源
- 将控制逻辑入口放入 foc 模块
- main 循环只保留慢速显示与调试
- 为后续 Encoder 和 PWM 接入做准备

计划接口：

Control_Init()  
Control_Task()  
Control_SetTarget()

2 整理 Encoder 模块

目标：

- 将编码器逻辑从 ADC 模块中分离
- 建立独立的 encoder 模块

计划接口：

Encoder_Init()  
Encoder_Update()  
Encoder_GetAngle()  
Encoder_GetRawAdc()

---

# 当前发现的问题

## 代码问题

- [ ] 中断与主循环共享变量未加 `volatile`
- [ ] USART 初始化与 GPIO 配置不一致
- [ ] USART 初始化缺少 `USART_Cmd(...)`
- [ ] ADC 通道注释与实际配置不一致
- [ ] 命名存在拼写问题（如 `filer` / `Perioh`）

---

## 工程结构问题

- [ ] AD 模块职责边界不清晰
- [ ] 编码器逻辑尚未独立为模块
- [ ] 初始化代码集中度过高
- [ ] 硬件引脚与代码配置尚未完全核对

---

# 当前开发进度

已完成：

- GitHub 仓库建立
- main / dev / feature/algorithm-sandbox 分支建立
- ADC + DMA 基础采样链路
- 摇杆 ADC 读取
- AS5600 OUT 模拟输出读取
- 电机 GPIO 驱动验证
- 文档体系建立
- .gitignore 整理

---

# 下一阶段开发计划

短期任务：

- [ ] 整理 AD 模块接口
- [ ] 独立 Encoder 模块
- [ ] 核对所有 ADC 通道配置

中期任务：

- [ ] 建立 PWM 驱动模块
- [ ] 使用 TIM1 输出 PWM
- [ ] 替换 GPIO 电机驱动

长期目标：

- [ ] 实现角度连续化处理
- [ ] 实现角速度计算
- [ ] 建立电机控制架构
- [ ] 为 FOC 控制做准备

---

# Encoder 开发阶段计划

当前编码器：

**AS5600**

当前模式：

**OUT 模拟输出**

当前目标：

1 确认 OUT 信号读取正确  
2 验证角度范围是否正确  
3 验证静止噪声  
4 实现角度读取接口  

后续计划：

- 实现角度连续化
- 实现角速度计算
- 研究 I2C 模式读取

---

# PWM 驱动阶段计划

目标：

将当前 GPIO 控制方式升级为 **TIM PWM 驱动**。

任务：

- [ ] 梳理 TIM1 PWM 输出引脚
- [ ] 完成 PWM 初始化
- [ ] 建立 PWM 驱动模块
- [ ] 替换当前 GPIO 控制逻辑
- [ ] 验证电机 PWM 控制

---

# 开发检查清单

每次修改工程前检查：

- [ ] 是否影响 ADC 采样
- [ ] 是否影响 DMA 配置
- [ ] 是否影响中断逻辑
- [ ] 是否影响模块接口
- [ ] 是否需要同步更新文档

---

# 文档同步检查

当以下内容发生变化时，需要同步更新对应文档：

硬件变化：

→ 更新 `hardware_map.md`

软件结构变化：

→ 更新 `project_structure.md`

开发任务变化：

→ 更新 `Plain next.md`
---

# System Data Flow (temporary)

当前系统数据流：

Sensor
↓
ADC Sampling
↓
DMA Transfer
↓
DMA Interrupt
↓
Low Pass Filter
↓
Filtered Sensor Data
↓
Main Loop
↓
Debug Output (OLED)

说明：

当前系统主要用于：

- 验证 ADC + DMA 采样链路
- 验证编码器模拟信号读取
- 验证数据滤波
- 验证调试输出

当前系统 **不包含控制算法**。

---

# Future Control Flow (target)

未来控制系统目标结构：

Sensor
↓
ADC Sampling
↓
DMA Transfer
↓
Angle Calculation
↓
Control Algorithm
↓
PWM Output
↓
Motor

---

# Data Flow Upgrade Condition

当完成以下目标时：

- Encoder 角度读取稳定
- PWM 电机驱动完成
- 第一个闭环控制实验完成

将建立新的架构文档：

Docs/Architecture/data_flow.md

# Current Codex Tasks

当前阶段需要 Codex 完成的事情：

1. 读取当前项目中的指定文件
2. 分析当前工程从“采样显示工程”过渡到“控制工程”的最小改动路径
3. 基于当前代码修改，分析哪些文件最适合作为第一步改动入口
4. 按文件给出修改建议，不直接生成完整实现代码
5. 检查当前改动是否会影响现有 ADC + DMA + 滤波链路
6. 辅助分析 TIM3 作为控制节拍源是否合理
7. 辅助分析 foc 模块应如何作为控制骨架入口

Codex 当前推荐分析范围：

- User/main.c
- User/stm32f10x_it.c
- Hardware/AD.c
- Hardware/AD.h
- Hardware/Periph_Init.c
- Hardware/Periph_Init.h
- Hardware/Encoder.c
- Hardware/Encoder.h
- Hardware/foc.c
- Hardware/foc.h

当前阶段禁止 Codex 默认执行的事情：

- 不直接修改源码文件
- 不直接重构整个工程
- 不扫描整个项目
- 不直接给出完整实现代码