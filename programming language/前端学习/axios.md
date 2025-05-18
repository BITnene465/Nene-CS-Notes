# Axios

## 安装与开始使用

安装：

```shell
npm install axios
```



使用须知：

- 在原生 js 中，需要设置为 module 的 js 脚本才能够使用 import 语法

```html
<script type="module" src="./script.js" defer></script>  
<!-- 加上 type='module' 才可以在js脚本里面引入其他模块-->`
```



- 引入 axios 

```js
import axios from 'axios';
```



## 使用范式

### 范式1

一个和后端通过 http 协议沟通的简单方案：

```js
const response = await axios({
            url: 'http://127.0.0.1:10001/semantic_seg',
            method: 'POST',   // http 请求的方式
            data: formData,
            headers: {
                'Content-Type': 'multipart/form-data',  // 说明发送的数据类型
            },
            responseType: 'blob',  // 指定响应类型
        });
```









