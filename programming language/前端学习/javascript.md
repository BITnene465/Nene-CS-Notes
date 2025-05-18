# JS

## 基础语法

### 字面量

- 数字 ， Number
- 字符串， String
- 表达式字面量
- 数组字面量， Array
- 对象字面量， Object
- 函数字面量， Function

```js
/* Number */
3.14
1001
123e5

/* String */
"John Doe"
'John Doe'

/* Expression */
5 + 6
5 * 10

/* Array */
[40, 100, 1, 5, 25, 10]

/* Object */
{firstName:"John", lastName:"Doe", age:50, eyeColor:"blue"}

/* Function */
function myFunction(a, b) { return a * b;}
```



### 变量

使用 `var` 关键字进行变量的声明， `=` 进行变量的赋值

```js
var x, length
x = 5
length = 6
```



- `Value = undefined`  ：变量在声明（**使用 var 关键字进行赋值**）后没有进行赋值

- 重新声明的 JavaScript 变量， 该变量的值不会丢失 (下面的例子中 carname 仍然为 Volvo)

  ```js
  var carname="Volvo";
  var carname;
  ```



在 2015 年后的 Js 版本（ES6） ，可以使用 `const` 定义 **常量**， 使用 `let` 定义限定范围内作用域的 **变量**





### 数据类型

> 基本类型（`number`、`string`、`boolean`、`null`、`undefined`、`symbol`）和引用类型（`object`、`array`、`function`）。
>
> <img src="G:\softwares\typora\typora 图片\javascript\image-20250130144626256.png" alt="image-20250130144626256" style="zoom: 80%;" />

JavaScript 是一个 **动态语言** （类似 python）

```js
var x;               // x 为 undefined
var x = 5;           // 现在 x 为数字
var x = "John";      // 现在 x 为字符串
```



变量的数据类型可以使用 `typeof` 操作符来查看

```js
typeof "John"                // 返回 string
typeof 3.14                  // 返回 number
typeof false                 // 返回 boolean
typeof [1,2,3,4]             // 返回 object
typeof {name:'John', age:34} // 返回 object
```



Undefined 这个值表示变量不含有值；可以通过将变量的值设置为 null 来 **清空变量**。

```js
cars=null;
person=null;
```



如何 **声明变量类型**？   在创建变量的时候可以使用 `new` 来声明其类型。

```js
var carname=new String;
var x=      new Number;
var y=      new Boolean;
var cars=   new Array;
var person= new Object;
```



> **JavaScript  变量均为对象**，当我创建一个变量时，就创建了一个对象。



### 运算符

大部分运算符和 C 语言一致，主要介绍和 C 语言不一样的地方



####  严格相等与不相等：`===` 和 `!==`

javascript 中的 `==` 有点宽松了，不会检查类型

**作用**：

- `===`：检查值和类型是否完全相同。
- `!==`：检查值或类型是否不同。

```js
console.log(5 == "5");  // true（值相等，类型不同）
console.log(5 === "5"); // false（类型不同）
console.log(5 !== "5"); // true（类型不同）
```



#### 空值合并运算符：`??`

**作用**：

- 检查值是否为 `null` 或 `undefined`，如果是，则返回默认值。
- 与 `||` 的区别：`||` 会检查所有假值（如 `0`、`""`、`false`），而 `??` 只检查 `null` 和 `undefined`。

```js
let a = null;
let b = a ?? "默认值";
console.log(b); // 输出 "默认值"

let c = 0;
let d = c || "默认值"; // 0 是假值，会被替换
let e = c ?? "默认值"; // 0 不是 null 或 undefined，不会被替换
console.log(d); // 输出 "默认值"
console.log(e); // 输出 0
```



#### 可选链运算符：`?.`

**作用**：

- 安全访问嵌套对象的属性，避免因属性不存在而报错。
- 如果某个属性不存在，则返回 `undefined`，而不会抛出错误。

```js
let obj = { name: "Alice" };
console.log(obj.age?.toString()); // 输出 undefined，不会报错

let arr = [1, 2, 3];
console.log(arr[5]?.toString()); // 输出 undefined，不会报错
```



#### 类型检查：`typeof` 和 `instanceof`

这两个 python 中也有相应的关键字

1. `typeof`

   - 返回变量类型，结果是一个 String

   - specially， `typeof null` 会返回 `"object"` 是历史遗留问题

     ```js
     console.log(typeof 42);         // 输出 "number"
     console.log(typeof "hello");    // 输出 "string"
     console.log(typeof true);       // 输出 "boolean"
     console.log(typeof undefined);  // 输出 "undefined"
     console.log(typeof null);       // 输出 "object"
     ```

     

2. `instanceof`

   - 检查某个对象是否为某个类的实例

     ```js
     let arr = [1, 2, 3];
     console.log(arr instanceof Array); // 输出 true
     console.log(arr instanceof Object); // 输出 true（数组也是对象）
     ```





#### 其他独特运算符：`in`、`delete`、`void`、`new`、`yield`

`in` 用于判断是否是对象中的属性; `delete` 用于删除对象中的属性

```js
let obj = {name: "Alice", age: 20};
console.log("name" in obj); // 输出 true
console.log("gender" in obj);  // 输出 false

delete obj.age;
console.log(obj);   // 输出 {name: "Alice"}
```



`void` 

- 执行表达式并返回 `undefined`
- 常用于阻止默认行为（如 `<a>` 标签的跳转）

```js
console.log(void 0); // 输出 undefined
```



`new` 

- 创建对象的实例

```js
function Person(name) {
  this.name = name;
}
let p = new Person("Alice");
console.log(p.name); // 输出 "Alice"
```



`yeild` 用于生成器函数中，暂停函数执行并且返回一个值 （这在 python 中亦有记载）



```js
function* generator() {
  yield 1;
  yield 2;
}
let gen = generator();
console.log(gen.next().value); // 输出 1
console.log(gen.next().value); // 输出 2
```





### 控制结构

**循环语句：**  for, while, do while

**条件语句：** if, else if, else, swicth

**跳转语句：** break, continue, return

**与 C 语言的使用方法一模一样**



**specially,** 

- `for...in` 循环

  ```js
  // 遍历对象的可枚举属性
  let obj = { name: "Alice", age: 20 };
  for (let key in obj) {
    console.log(key + ": " + obj[key]); // 输出 name: Alice, age: 20
  }
  ```

  

- `for...of` 循环 

  ```js
  // 遍历可迭代对象
  let arr = [1, 2, 3];
  for (let value of arr) {
    console.log(value); // 输出 1, 2, 3
  }
  ```

  

### JavaScript 作用域*

> 关于变量**作用域**：
>
> - 函数作用域（局部变量） 
> - 全局作用域（全局变量）
>
> 关于变量的**生命周期**：
>
> - 局部变量在函数执行完毕后销毁
> - 全局变量在页面关闭后销毁

**局部变量(函数作用域)**

```js
// 此处不能调用 carName 变量
function myFunction() {
    var carName = "Volvo";
    // 函数内可调用 carName 变量
}
```



**全局变量**

```js
var carName = " Volvo";
// 此处可调用 carName 变量
function myFunction() {
    // 函数内可调用 carName 变量
}
```





在函数内不声明直接用也是**全局变量**，不过函数外面不可见，所以要使用 `window.carname` 来调用

```js
// 此处可调用 carName 变量， 但要使用 window.carname 
 
function myFunction() {
    carName = "Volvo";
    // 此处可调用 carName 变量
}
```







### others

- **注释：** 同 C 语言， 可以使用 `\\` 和 `\*  *\`
- **字符集：** 采用 Unicode 字符集
- JavaScript 是大小写敏感的
- JavaScript 代码每一句用分号结束是 **可选的**





## JavaScript 对象



### 对象定义

```js
var person = {
    firstName:"John",
    lastName:"Doe",
    age:50,
    eyeColor:"blue"
};
```



### 对象属性

JavaScript 对象是变量的容器，这之中的键值对一般被称为 **对象属性**

**如何访问属性？**

```js
person.lastname  
person["lastname"]   // js 特有，当字典用了
```



### 对象方法

对象的方法定义了一个函数，并作为对象的属性存储。

**如何访问？**

```js
name = person.fullname()    // 访问 fullname 方法
str = person.fullname     // 作为定义函数的字符串返回 
```



**如何创建？**

在声明对象时，添加 `methodName : function() { 函数体 }` 以声明对象方法

```js
var person = {
    firstName: "John",
    lastName : "Doe",
    id : 5566,
    fullName : function() 
	{
       return this.firstName + " " + this.lastName;
    }
};
```



## JavaScript 函数

> 和 C 语言函数基本一致，没有默认参数（ES6 后支持默认参数），参数传递必须按照顺序。但是有一些特殊的语法。

### 函数声明与定义

声明语法： (可以函数提升 hoisting)

 `function funcName(arg1, arg2, ...) { \\执行代码 }`

函数表达式也可以存储在变量中：（不能函数提升）

```js
var x = function (a, b) {return a * b};
var z = x(4, 3);
```



也可以用 `Function()` 构造器来定义函数： (不太会用)

```js
var myFunction = new Function("a", "b", "return a*b")
var x = myFunction(3, 4)
```



### 自调用函数

```js
(function () {
    var x = "Hello!!";      // 我将调用自己
})();
```



这是一个**匿名自调用函数**：

- 添加括号，来说明这是一个函数表达式
- 表达式后面紧跟 `()` ，该函数会自动调用
- 不可以自调用**声明的函数**



### 箭头函数 (ES6)

```js
(参数1, 参数2, …, 参数N) => { 函数声明 }

(参数1, 参数2, …, 参数N) => 表达式(单一)
// 相当于：(参数1, 参数2, …, 参数N) =>{ return 表达式; }

// 只有一个参数时，圆括号可选
(单一参数) => {函数声明}
单一参数 => {函数声明}
// 没有参数的函数应该写成一对圆括号
() => {函数声明}
```



**使用实例：** `const x = (x, y) => {return x * y};` 或 `const x = (x, y) => x * y;` 

- 有的箭头函数都没有自己的 **this**。 不适合定义一个 **对象的方法**。
- 当我们使用箭头函数的时候，箭头函数会默认帮我们绑定外层 this 的值，所以在箭头函数中 this 的值和外层的 this 是一样的。
- 箭头函数是不能提升的，所以需要在使用之前定义。
- 使用 **const** 比使用 **var** 更安全，因为函数表达式始终是一个常量。



### Js 函数参数传递

显式参数

隐式参数



### Js 函数调用





### Js 闭包

闭包是一种保护私有变量的机制，它在函数执行时创建一个私有作用域，从而保护内部的私有变量不受外界干扰。

直观地说，闭包就像是一个不会被销毁的栈环境。

**以下为一个关于计数器的实例：**

```js
var add = (function () {
    var counter = 0;
    return function () {return counter += 1;}
})();
 
add();
add();
add();
// 计数器为 3
```



- 变量 **add** 指定了函数自我调用的返回字值。
- 自我调用函数只执行一次。设置计数器为 0。并返回函数表达式。
- add变量可以作为一个函数使用。非常棒的部分是它可以访问函数上一层作用域的计数器。
- 这个叫作 JavaScript **闭包。**它使得函数拥有私有变量变成可能。
- 计数器受匿名函数的作用域保护，只能通过 add 方法修改。







## Js 事件 (略)



下面是一些常见的HTML事件的列表:

| 事件        | 描述                                 |
| :---------- | :----------------------------------- |
| onchange    | HTML 元素改变                        |
| onclick     | 用户点击 HTML 元素                   |
| onmouseover | 鼠标指针移动到指定的元素上时发生     |
| onmouseout  | 用户从一个 HTML 元素上移开鼠标时发生 |
| onkeydown   | 用户按下键盘按键                     |
| onload      | 浏览器已完成页面的加载               |

[HTML DOM 事件对象 | 菜鸟教程](https://www.runoob.com/jsref/dom-obj-event.html)





## JS内置数据类型的使用方法*



### 字符串（String）

