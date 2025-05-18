# python 面向对象



## 前面的基础知识

### 创建一个类并且实例化

```python
class Point():
    def __init__(self,x=0,y=0) -> None:
        self.x=x
        self.y=y
    def get_x(self):
        return self.x
    def get_y(self):
        return self.y
def main():
    p=Point(1,2)
    print("({},{})".format(p.get_x(),p.get_y()),end='')
main()
```
### 类的结构

- 一个类
    - 类属性  
        - 共有属性
        - 私有属性
    - 实例方法   
    - 静态方法  用`@staticmethod`修饰
    - 类方法   用`@classmethod`修饰



### 几种类型的方法

对于几种类型的方法，**一个程序的举例**

```python
class undergraduate:
    name = "Unknown"
    score = 0
    grade = 0
    def __init__(self,name,score,grade):
        self.name = name
        self.score = score
        self.grade = grade

    # 声明为静态方法，没有实例化也可以调用
    @staticmethod
    def show():
        print("meaningless static method")
    # 声明为类方法，可以对模板类的参数调用
    @classmethod
    def printDefault(cls):
        print("name:",cls.name)
        print("score:",cls.score)
        print("grade:",cls.grade)
    # 没有声明就是实例方法
    def printInfo(self):
        print("name: {}\nscore {}\ngrade: {}\n".format(self.name,self.score,self.grade))

def main():
    stu1 = undergraduate("TanJingyuan",100,2)
    undergraduate.show()
    undergraduate.printDefault()
    stu1.printInfo()
if __name__ == '__main__':
    main()
```



### 动态绑定

1. 动态绑定方法

实例对象可以动态绑定属性

沿用上面的 undergraduate 类，可以为 stu1 动态绑定一个属性 gender ，只有这个对象可以访问这个属性（有点像字典，底层实现是指针）

```python
stu1.gender = "male"
```



2. 动态绑定方法

沿用上面的类模板

```python
# 此处在类外
def method_test():
    pass
stu.method_test()  # 这样声明后，只有这个对象可以调用这个方法
```



### 关于属性

``__`` 双下划线开头的变量或方法只能在类的内部调用，即 **private**  不希望该属性在类的外部使用



其余变量和方法可以在外部调用，即 **public**  属性可以在类的外部使用





## object 类 --- python中所有类的父类

### 自带方法 & 自带属性



```python
print(dir(object))

'''
['__class__',
 '__delattr__',
 '__dir__',
 '__doc__',
 '__eq__',
 '__format__',
 '__ge__',
 '__getattribute__',
 '__getstate__',
 '__gt__',
 '__hash__',
 '__init__',
 '__init_subclass__',
 '__le__',
 '__lt__',
 '__ne__',
 '__new__',
 '__reduce__',
 '__reduce_ex__',
 '__repr__',
 '__setattr__',
 '__sizeof__',
 '__str__',    
 '__subclasshook__']
'''
```

| 常用的特殊属性   | 描述                                |
| ---------------- | ----------------------------------- |
| `__dict__`       | 实例或类模板的属性字典              |
| `__mro__`        | 类的层次结构                        |
| `__bases__`      | 类的父类们，返回元组                |
| `__base__`       | 最近的父类                          |
| `__subclasses__` | 类的所有子类，返回列表              |
| `__doc__`        | 类的说明字符串，就是class下面的注释 |
| `__class__`      | 对象所属的类！！                    |



**常用的特殊方法：**

- 关于实例化对象：

    - `__new__` 创建方法（类方法），在实例化对象的时候调用

    - `__init__` 构造方法（实例方法），在初始化对象的时候调用

    - > `stu1 = Student()` 之后
        >
        > 先调用类方法 `__new__` 申请一个实例的空间
        >
        > 在调用实例方法 `__init__` 将该对象初始化属性和方法

- `__setitem__` 按照索引赋值
- `__getitem__` 按照索引获取值
- `__repr__` 打印，转换
- `__len__` 获得长度（实例方法），在调用 `len()` 函数的时候会返回这个方法的返回值
- `__del__` 析构函数（实例方法），使用 `del` 释放对象时调用
- `__str__` 返回一个描述的字符串（实例方法），在打印该对象的时候会打印这个字符串 比如使用 `print` 函数
- `__call__` 函数调用
- 运算方法：
    - `__add__` 加法运算：对于 `+` 调用
    - `__sub__` 减法： 对于 `-` 调用
    - `__mul__`  乘法 multiply ： 对于 `*` 调用
    - `__truediv__` 除法 ： 对于 `/` 调用
    - `__mod__` 求余运算： `%` 调用
    - `__pow__` 乘方运算： `**` 调用
    - `__cmp__` 比较运算： 



## 类的浅拷贝和深拷贝 & 变量赋值

**一个实例：**

```python
import copy
class Cpu(object):
    pass
class Disk(object):
    pass
class Computer(object):
    def __init__(self, cpu: Cpu, disk :Disk) -> None:
        self.cpu = cpu
        self.disk = disk

cpu = Cpu()
disk = Disk()
computer = Computer(cpu, disk)
computer1 = computer
computer2 = copy.copy(computer)
computer3 = copy.deepcopy(computer)
print("computer:", id(computer))
print("cpu:", id(computer.cpu))
print("disk:", id(computer.disk))
print("computer1:", id(computer1))
print("cpu:", id(computer1.cpu))
print("disk:", id(computer1.disk))
print("computer2:", id(computer2))
print("cpu:", id(computer2.cpu))
print("disk:", id(computer2.disk))
print("computer3:", id(computer3))
print("cpu:", id(computer3.cpu))
print("disk:", id(computer3.disk))
```

**输出结果为：**

```shell
computer: 2017853413776
cpu: 2017853413648
disk: 2017853413712
computer1: 2017853413776
cpu: 2017853413648
disk: 2017853413712
computer2: 2017850848144
cpu: 2017853413648
disk: 2017853413712
computer3: 2017851214032
cpu: 2017851998800
disk: 2017851213008
```

所以有如下理解（不保真）：

- **实例变量赋值，类似于引用赋值**
- **浅拷贝**，类似于新建一个指针，并且把这个实例指针指向原对象
- **深拷贝**，类似于新申请一块内存，内容全部拷贝，生成一个全新的对象



### 浅拷贝

- python 中的拷贝一般都是浅拷贝，拷贝时，对象包含的子对象内容不拷贝，因此，源对象和拷贝对象会使用同一块内存
- 浅拷贝类似与 C++ 的新建指针并且赋值
- 使用 `copy.copy()` 进行浅拷贝



### 深拷贝

- 递归拷贝对象中包含的子对象，源对象和拷贝对象所有的子对象也不相同
- 使用 `copy.deepcopy()` 进行拷贝



## 封装

**通过定义公有、私有属性、方法来实现封装**

硬要访问私有属性也可以，如获取属性方法列表可以使用 `dir()` 函数

```python
print(dir(class1))
```



## 多态

> 简单而言，多态就是“具有多种形态”，他指的是：即便不知道一个变量所引用的对象到底是什么类型，仍然可以通过这个变量调用方法，在运行过程中根据变量所引用对象的类型，动态决定调用哪个对象中的方法。

一个程序实例

```python
class Animal(object):
    def eat(self):
        print("animal eat ...")
class Dog(Animal):
    def eat(self):
        print("dog eat bonds")
class Cat(Animal):
    def eat(self):
        print("Cat eat fishes")
class DC(Dog,Cat):
    pass
class CD(Cat,Dog):
    pass
def func(obj):
    obj.eat()

func(Animal())
func(Dog())
func(Cat())
func(DC())
func(CD())
```

输出为：

```shell
animal eat ...
dog eat bonds
Cat eat fishes
dog eat bonds
Cat eat fishes
```



**调用方法的规则**

查看此类中是否有该方法，如果没有就向其父类中寻找，并且在同一辈的父类中查找的顺序和继承的顺序有关



## 继承



### 单继承

单继承就如字面意思，很好理解

继承所有属性和方法（未知？）

```python
class Person():
    # 定义基础属性
    name = ''
    age = 0
    # 定义私有属性，外部无法访问
    __height = 0
    def __init__(self,n='姓名未知',a=0,h=0) -> None:
        self.name = n
        self.age = a
        self.__height = h
    def intro(self):
        print("my name is %s, %d years old" % (self.name,self.age))
class Student(Person):
    # 单继承Person类
    # 一部分属性已经不用再声明了
    grade = 0
    def __init__(self, n='姓名未知', a=0,h=0,g=0) -> None:
        Person.__init__(self, n, a, h)   # 调用Person类的初始化
        self.grade = g
    def intro(self):     # 重写方法
        print("my name is %s, %d years old, %d grades" % (self.name,self.age,self.grade))
s1 = Student("TJY",19,176,14)
s1.intro()
```

更加推荐使用 `super()` 函数，注意：不需要 `self` 参数

```python
class Person(object):
    def __init__(self,name,age,gender):
        self.name = name
        self.age = age
        self.gender = gender
    def info(self):
        print(self.name,self.age)
class Student(Person):
    def __init__(self,name,age,gender,grade):
        super().__init__(name,age,gender)
        self.grade = grade
    def info(self):
        super().info()   # 调用父类方法
        print(self.grade)
def main():
    stu1 = Student("TJY",18,'male',2)
    stu1.info()
if __name__ == '__main__':
    main()
```





### 多继承

**这是一个好东西**，python支持，但是java就不支持（

形如：
```python
class DerivedClassName(Base1, Base2, Base3):
    <statement-1>
    .
    .
    .
    <statement-N>
```

**tips：** 

- 圆括号中父类的顺序，若是父类中有相同的方法名，而在子类使用时未指定，python从左至右搜索 
    即方法在子类中未找到时，从左到右查找父类中是否包含方法。

- 使用 `super()` 函数来调用父类函数是最稳妥的



### 方法重写（继承的精髓）

`alt + insert` 在 PyCharm 中查看提示，重写方法或构造方法
