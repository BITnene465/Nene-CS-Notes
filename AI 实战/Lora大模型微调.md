# 大模型微调

该任务为大三上 nlp 第四次实践作业

使用大模型为 Qwen2-1.5b， 微调方法为 LoRA

相关学习点：

- transformers 库的基本使用
    - tokenizer 分词
    - feature extractor 预处理图像
    - 大模型和其他模型的基础调用方法
- 自回归模型进行 seq2seq 任务的训练方式与 loss 函数的构建
- LoRA 的接口调用





### transformers 库

在调用 `generate` 方法时，参数设置对生成文本的质量和多样性有很大影响。以下是一些常用的参数及其作用，我会帮你将参数设置得更加齐全和合理。

------

####  1. **常用参数说明**

| 参数名                 | 作用                                                         | 推荐值或示例                                        |
| :--------------------- | :----------------------------------------------------------- | :-------------------------------------------------- |
| `inputs_embeds`        | 输入的嵌入向量，替代 `input_ids`。                           | `combined_input`（你的输入）                        |
| `max_length`           | 生成文本的最大长度。                                         | 50（根据任务需求调整）                              |
| `max_new_tokens`       | 生成的新 token 数量（优先使用，避免与 `max_length` 冲突）。  | 50（根据任务需求调整）                              |
| `num_beams`            | Beam Search 的 beam 数量，增加生成文本的质量，但会降低多样性。 | 4（默认值，可根据任务调整）                         |
| `early_stopping`       | 是否在生成满足条件时提前停止。                               | `True`                                              |
| `pad_token_id`         | 填充 token 的 ID。                                           | `self.ar_model.config.pad_token_id`                 |
| `eos_token_id`         | 结束 token 的 ID。                                           | `self.ar_model.config.eos_token_id`                 |
| `do_sample`            | 是否使用采样（sampling）生成文本。                           | `True`（增加多样性）                                |
| `top_k`                | Top-k 采样，保留概率最高的 k 个 token。                      | 50（默认值，可根据任务调整）                        |
| `top_p`                | Top-p（nucleus）采样，保留概率累积和超过 p 的最小 token 集合。 | 0.9（默认值，可根据任务调整）                       |
| `temperature`          | 温度参数，控制生成文本的随机性。                             | 0.7（默认值，可根据任务调整）                       |
| `repetition_penalty`   | 重复惩罚因子，避免生成重复文本。                             | 1.2（默认值，可根据任务调整）                       |
| `length_penalty`       | 长度惩罚因子，控制生成文本的长度。                           | 1.0（默认值，大于 1 鼓励长文本，小于 1 鼓励短文本） |
| `no_repeat_ngram_size` | 禁止重复的 n-gram 大小。                                     | 3（默认值，可根据任务调整）                         |
| `num_return_sequences` | 返回的生成文本数量。                                         | 1（默认值，可根据任务调整）                         |

------

####  2. **完整代码示例**

```python
generated_ids = self.ar_model.generate(
    inputs_embeds=combined_input,  # 输入特征
    max_length=50,  # 生成文本的最大长度
    max_new_tokens=50,  # 生成的新 token 数量（优先使用）
    num_beams=4,  # Beam Search 的 beam 数量
    early_stopping=True,  # 提前停止
    pad_token_id=self.ar_model.config.pad_token_id,  # 填充 token ID
    eos_token_id=self.ar_model.config.eos_token_id,  # 结束 token ID
    do_sample=True,  # 使用采样生成文本
    top_k=50,  # Top-k 采样
    top_p=0.9,  # Top-p 采样
    temperature=0.7,  # 温度参数
    repetition_penalty=1.2,  # 重复惩罚因子
    length_penalty=1.0,  # 长度惩罚因子
    no_repeat_ngram_size=3,  # 禁止重复的 n-gram 大小
    num_return_sequences=1,  # 返回的生成文本数量
)
```

