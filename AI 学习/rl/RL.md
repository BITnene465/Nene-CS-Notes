# Reinforcement Learning

## Definition

![image-20241025154524318](G:/softwares/typora/typora%20%E5%9B%BE%E7%89%87/RL/image-20241025154524318.png)

## Categorizing RL agents

<img src="G:/softwares/typora/typora%20%E5%9B%BE%E7%89%87/RL/image-20241025154852828.png" alt="image-20241025154852828" style="zoom:80%;" />



## Model Free Evaluation

### Monte Carlo evaluation

<span style="color:#FF6666; border:1px solid #330000;">sample approximation</span>
$$
V_{\pi}(s) = E_{\pi} [\sum_t \gamma^t r_t] \approx \dfrac{1}{n(s)} \sum_{k=1}^n(s) [\sum_t \gamma^t r_t^{(k)}]
$$
**轮次更新形式**
$$
\begin{align*}
	Let \qquad G_k = & \sum_t \gamma^t r_t^{(k)}  \\
	V_n^{\pi} \approx & \dfrac{1}{n(s)} \sum_{k=1}^{n(s)} G_k \\
	 = & V_{n-1}^{\pi} (s) + \dfrac{1}{n(s)} (G_{n(s)} - V_{n-1}^{\pi} (s))
\end{align*}
$$
**Incremental update**   用于算法中: learning rate $\alpha_n = \frac{1}{n(s)}$
$$
V_{n}^{\pi}(s) \ \leftarrow \ V_{n-1}^{\pi}(s) + \alpha_n (G_{n(s)} - V_{n-1}^{\pi}(s))
$$




### Temporal Difference(TD) Evaluation

<span style="color:#FF6666; border:1px solid #330000;">one sample approximation</span>
$$
\begin{align*}
	V^{\pi} (s) &= E[r \ | \ s, \pi(s)] + \gamma \sum_{s'} Pr(s' \ | \ s, \pi(s)) V^{\pi} (s')  \\
	 & \approx r + \gamma V^{\pi} (s')
\end{align*}
$$
**Incremental update**
$$
V^{\pi}_{n}(s) \ \leftarrow \ V^{\pi}_{n-1}(s) + \alpha_n(r + \gamma V^{\pi}_{n-1}(s') - V^{\pi}_{n-1}(s))
$$
**about learning rate:**

(1) $\sum_n \alpha_n \ \rightarrow \infty$

(2) $\sum_n(\alpha_n)^2$ 收敛

常取 $\alpha_n = \frac{1}{n(s)}$



**算法伪代码：**

<img src="G:/softwares/typora/typora%20%E5%9B%BE%E7%89%87/RL/image-20241025163039927.png" alt="image-20241025163039927" style="zoom:80%;" />



## Model Free Control

### Q Value

**definition:**

$Q^{\pi}(s, a)$ : value of executing $a$ followed by $\pi$ 
$$
Q^{\pi} (s, a) = E[r \ | \ s, a] + \gamma \sum_{s'} Pr(s' \ | \ s, a) V^{\pi} (s')
$$


### Bellman’s Equation (upd)

<img src="G:/softwares/typora/typora%20%E5%9B%BE%E7%89%87/RL/image-20241025170953795.png" alt="image-20241025170953795" style="zoom: 67%;" />



### Monte Carlo Control

<img src="G:/softwares/typora/typora%20%E5%9B%BE%E7%89%87/RL/image-20241025171201907.png" alt="image-20241025171201907" style="zoom: 67%;" />



### TD Control

**Approximate Q-function**
$$
\begin{align*}
Q^* (s, a) & = E[r \ | \ s, a] + \gamma \sum_{s'} Pr(s' \ | \ s, a) max_{a'} Q^*(s', a') \\
& \approx r + \gamma max_{a'} Q^*(s', a')
\end{align*}
$$




**Incremental update**
$$
Q^{*}_n(s, a) \ \leftarrow \ Q_{n-1}^*(s, a) + \alpha_n (r + \gamma_{a'} Q_{n-1}^*(s' ,a') - Q^*_{n-1}(s, a))
$$


**Q-learning Algorithm (TD control)**

<img src="G:/softwares/typora/typora%20%E5%9B%BE%E7%89%87/RL/image-20241025172059313.png" alt="image-20241025172059313" style="zoom:80%;" />

**Q-learning example:**

<img src="G:/softwares/typora/typora%20%E5%9B%BE%E7%89%87/RL/image-20241025172413188.png" alt="image-20241025172413188" style="zoom: 67%;" />
