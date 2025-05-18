## huffman coding

**编码和解码需要同一棵 huffman 树**  -->  可以用于加密，而 huffman 树相当于 key

> [[译文\]5分钟系列—快速理解Huffman Coding(霍夫曼编码) - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/390459645)



如何对一份文件产生一棵最优的 huffman 编码树？



## huffman tree

-----

> [霍夫曼树 - OI Wiki (oi-wiki.org)](https://oi-wiki.org/ds/huffman-tree/)
>
> **最优二叉树**，WPL最小的二叉树



### 树的带权路径长度

$WPL$ : **带权叶子节点**的二叉树的**带权路径长度**

设 $v_i$ 是二叉树第 $i$ 个叶节点的权值，$l_i$ 是从根节点到第$i$个叶子节点的路径长度，有公式：
$$
WPL = \sum_{i=1}^n v_i l_i
$$

### 结构

由排序不等式，叶子节点的权值越小，距离根越远；权值越大，距离根越近。

对于 Huffman tree ，有且仅有叶子结点的度为0，其他节点的度均为2。



### Huffman 算法

霍夫曼算法用于构造一棵霍夫曼树，算法步骤如下：

> 1. **初始化**：由给定的 n 个权值构造 n 棵只有一个根节点的二叉树，得到一个二叉树集合 **F**(森林)。
> 2. **选取与合并**：从二叉树集合 **F** 中选取根节点权值 **最小的两棵** 二叉树分别作为左右子树构造一棵新的二叉树，这棵新二叉树的根节点的权值为其左、右子树根结点的权值和。
> 3. **删除与加入**：从 **F** 中删除作为左、右子树的两棵二叉树，并将新建立的二叉树加入到 **F** 中。
> 4. 重复 2、3 步，当集合中只剩下一棵二叉树时，这棵二叉树就是霍夫曼树。



### Huffman 编码



### 相关实现代码

#### 通过数组建立 Huffman树

朴素算法，时间复杂度为 $O(n^2)$

```cpp
typedef struct HNode {
  int weight;
  HNode *lchild, *rchild;
} * Htree;

Htree createHuffmanTree(int arr[], int n) {
  Htree forest[N];
  Htree root = NULL;
  for (int i = 0; i < n; i++) {  // 将所有点存入森林,初始化 F
    Htree temp;
    temp = (Htree)malloc(sizeof(HNode));
    temp->weight = arr[i];
    temp->lchild = temp->rchild = NULL;
    forest[i] = temp;
  }

  for (int i = 1; i < n; i++) {  // n-1 次循环建哈夫曼树
    int minn = -1, minnSub;  // minn 为最小值树根下标，minnsub 为次小值树根下标
    for (int j = 0; j < n; j++) {
      if (forest[j] != NULL && minn == -1) {
        minn = j;
        continue;
      }
      if (forest[j] != NULL) {
        minnSub = j;
        break;
      }
    }

    for (int j = minnSub; j < n; j++) {  // 根据 minn 与 minnSub 赋值
      if (forest[j] != NULL) {
        if (forest[j]->weight < forest[minn]->weight) {
          minnSub = minn;
          minn = j;
        } else if (forest[j]->weight < forest[minnSub]->weight) {
          minnSub = j;
        }
      }
    }

    // 建新树
    root = (Htree)malloc(sizeof(HNode));
    root->weight = forest[minn]->weight + forest[minnSub]->weight;
    root->lchild = forest[minn];
    root->rchild = forest[minnSub];

    forest[minn] = root;     // 指向新树的指针赋给 minn 位置
    forest[minnSub] = NULL;  // minnSub 位置为空
  }
  return root;
}
```



可以使用优先队列改进算法，时间复杂度为$O(nlog(n))$



#### 已有 Huffman树，求WPL

一个简单的递归即可实现，时间复杂度 $O(n)$

```cpp
typedef struct HNode {
  int weight;
  HNode *lchild, *rchild;
} * Htree;

int getWPL(Htree root, int len) {  // 递归实现，对于已经建好的霍夫曼树，求 WPL
  if (root == NULL)
    return 0;
  else {
    if (root->lchild == NULL && root->rchild == NULL)  // 叶节点
      return root->weight * len;
    else {
      int left = getWPL(root->lchild, len + 1);
      int right = getWPL(root->rchild, len + 1);
      return left + right;
    }
  }
}
```



#### 给定叶子节点的权值序列，直接求 WPL

想要证明这个的正确性，计算**每个节点被加的次数**即可。

```cpp
int getWPL2(int arr[], int n) {  // 对于未建好的霍夫曼树，直接求其 WPL
  priority_queue<int, vector<int>, greater<int>> huffman;  // 小根堆
  for (int i = 0; i < n; i++) huffman.push(arr[i]);

  int res = 0;
  for (int i = 0; i < n - 1; i++) {
    int x = huffman.top();
    huffman.pop();
    int y = huffman.top();
    huffman.pop();
    int temp = x + y;
    res += temp;
    huffman.push(temp);
  }
  return res;
}
```



#### 对于给定序列，计算 Huffman编码

```cpp
typedef struct HNode {
  int weight;
  HNode *lchild, *rchild;
} * Htree;

void huffmanCoding(Htree root, int len, int arr[]) {  // 计算霍夫曼编码
  if (root != NULL) {
    if (root->lchild == NULL && root->rchild == NULL) {
      printf("结点为 %d 的字符的编码为: ", root->weight);
      for (int i = 0; i < len; i++) printf("%d", arr[i]);
      printf("\n");
    } else {
      arr[len] = 0;
      huffmanCoding(root->lchild, len + 1, arr);
      arr[len] = 1;
      huffmanCoding(root->rchild, len + 1, arr);
    }
  }
}
```

