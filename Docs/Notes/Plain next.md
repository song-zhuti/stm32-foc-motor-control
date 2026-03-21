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

**硬件控制框架整理与验证阶段**

当前状态：

- TIM3 基础节拍源已可用
- ADC + DMA + 滤波链路保持可用
- AS5600 OUT 模拟量读取可用
- OLED 调试显示可用
- 当前控制调度骨架仅用于验证执行流，不作为正式 FOC 执行方案

当前目标：

- 先完成硬件控制框架整理
- 先确认 PWM 输出链路
- 先确认 Encoder 反馈链路
- 先明确 Motor / PWM / Encoder 模块边界
- 暂不推进 FOC 实时执行迁移

---

# 当前开发任务

当前任务：

1 先完成硬件控制框架整理

目标：

- 保持 ADC + DMA + 滤波链路稳定
- 明确 Encoder 模块输入输出接口
- 明确 PWM 模块初始化与输出接口
- 明确 Motor 模块职责与控制入口
- 保持 TIM3 仅作为基础节拍与调试验证使用
- foc 模块暂只保留骨架，不进入正式实时执行阶段

当前优先事项：

- 梳理 TIM1 PWM 输出引脚与初始化方案
- 整理 Encoder 模块接口
- 整理 Motor / PWM / Encoder 模块边界
- 核对硬件引脚映射与代码配置一致性
- 为后续闭环控制预留接口

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
- TIM3 基础节拍调度跑通
- 主循环基于 Tim3_tick 的异步任务执行跑通

---

# 下一阶段开发计划

短期任务：

- [ ] 核对硬件引脚映射与代码配置一致性
- [ ] 梳理 TIM1 PWM 输出引脚
- [ ] 完成 PWM 初始化方案设计
- [ ] 整理 AD 模块接口
- [ ] 独立 Encoder 模块
- [ ] 明确 Motor / PWM / Encoder 模块接口关系
- [ ] 保持当前 TIM3 调度骨架仅用于验证，不继续扩展为正式 FOC 执行结构

中期任务：

- [ ] 建立 PWM 驱动模块
- [ ] 使用 TIM1 输出 PWM
- [ ] 替换当前 GPIO 电机驱动
- [ ] 验证 Encoder 反馈链路稳定性
- [ ] 建立基础 Motor 控制模块

长期目标：

- [ ] 实现角度连续化处理
- [ ] 实现角速度计算
- [ ] 建立第一个闭环控制实验
- [ ] 在硬件链路稳定后迁移到实时控制执行结构
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

# Control Scheduling Note (temporary)

当前工程中的控制任务调度方式属于 **过渡方案**。

当前结构：

TIM3 interrupt
↓
tick update / pending mark
↓
main loop
↓
control task execution

说明：

- 当前方案的目标是先建立控制模块骨架
- 当前方案用于验证执行流、模块接口和调度关系
- 当前方案不是最终的 FOC 执行结构

原因：

- 主循环中的 OLED 显示、调试输出和其他耗时操作会影响控制任务的实际执行时刻
- 即使定时器节拍固定，主循环异步执行仍然会引入控制周期抖动
- 对真正的 FOC 算法来说，控制周期应尽量固定、实时、可预测

后续目标：

当完成以下条件后，应将控制算法迁移到严格周期执行结构：

- Encoder 反馈链路稳定
- PWM 输出链路稳定
- 第一个闭环控制实验完成

最终目标结构：

Timer / PWM synchronized interrupt
↓
sensor update
↓
control algorithm
↓
PWM update

结论：

当前 main loop 异步执行只作为控制框架验证方案使用，
未来真正的 FOC 核心算法不应长期放在主循环中执行。

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

将建立独立的数据流文档。
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

# Current Strategy Note

当前阶段策略：

当前工程优先完成硬件控制框架整理，不提前推进正式 FOC 实时执行迁移。

说明：

- 当前 TIM3 + main loop 调度骨架仅用于验证模块接口与执行流
- 当前阶段重点不是控制算法本身，而是硬件链路与模块边界整理
- 在 PWM 输出链路、Encoder 反馈链路、Motor 控制模块未稳定前，不进入正式实时闭环控制阶段
- 当硬件框架稳定后，再重新规划 FOC 的实时执行位置与控制周期结构

当前优先级：

硬件链路稳定性  
> 模块边界清晰  
> 基础控制框架可扩展  
> FOC 实时执行迁移

# 今日开发记录

今日主要工作：

完成 TIM1 PWM 初始化学习与验证。

当前进展：

- 已完成 TIM1 PWM 基础配置
- 已理解 PSC / ARR / CCR 对 PWM 的影响
- 已确认 PWM 占空比由 CCR 控制
- 已确认运行时可通过 `TIM_SetComparex()` 修改 CCR
- 已理解高级定时器 TIM1 需要调用 `TIM_CtrlPWMOutputs()` 才能输出 PWM

当前系统状态：

TIM1 PWM 输出链路已经基本跑通，可输出 PWM 波形。

当前阶段仍处于 **硬件控制框架整理阶段**，
PWM 配置目前用于验证驱动链路，不作为最终控制方案。

后续学习内容：

- `TIM_CtrlPWMOutputs()` 工作机制
- CCR Preload 机制
- PWM 周期更新方式

下一步计划：

- 整理 PWM 初始化代码结构
- 明确 PWM 模块接口
- 梳理 Motor / PWM / Encoder 模块边界
- vscode的快捷键有的冲突研究解决一下