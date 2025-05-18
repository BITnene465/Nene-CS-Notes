# MDP Learning

## Markov Decision Process

### intro

<img src="G:/softwares/typora/typora%20%E5%9B%BE%E7%89%87/MDP%20learning/image-20241011170041660.png" alt="image-20241011170041660" style="zoom:67%;" />



```python
class MDP:
    '''一个简单的MDP类，它包含如下成员'''

    def __init__(self,T,R,discount):
        '''构建MDP类

        输入:
        T -- 转移函数: |A| x |S| x |S'| array
        R -- 奖励函数: |A| x |S| array
        discount -- 折扣因子: scalar in [0,1)

        构造函数检验输入是否有效，并在MDP对象中构建相应变量'''

        assert T.ndim == 3, "转移函数无效，应该有3个维度"
        self.nActions = T.shape[0]
        self.nStates = T.shape[1]
        assert T.shape == (self.nActions,self.nStates,self.nStates), "无效的转换函数：它具有维度 " + repr(T.shape) + ", 但它应该是(nActions,nStates,nStates)"
        assert (abs(T.sum(2)-1) < 1e-5).all(), "无效的转移函数：某些转移概率不等于1"
        self.T = T
        assert R.ndim == 2, "奖励功能无效：应该有2个维度"
        assert R.shape == (self.nActions,self.nStates), "奖励函数无效：它具有维度 " + repr(R.shape) + ", 但它应该是 (nActions,nStates)"
        self.R = R
        assert 0 <= discount < 1, "折扣系数无效：它应该在[0,1]中"
        self.discount = discount
```

### policy evaluation

评估一个策略 $\pi$ , 得到在该策略下的 $V$ 值
$$
V^{\pi} = \sum_{t=0}^h 
$$




### optimal policy

最优策略为 $\pi^*$
$$
V^{\pi^*}(s_0) \ \ge \ V^{\pi}(s_0)  \qquad \forall \ \pi
$$


## policy optimization

### Bellman’s Equation

#### normal form

$$
V(s_t) = max_{a_t} (R(s_t, a_t) + \gamma \sum_{s_{t+1}} P(s_{t+1} | s_t, \ a_t) V(s_{t+1}))  \\
\pi(s_t) = argmax_{a_t} (R(s_t, a_t) + \gamma \sum_{s_{t+1}} P(s_{t+1} | s_t, \ a_t) V(s_{t+1}))
$$



#### infinite horizon





### policy evaluation

> 

#### intro

<img src="G:/softwares/typora/typora%20%E5%9B%BE%E7%89%87/MDP%20learning/image-20241011162327904.png" alt="image-20241011162327904" style="zoom:67%;" />

此处的 $T$ 实际上的含义为 $T^{\pi}$  
$$
\mathbf{evaluation}: policy  \rightarrow V
$$



#### solving linear system

> **但是矩阵不总是有逆, 可以直接解 Ax = B**

当操作步为 **无穷** 时，根据 **Bellman’s Equation 的矩阵形式**，有
$$
\mathbf{V} = \mathbf{R} + \gamma \mathbf{TV}  \\
(\mathbf{I} - \gamma \mathbf{T}) \mathbf{V} = \mathbf{R} \\
\mathbf{V} = (\mathbf{I} - \gamma \mathbf{T})^{-1} \mathbf{R}
$$

```python
    def evaluatePolicy(self, policy):
        '''通过求解线性方程组来评估策略
        V^pi = R^pi + gamma T^pi V^pi

        Input:
        policy -- 策略: 大小为|S|的array

        Ouput:
        V -- 值函数: 大小为|S|的array'''

        V = np.zeros(self.nStates)
        T_pi = np.zeros((self.nStates, self.nStates))  # |S| x |S'| 矩阵
        R_pi = np.zeros(self.nStates)  # |S| 向量

        for s in range(self.nStates):
            a = policy[s]  # 获取当前状态 s 的策略动作
            R_pi[s] = self.R[a, s]  # 奖励函数
            T_pi[s, :] = self.T[a, s, :]  # 转移概率

        # 使用线性方程组求解 V
        I = np.eye(self.nStates)
        V = np.linalg.solve(I - self.discount * T_pi, R_pi)  # 求解方程

        return V
```



#### iteration method


$$
repeat \qquad \mathbf{V} \ \leftarrow \ \mathbf{R} \ + \  \gamma \mathbf{TV}
$$

```python
    def evaluatePolicyPartially(self, policy, initialV, nIterations=np.inf, tolerance=0.01):
        '''部分的策略评估:
        Repeat V^pi <-- R^pi + gamma T^pi V^pi

        Inputs:
        policy -- 策略: 大小为|S|的array
        initialV -- 初始的值函数: 大小为|S|的array
        nIterations -- 迭代数量的限制: 标量 (默认值: infinity)
        tolerance --  ||V^n-V^n+1||_inf的阈值: 标量 (默认值: 0.01)

        Outputs:
        V -- 值函数: 大小为|S|的array
        iterId -- 迭代执行的次数: 标量
        epsilon -- ||V^n-V^n+1||_inf: 标量'''

        V = initialV
        iterId = 0
        epsilon = 0

        while iterId < nIterations:
            V_new = np.zeros(self.nStates)
            for s in range(self.nStates):
                a = policy[s]  # 获取当前状态 s 的策略动作
                V_new[s] = self.R[a, s] + self.discount * np.sum(self.T[a, s, :] * V)   # 注意此处不是点乘

            epsilon = np.max(np.abs(V_new - V))  # 计算收敛性
            if epsilon < tolerance:
                break

            V = V_new
            iterId += 1

        return [V, iterId, epsilon]
```





### value iteration(algorithm)

> **保证收敛到局部极值**, 时间复杂度 $O(n|A||S|^2)$

<img src="G:/softwares/typora/typora%20%E5%9B%BE%E7%89%87/policy%20learning/image-20240927171325583.png" alt="image-20240927171325583" style="zoom: 67%;" />

**使用矩阵运算：**

<img src="G:/softwares/typora/typora%20%E5%9B%BE%E7%89%87/policy%20learning/image-20240927171417376.png" alt="image-20240927171417376" style="zoom:67%;" />



```python
    def valueIteration(self,initialV,nIterations=np.inf,tolerance=0.01):
        '''值迭代法
        V <-- max_a R^a + gamma T^a V

        输入:
        initialV -- 初始的值函数: 大小为|S|的array
        nIterations -- 迭代次数的限制：标量 (默认值: infinity)
        tolerance -- ||V^n-V^n+1||_inf的阈值: 标量 (默认值: 0.01)

        Outputs: 
        V -- 值函数: 大小为|S|的array
        iterId -- 执行的迭代次数: 标量
        epsilon -- ||V^n-V^n+1||_inf: 标量'''

        iterId = 0
        epsilon = 0
        V = initialV
        #填空部分
        Q_matrix = self.R + self.discount * (self.T @ V)
        V_new = np.max(Q_matrix, axis=0)
        iterId += 1
        while np.max(np.abs(V_new - V)) >= tolerance:
            V = V_new
            Q_matrix = self.R + self.discount * (self.T @ V)
            V_new = np.max(Q_matrix, axis=0)
            iterId += 1
        epsilon = np.max(np.abs(V_new - V))

        return [V,iterId,epsilon]
```





### policy iteration

> **保证收敛到全局最优**







