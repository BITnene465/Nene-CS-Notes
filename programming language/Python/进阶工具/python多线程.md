# python 多线程

## 多线程 与 异步

### 并行与并发

多线程可以实现**并发（Concurrency）**或**并行（Parallelism）**：

- **并发**适合 I/O 密集型任务；**并行**适合 CPU 密集型任务
- **并发**是指多个任务交替执行，通过时间片轮转在单核或多核处理器上实现。虽然任务看起来是同时进行的，但实际上是在快速切换
- **并行**是指多个任务真正同时执行，需要多核处理器



**从线程的角度**，线程总是认为自己一直在运行。每个线程在运行时，都会认为自己独占 CPU，直到被操作系统调度器中断并切换到其他线程。

**从开发者的角度**，利用多线程实现**并行**和**并发**从**代码角度上**几乎没有差别（但是一般并行更加复杂），但是由于多线程可以访问所在进程的所有资源，所以要使用锁机制（**掉头发**）



**异步（Async）**实现并发的一种技术

### 多线程并发 与 异步

**多线程并发**是通过创建多个线程来同时执行多个任务。每个线程独立运行，操作系统负责调度线程的执行。

- **线程是操作系统调度的基本单位**：
  - 每个线程有自己的栈、程序计数器和寄存器状态。
  - 线程之间共享进程的内存空间（如堆、全局变量等）。
- **并行或交替执行**：
  - 在多核 CPU 上，线程可以真正并行运行；在单核 CPU 上，线程通过时间片轮转交替执行。
- **线程切换开销**：
  - 线程切换需要保存和恢复上下文，开销较大。
- **线程安全问题**：
  - 多个线程共享资源时，可能引发竞态条件，需要使用锁、信号量等机制保证线程安全。



多线程运行中，如果一个子线程在运行时遇到阻塞操作（如 I/O 操作、锁等待、`time.sleep()` 等），**主线程不会被阻塞**。

```python
#! 子线程阻塞
import threading
import time

def task1():
    for _ in range(10):
        print("Task 1: Working")
        time.sleep(0.1)
    
def task2():
    for _ in range(10):
        print("Task 2: Working")
        input("Task 2: enter to continue")    # 只会阻塞当前线程，其他线程照常运行

if __name__ == "__main__":
    thread1 = threading.Thread(target=task1)
    thread2 = threading.Thread(target=task2)
    thread1.start()
    thread2.start()
    for _ in range(10):
        print("Main: Working")
        time.sleep(0.1)
    thread1.join()
    thread2.join()
    print("All tasks done")
```



---------

**异步编程**是通过**事件循环**和**非阻塞 I/O** 来实现并发。它通常使用**单线程**（或少量线程）来处理多个任务，任务之间通过协作式调度切换。

- **事件驱动**：
  - 异步编程基于事件循环，任务在等待 I/O 操作（如网络请求、文件读写）时主动让出控制权，事件循环会调度其他任务执行。
- **非阻塞**：
  - 异步任务不会阻塞主线程，适合 I/O 密集型任务。
- **轻量级**：
  - 异步任务通常是协程（coroutine），切换开销远小于线程切换。
- **无需锁机制**：
  - 由于是单线程运行，不存在多线程的竞态条件问题。



**异步编程**中，依靠程序员使用 `await` 语句来实现异步任务控制权交出的时机，如果没有 `await` 语句，则会一直运行下去（和同步程序一样），因此如果在运行异步任务时碰到了阻塞操作，那么会导致整个程序被阻塞（**所以我们的异步编程是建立在 非阻塞 I/O 操作下的**）。

```python
#! 协程阻塞
import asyncio

async def task1():
    for _ in range(10):
        print("Task 1: Working")
        await asyncio.sleep(0.5) 

async def task2():
    for _ in range(10):
        print("Task 2: Working")
        input("Task 2: Press Enter to continue\n")  # 运行到这就会阻塞整个事件循环
        

async def main():
    # 创建任务
    t1 = asyncio.create_task(task1())
    t2 = asyncio.create_task(task2())
    input("Press Enter to start the task\n")
    await asyncio.gather(t1, t2)

asyncio.run(main())
```







## threading 库