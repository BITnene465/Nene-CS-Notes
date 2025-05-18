# HTML

> [HTML 速查列表 | 菜鸟教程](https://www.runoob.com/html/html-quicklist.html)
>
> [HTML 全局属性 | 菜鸟教程](https://www.runoob.com/tags/ref-standardattributes.html)
>



## HTML basic



### 元素

标签一般**使用小写**，不建议使用大写（虽然 HTML5 不区分大小写）

**一般元素**有开始标签和结束标签，如：

```html
<p> 段落内容 </p>
<a href="https://www.runoob.com/html/html-basic.html">这是一个链接</a>
```



**空元素**，不包含内容，最后使用 `/`  表示空元素的闭合（不使用也没有问题）：

```html
<br />    <!-- 这是一个换行符 -->
<br> 
```





### 属性

**HTML 属性**：

- HTML 元素可以设置**属性**
- 属性可以在元素中添加**附加信息**
- 属性一般描述于**开始标签**
- 属性总是以名称/值对的形式出现，**比如：name="value"**



**tips：**

- 属性值应该始终被包括在引号内；双引号是最常用的，不过使用单引号也没有问题。
- 如果属性值内包含双引号，则外层用单引号
- 属性值一般**小写**（大小写不区分）





## HTML 组成

### 标题

诸如：(一共有 6 级标题)

```html
<h1></h1>
<h2></h2>
<h3></h3>
<hr />    <!-- 这是一条水平线 -->
```



### 段落

主要是 `<p> </p>` 和 `<br />`

注意，可以在段内换行： `<p> <br/> </p>`



###  格式化文本

在这里查表格即可: [HTML 文本格式化 | 菜鸟教程](https://www.runoob.com/html/html-formatting.html)



### 链接

使用标签 `<a> </a>`， 表示一个 anchor，作为网页之间跳转的核心部分。

**关于属性：**

1.  href ： 定义链接目标

2. target: 定义链接的打开方式

   - _blank:   在新窗口或新标签页中打开链接
   - _self:  在当前窗口或标签页中打开链接（默认方式）
   - _parent:  在父框架中打开链接
   - _top:  在整个窗口中打开链接，取消任何框架

3. rel： 定义链接与目标页面的关系

4. download：提示浏览器下载链接目标而不是导航到该目标

5. title： 定义链接的额外信息， 当鼠标悬停在链接上时显示的提示

6. id： 用于链接锚点，通常在同一页面中跳转到某个特定位置

   ```html
   <!-- 链接到页面中的某个部分 -->
   <a href="#section1">跳转到第1部分</a>
   <div id="section1">这是第1部分</div>
   ```

> 参考: [HTML 链接 | 菜鸟教程](https://www.runoob.com/html/html-links.html)



### 头部

头部标签： `<head> </head>`

`<head>` 元素包含了所有的头部标签元素。在 `<head>`元素中你可以插入脚本（scripts）, 样式文件（CSS），及各种meta信息。

可以添加在头部区域的元素标签为: `<title>`, `<style>`, `<meta>`, `<link>`, `<script>`, `<noscript>` 和 `<base>`。



[HTML 头部 | 菜鸟教程](https://www.runoob.com/html/html-head.html)





### 表格

```html
<table border='1'>
  <thead>
    <tr>
      <th>列标题1</th>
      <th>列标题2</th>
      <th>列标题3</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>行1，列1</td>
      <td>行1，列2</td>
      <td>行1，列3</td>
    </tr>
    <tr>
      <td>行2，列1</td>
      <td>行2，列2</td>
      <td>行2，列3</td>
    </tr>
  </tbody>
</table>
```



<table border="2">
  <thead>
    <tr>
      <th>列标题1</th>
      <th>列标题2</th>
      <th>列标题3</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>行1，列1</td>
      <td>行1，列2</td>
      <td>行1，列3</td>
    </tr>
    <tr>
      <td>行2，列1</td>
      <td>行2，列2</td>
      <td>行2，列3</td>
    </tr>
  </tbody>
</table>




### 列表

```html
<!-- 无序列表 -->
<ul>
    <li> 你好 </li>
    <li> 世界 </li>
</ul>


<!-- 有序列表 -->
<ol>
    <li> 你好 </li>
    <li> 世界 </li>
</ol>
```

<ul>
    <li> 你好 </li>
    <li> 世界 </li>
</ul>

<ol>
    <li> 你好 </li>
    <li> 世界 </li>
</ol>







### 区块（*）

通过 `<div>` `<span>` 将各个 HTML 元素组合起来

- `<div>` 是**块级元素**。如果与 CSS 一同使用，`<div>` 元素可用于对大的内容块设置样式属性。是文档布局的主力元素。
- `<span>` 是**内联元素**。当与 CSS 一同使用时，`<span>` 元素可用于为部分文本设置样式属性。





### 表单 (*)

```html
<form action="/" method="post">
    <!-- 文本输入框 -->
    <label for="name">用户名:</label>
    <input type="text" id="name" name="name" required>

    <br>

    <!-- 密码输入框 -->
    <label for="password">密码:</label>
    <input type="password" id="password" name="password" required>

    <br>

    <!-- 单选按钮 -->
    <label>性别:</label>
    <input type="radio" id="male" name="gender" value="male" checked>
    <label for="male">男</label>
    <input type="radio" id="female" name="gender" value="female">
    <label for="female">女</label>

    <br>

    <!-- 复选框 -->
    <input type="checkbox" id="subscribe" name="subscribe" checked>
    <label for="subscribe">订阅推送信息</label>

    <br>

    <!-- 下拉列表 -->
    <label for="country">国家:</label>
    <select id="country" name="country">
        <option value="cn">CN</option>
        <option value="usa">USA</option>
        <option value="uk">UK</option>
    </select>

    <br>

    <!-- 提交按钮 -->
    <input type="submit" value="提交">
</form>
```



![image-20250126232833875](G:\softwares\typora\typora 图片\html\image-20250126232833875-17379053208351.png)
