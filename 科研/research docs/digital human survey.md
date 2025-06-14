# Digital Human

## 介绍

数字人技术的最大难点是说话时的**口型**和**头面部动作**。

其次是**实时性**，比如在直播领域的应用。



## 分类

### 基于图像、视频生成

以图像/视频为表达载体，无需三维结构。核心工作包括：

- 基于音频驱动 

  Wav2Lip（语音驱动唇形同步）、MakeItTalk（隐式关键点映射）、SadTalker（3D运动系数生成）

- 基于视频驱动 

  face-vid2vid（支持自由视角生成）、LivePortrait（高效动画迁移 -- 快手开发、阿里云 MetaHuman）



**前沿进展** 

- 微软VASA-1实现多表情高保真生成，通过 control signal 来控制脸部表情生成，基于音频驱动。

- 复旦Hallo系列，基于音频驱动结合扩散模型提升音画一致性



### 参数化方法

例如 sadtalker 中的 expNet 会提取 3DMM 参数，然后使用3DMM渲染为2d图像

vasa-1中也会从单张参考图片和音频片段中提取 control signal ，然后再利用这些control signal 进行 transformer diffusion的生成。







## 技术分析

### 一、技术发展时间线

1. **Wav2Lip (2020)**  
   
   - 首个实现高精度唇形同步的GAN模型  
   - 依赖参考视频输入，仅生成唇部动作  
   - 开源社区广泛应用 
   
2. **SadTalker (2022)**  
   - 引入3DMM（三维可形变模型）生成头部姿态与表情  
   - 支持从单张图像生成动态视频  
   - 核心创新：ExpNet模块实现音频到3D运动参数映射 

3. **MakeItTalk (2021)**  
   - LSTM+CNN架构预测面部关键点运动  
   - 支持跨身份生成（如大叔变少女）  
   - 局限性：复杂头部运动易失真 

4. **Face-vid2vid (2019) → LivePortrait (2024)**  
   
   - Face-vid2vid：视频驱动的3D面部动画生成  
   - LivePortrait改进：两阶段训练+区域稳定性策略  
   - 实现跨身份动画生成（如真人→卡通形象） 
   
5. **VASA-1 (2024)**  
   
   - 微软实时生成3D面部动画框架  
   - 支持情感化表达（如微笑、皱眉）  
   - 扩散Transformer模型处理艺术照片与非英语语音 
   
   <img src="./digital human survey.assets/image-20250515174343987.png" alt="image-20250515174343987" style="zoom: 25%;" />
   
   
   
6. **Hallo (2024)**  
   - 端到端扩散模型实现高精度唇部同步  
   - 解耦学习机制分离形状/纹理/动作特征  
   - 开源项目，支持参数化控制眼部/唇部张闭 







### 二、核心技术对比

| 技术             | 输入类型         | 核心架构              | 生成特性                       | 实时性         | 开源状态 |
| ---------------- | ---------------- | --------------------- | ------------------------------ | -------------- | -------- |
| **Wav2Lip**      | 视频 + 音频      | GAN + 双判别器        | 唇部动作同步，依赖参考视频     | 高             | 开源     |
| **SadTalker**    | 图像 + 音频      | 3DMM + ExpNet         | 头部姿态/表情/唇部，三维渲染   | 中             | 开源     |
| **MakeItTalk**   | 图像 + 音频      | LSTM/CNN + 特征点预测 | 唇部/眉毛/下巴动作+头部姿态    | 高             | 开源     |
| **Face-vid2vid** | 图像 + 视频      | GAN + 运动特征提取    | 视频驱动动画，需参考动作序列   | 中             | 未开源   |
| **LivePortrait** | 图像 + 音频/视频 | 两阶段训练+区域约束   | 稳定跨身份生成，支持参数化控制 | 高             | 开源     |
| **VASA-1**       | 图像 + 音频      | 扩散Transformer       | 实时3D动画，情感化表情         | 极高           | 未开源   |
| **Hallo**        | 图像 + 音频      | 扩散模型 + UNet       | 高精度唇部同步，解耦特征学习   | 低（迭代生成） | 开源     |

---

### 三、应用场景分析

1. **影视与娱乐产业**  
   - **VASA-1**：复活已故演员/电影角色生成   
   - **Hallo**：高质量虚拟主播、AI换脸短视频   

2. **虚拟数字人与客服**  
   - **SadTalker**：企业级虚拟客服、教育场景   
   - **LivePortrait**：跨身份数字人生成（如真人→卡通）   

3. **视频内容创作**  
   - **Wav2Lip**：低成本视频配音、口播视频生成   
   - **MakeItTalk**：静态图像转动态社交媒体内容   

4. **科研与开源生态**  
   - **Face-vid2vid**：作为基础框架推动后续改进（如LivePortrait）   
   - **Hallo**：扩散模型研究与个性化表情控制实验   

---

### 四、技术演进趋势

1. **从2D到3D建模**  
   - SadTalker/VASA-1采用3DMM实现自然头部运动，超越Wav2Lip的2D特征点预测 

2. **生成质量提升路径**  
   - 传统GAN → 扩散模型（Hallo） → 扩散Transformer（VASA-1） 

3. **实时性优化方向**  
   - LivePortrait两阶段训练策略 vs VASA-1的微软级工程优化 

4. **可控性增强**  
   - Hallo的参数化解耦学习 vs LivePortrait的区域稳定性控制 





### 







## live2d ？数字人



很少有人做这方面的数字人，可能是因为应用场景不广：主要是虚拟主播等行业在使用，并且都是由真人面捕实现数字人动作和面部表情。很少有纯ai驱动的live2d数字人。

其实也有相关的数字人，可是没有成熟的商业落地方案和成熟的开源方案：

- yotube 上的虚拟主播 neuro，母语为英文
- bilibili 上的虚拟主播 木几萌，母语为中文























