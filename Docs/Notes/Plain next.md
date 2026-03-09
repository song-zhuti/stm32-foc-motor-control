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

**基础架构整理阶段**

目标：

- 保证工程结构稳定
- 明确模块职责
- 为后续控制算法开发做准备

---

# 当前开发任务

当前任务：

1 整理 Encoder 模块

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