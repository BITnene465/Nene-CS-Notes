# Java 多线程基础

## 线程简介

### 多任务 

多任务 multi-task

### 进程 和 线程

进程 Process  &&  线程 Thread

- 在操作系统中运行的一个程序就是一个进程，例如: QQ,游戏,IDE ...

- 进程是程序的一次执行过程，是一个动态的概念。是系统资源分配的单位
- 通常在一个进程中可以包含若干个线程，一个进程中至少有一个线程，不然就没有存在的意义。线程是 CPU 调度和执行的单位

tips ： 很多多线程都是模拟出来的，真正的多线程是指有多个cpu，即多核，如服务器。如果是模拟出来的多线程，即在一个cpu的情况下，在同一个时间点，cpu只能执行一个代码，但是因为切换的很快，所以有同时执行的错觉



## 核心概念

- 线程就是独立的执行路径
- 在程序运行时，即使没有自己创建线程，后台也会有多个线程，如主线程，gc线程（java 自带的垃圾回收线程）
- main() 称之为主线程，为系统的入口，用于执行整个程序
- 在一个进程中，如果开辟了多个线程，线程的运行由调度器安排调度，调度器是与操作系统密切相关的，先后顺序是不能人为干预的
- 对于同一份资源操作时，会存在资源抢夺的问题，需要加入并发控制
- 线程会带来额外的开销，如 cpu调度时间，并发控制开销
- 每个线程都有自己的工作内容交互，内存控制不当会造成数据不一致



### 线程创建

三种方式：

- 继承 Thread 类
- 实现 Runnable 接口
- 实现 Callable 接口



#### 继承 Tread 类

1. 实现一个类继承 Tread 类
2. 重写 run() 方法
3. 调用 start() 开启线程

**run() 和 start() 的区别！**

![](F:\Note\面向科学问题的JAVA程设\img\是否并发？.png)



**踩坑：**

- Java中 在一个类的方法中调用另一个方法，采用的是第一种方式（这很符合我们平常写的代码的逻辑）（也即函数调用）
- java中 主线程可以先于子线程结束，直到所有线程结束，该进程才会结束
- 尤其注意 GUI 编程中，**创建一个新的窗口会创建一个新的线程**！

**一个多线程实例：**

```java
// 多线程运行的实例
// 并行运行时，会由CPU来调度，人为不可控
public class TestThread2 {
    public static void main(String[] args) {
        MyThread2 thread1 = new MyThread2("子线程1");
        MyThread2 thread2 = new MyThread2("子线程2");
        thread2.start();       // 子线程1 和 子线程2 并行运行
        thread1.run();  // 先运行完 子线程1 ，再回到 主线程 (就是方法调用)
        for (int i = 0; i < 1000; i++) {
            System.out.println("主线程 "+i);
        }
    }
}
class MyThread2 extends Thread{
    private String name = null;

    public MyThread2(String name) {
        this.name = name;
    }

    @Override
    public void run() {
        for (int i = 0; i < 1000; i++) {
            System.out.println(name+"  "+i);
        }
    }
}
```







目前到 p4
