# A* 算法

## 简介
A*算法是一种常用的启发式搜索算法，用于图遍历和路径规划问题。它有效地找到了从给定起点到目标点的最优路径。

## 算法步骤

1. **初始化：**
   - 将起始节点放入开放列表中，并将其初始成本设为0。

2. **重复以下步骤，直到找到路径或确定不存在路径：**
   a. 从开放列表中选择具有最低总成本的节点。
   b. 将所选节点标记为已关闭，表示已经考虑过它。
   c. 遍历所选节点的相邻节点：
      i. 对于每个相邻节点，计算从起始节点到该节点的实际成本（通常是已经走过的路径长度）。
      ii. 如果相邻节点不在开放列表中，则将其添加到开放列表中，并计算其总成本（实际成本加上启发式估计成本）。
      iii. 如果相邻节点已经在开放列表中，并且新的实际成本比已有的实际成本小，则更新该节点的实际成本，并重新计算总成本。(把新值加入队列的同时，**可以移除旧值也可不移除？**)

3. **当达到目标节点或开放列表为空时停止搜索。**

4. **如果达到目标节点，则从目标节点开始回溯，直到回到起始节点，构建出最优路径。**

## 启发式函数
在A*算法中，使用启发式函数来估计从当前节点到目标节点的成本。这种估计影响节点的总成本，指导算法朝着最有希望的方向前进，提高搜索效率。