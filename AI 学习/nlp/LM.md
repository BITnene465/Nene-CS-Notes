# LM

## 梗概

语言模型 -- 评估一个句子的好坏

归类为 **序列评估问题**



<img src="G:/softwares/typora/typora%20%E5%9B%BE%E7%89%87/LM/image-20241029102657934.png" alt="image-20241029102657934" style="zoom:80%;" />

故 LM 常作为 NLP 模型中的“先验模型”



## SLM

### 对 P(W) 建模

 <img src="G:/softwares/typora/typora%20%E5%9B%BE%E7%89%87/LM/image-20241029102500057.png" alt="image-20241029102500057" style="zoom:67%;" />



### n-gram

$$
\begin{align*}
P(W) & = \prod_i P(w_i \ | \ w_1w_2\cdots w_{i-1}) \\ 
 & \approx \prod_i P(w_i \ | \ w_{i-n+1}w_{i-n+2}\cdots w_{i-1}) 
\end{align*}
$$

$P(w_i \ | \ w_{i-n+1}w_{i-n+2}\cdots w_{i-1})$ 通过统计语料库来得到，可以使用平滑技巧

LM 返回的是一个概率分布向量，向量长度就是词汇表的长度



## NNLM

### 起源

2003 年， “A neural probabilistic language model”(NPLM)

- 简单的前馈网络（FNN）
- 不能解决自然语言的长距离依赖
- 首次使用了 **word embedding**

<img src="G:/softwares/typora/typora%20%E5%9B%BE%E7%89%87/LM/image-20241029110024363.png" alt="image-20241029110024363" style="zoom: 67%;" />



### RNNLM

<img src="G:/softwares/typora/typora%20%E5%9B%BE%E7%89%87/LM/image-20241029112302889.png" alt="image-20241029112302889" style="zoom:80%;" />





## Word Embedding

### Word2Vec

#### 论文: CBOW & skip-gram

Mikolov 2013 两篇论文

- “Distributed representations of words and phrases and their compositionality”
- “Efficient estimation of word representations in vector space”



#### Continuous bag of words(CBOW)

**基于分布式假设**： 每个词的含义只与上下文相关

<img src="G:/softwares/typora/typora%20%E5%9B%BE%E7%89%87/LM/image-20241029114855157.png" alt="image-20241029114855157" style="zoom:80%;" />

$w_{1\times V}$ 是 one-hot 编码， 通过降维矩阵 $U_{V\times D}$ 相乘得到词嵌入 $h_{1\times D}$

$h_{1\times V}$ 与升维矩阵 $U^*_{D\times V}$ 相乘得到预测词的概率分布



#### 一些优化策略

- 负采样
- Hierarchical Softmax(分层 softmax)
    - 使用 Huffman 树将单层的 Softmax 计算转化为多次的二分类 sigmoid



### GloVe





### FastText









### 使用



### 训练（学习）



