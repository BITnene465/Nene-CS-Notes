

# LLM video understanding & inference



## introduction

<img src="./LLM-video infer.assets/image-20250607003749394.png" alt="image-20250607003749394" style="zoom:50%;" />

视频理解发展的几个阶段：

1. **传统方式**：基于传统机器学习算法和特征工程，人为设计规则捕捉视频帧的相关信息。
2. **基于人工神经网络的方法：** LSTM 等时序网络来处理视频信息。
3. **自监督视频预训练：** 基于 BERT，在视频-文本数据中进行自监督学习。
4. **Vid-LLM，使用大模型进行视频理解：**  外挂多模态编码器，映射到同一特征空间后由 LLM 统一处理。结构类似，训练范式与训练数据各有不同。

随着大型语言模型（LLM）向多模态扩展，视频推理成为研究热点。视频作为包含时空动态信息的复杂模态，要求模型同时理解视觉内容、时序逻辑与语义关联。当前，LLM 视频推理的核心目标是实现 **“视觉-语言-时序”一体化建模**，例如通过多模态输入（视频+文本）回答问题、预测事件或生成描述 。 



##  benchmark

###  通用视频理解

1. **VideoReasonBench**（Moonshot AI & 北京大学）

- **核心任务**：评估基于视觉内容的复杂推理能力，提出三级推理层级：  
  - **L1 回忆**：准确记忆视频中的操作序列（如滑动拼图的移动路径）  
  - **L2 推断**：推测未直接展示的隐藏状态（如拼图最终排列）  
  - **L3 预测**：预测超出视频范围的新状态（如额外移动后的结果）  
  
- **数据设计**：  
  - 6类合成/真实视频（数字拼图、卡片堆、筹码操作等）  
  - 1,440个问题，操作步骤5-14步，平均视频时长54.3秒  
  

注意点：
当前最优模型（Gemini-2.5-Pro）准确率仅56.0%，远低于人类的73.8% 
删除50%视频帧导致模型性能下降55.5%，证明强视觉依赖性 



2. **MLVU**（智源研究院 & 北邮/北大/浙大）

- **核心任务**：多任务长视频理解（平均12分钟，最长超2小时）  
- **任务设计**： 
  - **9类任务**分三级：全面理解（全局信息）、单细节理解（定位局部事件）、多细节理解（关联多片段）  
  - 采用“细节化代词”指代角色/事件，避免知识先验泄露  
- **模型表现**：  
  - GPT-4o以64.6%准确率领先，但单细节任务不足50%  
  - 视频时长↑ → 模型性能↓（如50+镜头时GPT-4o性能降至75%）  



3. **E.T. Bench**（港理工 & 腾讯，NeurIPS 2024）

- **核心任务**：开放域事件级时序理解  
- **创新点**：  
  - 4大类任务（指代/定位/密集描述/复杂理解），覆盖7K视频（251小时）  
  - 时间敏感型问答，要求模型关联多事件时序逻辑  
- **模型突破**：  
  - 提出 **E.T. Chat** 模型，将时间戳预测重构为特征匹配问题  
  - 在定位任务中F1分数提升12%，但仍显著落后人类  



###  **专用任务评测基准**

1. **Video-Bench**（上海交大 & 斯坦福，CVPR 2025）

- **核心任务**：视频生成质量双维度评估  
  - **视频-条件对齐**：物体/动作/颜色一致性（相关性0.735）  
  - **视频质量**：成像质量、运动合理性、时间一致性  
- **技术亮点**：  
  - 链式查询（CoQ）解决跨模态对齐难题  
  - 少样本评分量化主观美学，人类认同率达73%  

2. **OVO-Bench**（在线视频理解）

- **核心任务**：模拟实时视频流动态推理  
  - **回溯**：追溯过去事件（如“3分钟前发生了什么？”）  
  - **实时理解**：响应当前事件（如“屏幕正在显示什么？”）  
  - **前瞻响应**：延迟回答至未来关键帧（如“等10秒后回答”）  
- **价值**：填补在线模型评估空白，揭示商业模型动态推理短板  

3. **VAU-Bench**（视频异常理解）

- **任务设计**：异常事件四阶段评估（感知→定位→推理→结论）  
- **数据**：4,602个异常视频（169小时），覆盖偷窃、事故等19类场景  
- **突破**：VAU-R1模型通过强化学习将时间定位mIoU提升至33.25%  



### **在线长视频训练基准**

1. **VideoMarathon**（长视频训练数据集）

- **规模**：9,700小时视频（3-60分钟/段），3.3M QA对  
- **任务覆盖**：6大主题（时间/空间/物体/动作/场景/事件）+22类任务  
- **配套模型**：  
  - **Hour-LLaVA**：支持1-FPS采样，缓存全视频上下文，实现小时级推理  

2. **MVBench**（时空理解评测）

- **设计**：20项任务分两大类：  
  - **空间理解**：单帧物体/场景解析  
  - **时间理解**：跨帧动作关联/因果推理  
- **自动化工具**：将公共视频注释转为多选QA，提升评估效率  





### 评测基准对比概览

| **基准名称**     | **类型**     | **视频特点**         | **核心评估能力**         | **最佳模型表现**     |
| ---------------- | ------------ | -------------------- | ------------------------ | -------------------- |
| VideoReasonBench | 通用推理     | 54秒短视频，多步操作 | 三级视觉推理链           | Gemini-2.5-Pro 56.0% |
| MLVU             | 通用长视频   | 3min-2hr，多领域     | 全局/细节/多片段关联理解 | GPT-4o 64.6%         |
| E.T. Bench       | 事件级时序   | 251小时，开放域      | 时间敏感型多事件关联     | E.T. Chat (F1+12%)   |
| OVO-Bench        | 在线动态理解 | 流式视频             | 回溯/实时/前瞻响应       | 闭源模型显著领先     |
| Video-Bench      | 生成质量评估 | AI生成视频           | 条件对齐+质量双维度      | 人类相关性73%        |



###  **总结**

当前视频理解评测正经历三大演进：  
1. **从静态到动态**：传统帧级分析 → 在线流式推理（OVO-Bench）  
2. **从短到长**：1分钟内短视频 → 小时级长视频（VideoMarathon）  
3. **从感知到推理**：物体识别 → 多步状态推演（VideoReasonBench L3）  

未来突破将依赖**时序建模算法**（如时间戳匹配）、**上下文扩展技术**（如分层缓存）及**多模态协同**（视觉+音频+文本），最终逼近人类级视频理解能力。





## 代表性模型和方法

### VideoChat （上海 AI Lab  2023）

#### 模型架构

<img src="./LLM-video infer.assets/image-20250607025641704.png" alt="image-20250607025641704" style="zoom:50%;" />

Video content 由两部分组成：对于视频帧的结构化文本描述，通过外部模型编码得到的 Video embeddings 。

LLM 通过 Video content 和 用户prompt 生成回复内容。

该系统主要处理 “文本 + 视频” 两个模态。



#### 训练流程

两阶段：

1. 视频-文本对齐：在大规模的视频 -文本对（10m）和图像-文本对（15m）上训练（自监督？）
2. 指令微调：在自己构建的视频指令数据集上微调

<img src="./LLM-video infer.assets/image-20250607030953743.png" alt="image-20250607030953743" style="zoom:50%;" />

### VAST （NIPS 2023）

 验证了**全模态预训练**的可行性：视频+语音+字幕+文本  

之前都是分阶段预训练，这里首次采用了全模态统一的预训练 （**下图所示**）

<img src="./LLM-video infer.assets/image-20250607032646923.png" alt="image-20250607032646923" style="zoom:67%;" />



### MaCaw LLM （2023）

#### 模型架构

MLLM 的经典三段式，各种模态的 encoder，对齐到语义模态，拼接后输入 llm中生成文本回复

- **模态模块：**
  - vision encoder：预训练的 clip 
  - audio encoder：预训练的 whisper
  - text encoder：预训练的 LLaMa-7B ，同时也是生成网络的骨干（backbone）
- **对齐模块** ： 将多个模态的信息映射到同一个语义空间（文本模态）
- **认知模块**：使用预训练的 llm 去完成“理解 + 生成” 的任务

<img src="./LLM-video infer.assets/image-20250607031248034.png" alt="image-20250607031248034" style="zoom:67%;" />

#### 训练流程

**数据方面：**

- 文本指令数据集：使用 Alpaca 指令数据集，包含约 52,000 个指令-回复示例。
- 图像指令数据集：从 COCO 图像标题生成约 69K 个指令-回复对。
- 视频指令数据集：从 Charades 和 AVSD 数据集的视频标题生成约 50K 个指令-回复示例。

最终的训练数据集包含 150K 个示例，每种指令数据随机采样 50K 个示例。



**训练方式：**

一阶段 **指令微调**，直接使用交叉熵 loss



#### 创新点

1. **对齐方法的创新**：将多模态特征与大语言模型的文本特征对齐，简化了适应过程，使模型能够自然地处理来自各种模态的表示。
2. **一步指令微调**：将表示对齐和指令微调合并为一个步骤，缓解了多步微调可能带来的错误传播问题，确保了模态间的一致对齐。
3. **大规模多模态指令数据集**：构建了一个包含图像和视频实例的大规模多模态指令数据集，为未来的多模态大语言模型研究奠定了基础。



### LanguageBind （ICLR 2024）

<img src="./LLM-video infer.assets/image-20250606164223321.png" alt="image-20250606164223321" style="zoom:50%;" />

**所有模态向文本模态靠齐** – 为什么？因为文本模态信息量大，并且已经有大量的研究。

通过**冻结文本编码器**然后使用 **文本模态和其他模态的对比学习** 实现



**创新点**：该训练方法可以拓展到更多模态，超越了传统的视觉和语言。









### Video-LLaVA （北大  2024）

<img src="./LLM-video infer.assets/image-20250607010404765.png" alt="image-20250607010404765" style="zoom:80%;" />

Video-LLaVA **统一了图像模态和视频模态的表征**，创新点如下：

1. 在投影前，先将图像和视频表征对齐到统一的视觉特征空间
2. 通过图像和视频的联合训练，相互增强，使得大语言模型同时具备图像和视频理解能力
3. 基于 Transformer 的端到端架构，实现了模型和数据规模的扩展



**经典两阶段训练：**

- 对齐：**图像-文本对**，**视频-文本对** 上训练。
- 指令微调：视觉指令微调。





## Long video understanding



<img src="./LLM-video infer.assets/657bbfe4950bbfe08d3e2b3b0569012c474347248-20250607015135377.png" alt="img" style="zoom:67%;" />

### 现状



多模态大模型视觉理解的三个场景：

- **静态图像理解**：一张或者多张静态图像，只需要按照顺序编码成图像 token，并且用形如 \<image\>\<\image\> 的 special token 包裹起来即可。**仅仅需要关注空间信息**，研究主要在空间的多颗粒度上做文章，一般分为粗颗粒度（全局视觉上下文）和细颗粒度（局部视觉信息）理解。
- **短视频理解**：短视频一般是几秒钟，包含几十帧图像。此时就算只是将所有帧都变成 image token 然后再加上时间位置编码或 token 压缩和摘要系统，也还算是可以接受的。 **包含事件内部的时间信息和时空推理。**
- **长视频理解**：长视频一般是几分钟到几小时，包含成千上万的视频帧。面临很多问题，例如视觉 token 爆炸（万帧以上导致 context length 溢出）、全局一致性建模（模型没有办法保持对整个视频内容的连续理解）。**可能包含多个事件，需要处理事件内部事件推理和跨事件推理。**

目前而言，长视频理解任务上模型的表现仍然较差，远低于人类水平。（2025.6）



<img src="./LLM-video infer.assets/9874451d2e3bc339aea0fc6b69696cba474347248.png" alt="img" style="zoom:67%;" />

1. 图像级接口 (Image-level Connectors)

 - 单线性层或多层感知机（MLP）。

 - 空间池化、自适应池化、语义相似Token合并等方法。

 - 使用交叉注意力或Transformer结构，如Q-Former和Perceiver Resampler。

2. 视频级接口 (Video-level Connectors)

 - 提取序列化视觉数据并压缩视觉特征。

 - 常用方法包括时间序列池化和Transformer结构，如Video Q-Former。

3. 长视频级接口 (Long-video-level Connectors)
 - 有效压缩长时间视频视觉信息。
 - 结合时间感知设计，保留时空信息。



### 代表模型和方法



### 问题

- **更多长视频训练资源：**高质量的长视频-语言配对预训练数据集和长视频-指令数据集仍然缺乏，这限制了MM-LLM在长视频理解方面的能力。
- **更具挑战性的长视频理解基准：**现有的长视频基准数据集大多集中在某一特定方面，缺乏能够全面评估长视频理解方法的综合性基准。
- **应用场景**：缺乏实时性和全模态整合能力。





## VoT

### 现状



### 代表模型和方法



### 问题

