# QML使用

> qml需要QT5或QT6的支持，使用很多QT特有关键字（宏定义）和语法规则

## 关于C++类在qml的注册

### 1. `qmlRegisterType`
`qmlRegisterType` 是最常见的将 C++ 类注册到 QML 的方法，允许在 QML 中创建该类的实例。

> <font size="6">**qmlRegisterType 函数的几个参数是什么意思？**</font>
>
> 
>
> `qmlRegisterType` 函数用于将 C++ 类注册到 QML 中，以便在 QML 中使用该类。这个函数的几个参数各自有特定的含义。以下是对参数的解释：
>
> ```cpp
> qmlRegisterType<Type>(const char *uri, int versionMajor, int versionMinor, const char *qmlName);
> ```
>
> ### 参数解释：
>
> 1. **`Type`**：
>    - **类型**：模板参数。
>    - **含义**：要注册的 C++ 类的类型。通过这个参数，QML 将能够实例化该类型的对象。
>
> 2. **`uri`**：
>    - **类型**：`const char *`
>    - **含义**：命名空间 URI（统一资源标识符）。用于在 QML 中标识该类所属的模块。一般情况下，可以使用类似 `"com.mycompany.doctor"` 这样的字符串。该 URI 应该在整个项目中唯一。
>
> 3. **`versionMajor`**：
>    - **类型**：`int`
>    - **含义**：该模块的主版本号。用于指定 QML 模块的版本管理。QML 文件可以通过 `import` 语句引入对应版本的模块。
>
> 4. **`versionMinor`**：
>    - **类型**：`int`
>    - **含义**：该模块的次版本号。和主版本号一起用于指定 QML 模块的版本管理。QML 文件可以通过 `import` 语句引入对应版本的模块。
>
> 5. **`qmlName`**：
>    - **类型**：`const char *`
>    - **含义**：在 QML 中使用的类名。这个名字是 QML 文件中引用该类时的名称。注册后的类在 QML 中可以用这个名字来创建实例。例如，如果定义了 `qmlName` 为 `"Doctor"`，那么在 QML 文件中可以通过 `Doctor {}` 创建实例。
>
> ### 示例：
>
> ```cpp
> qmlRegisterType<Doctor>("com.mycompany.doctor", 1, 0, "Doctor");
> ```
>
> - **Type**：`Doctor` 类（C++ 类名）。
> - **uri**：`"com.mycompany.doctor"`（命名空间 URI）。
> - **versionMajor**：`1`（主版本号）。
> - **versionMinor**：`0`（次版本号）。
> - **qmlName**：`"Doctor"`（在 QML 中的类名）。
>
> 在 QML 文件中，可以通过如下方式引入这个类型：
>
> ```qml
> import com.mycompany.doctor 1.0
> 
> Doctor {
>     // 在这里使用 Doctor 类的属性和方法
> }
> ```
>



#### 示例：

```cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "doctor.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // 注册 C++ 类到 QML 中
    qmlRegisterType<Doctor>("com.mycompany.doctor", 1, 0, "Doctor");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
```

#### 使用场景：

在 QML 中创建并使用该类的实例：

```qml
Doctor {
    // 使用 Doctor 的属性和方法
}
```

### 2. `qmlRegisterSingletonType`

这种方法用于将 C++ 类注册为 QML 单例（singleton），即在整个应用程序生命周期中只有一个实例。这在需要共享某个对象时非常有用。

#### 示例：

```cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "doctor.h"

// 创建单例实例的工厂函数
static QObject* doctorSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    Doctor *doctor = new Doctor();
    return doctor;
}

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // 注册单例类型到 QML
    qmlRegisterSingletonType<Doctor>("com.mycompany.doctor", 1, 0, "Doctor", doctorSingletonProvider);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
```

#### 使用场景：

在 QML 中使用单例对象时，例如：

```qml
Doctor.someFunction()
```

### 3. `setContextProperty`

`setContextProperty` 方法可以将现有的 C++ 对象直接暴露给 QML。这对于需要将应用程序中的特定实例直接绑定到 QML 时非常有用。

> 该方法是第一次编写QT程序使用的方法

#### 示例：

```cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "doctor.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Doctor doctor;  // 创建 C++ 类的实例

    // 将 C++ 对象绑定到 QML 上下文
    engine.rootContext()->setContextProperty("doctorInstance", &doctor);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
```

#### 使用场景：

在 QML 中通过 `doctorInstance` 访问 C++ 对象的属性和方法，例如：

```qml
doctorInstance.someFunction()
```

### 4. `qmlRegisterUncreatableType`

如果你希望将 C++ 类的类型暴露给 QML，但不希望 QML 直接创建该类的实例，可以使用 `qmlRegisterUncreatableType`。这对于暴露枚举类型或类的静态方法很有用。

#### 示例：

```cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "doctor.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // 注册 C++ 类型但不允许在 QML 中创建实例
    qmlRegisterUncreatableType<Doctor>("com.mycompany.doctor", 1, 0, "Doctor", "Doctor cannot be created in QML");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
```

#### 使用场景：

在 QML 中使用 C++ 类中的常量或枚举，例如：

```qml
console.log(Doctor.SomeEnumValue)
```

### 5. `qmlRegisterAnonymousType`

这种方法适用于不需要在 QML 中使用特定名称来引用类型，但需要暴露该类型的属性和信号槽。

#### 示例：

```cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "doctor.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // 注册匿名类型
    qmlRegisterAnonymousType<Doctor>("com.mycompany.doctor", 1);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
```

#### 使用场景：

在 QML 中使用注册的匿名类型，尤其是在组件中，例如：

```qml
Doctor {
    // 使用 Doctor 的属性和信号槽
}
```



## QML 与 C++ 交互流程

### 1. 将 C++ 类注册到 QML 中

在 QML 中使用 C++ 类之前，必须先将该类注册到 QML 类型系统中。这通常在 `main.cpp` （qml编写的前端的启动器）文件中完成。

#### `main.cpp`

```cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "doctor.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // 注册 C++ 类到 QML 中
    qmlRegisterType<Doctor>("com.mycompany.doctor", 1, 0, "Doctor");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
```

### 2. 在 C++ 类中声明 QML 可访问的字段和函数

要使 QML 访问 C++ 类中的字段和函数，需要使用 `Q_PROPERTY` 和 `Q_INVOKABLE` 进行声明。

#### ：`doctor.h`

```cpp
#include <QObject>
#include <QMap>

class Doctor : public QObject {
    Q_OBJECT
        // 创建一个qml中可读写有信号的字段 totMidMap 
    Q_PROPERTY(QMap<QString, int> totMidMap READ getTotMidMap WRITE setTotMidMap NOTIFY totMidMapChanged);  

public:
    QMap<QString, int> getTotMidMap() const {
        return totMidMap;
    }

    void setTotMidMap(const QMap<QString, int>& map) {
        if (totMidMap != map) {
            totMidMap = map;
            emit totMidMapChanged();
        }
    }

    Q_INVOKABLE void someFunction() {
        // 可从 QML 中调用的函数
    }

signals:
    void totMidMapChanged();

private:
    QMap<QString, int> totMidMap;
};
```

#### 说明

- `Q_PROPERTY` 用于将属性暴露给 QML，定义读取、写入方法和变更信号。
- `Q_INVOKABLE` 修饰符允许 QML 直接调用 C++ 函数。

### 3. 在 QML 中读写 C++ 类的字段

在 QML 中可以直接读取和修改通过 `Q_PROPERTY` 暴露的字段，同时可以调用 `Q_INVOKABLE` 函数。

#### 在 QML 中访问和修改 `totMidMap`

```qml
Rectangle {
    width: 400
    height: 400

    Doctor {
        id: doctor
    }

    // 初始化并修改 totMidMap
    Component.onCompleted: {
        if (!doctor.totMidMap.hasOwnProperty("patient1")) {
            var map = doctor.totMidMap;
            map["patient1"] = 0;
            doctor.totMidMap = map;
        }
    }

    // 调用 C++ 函数
    Button {
        text: "Call C++ Function"
        onClicked: {
            doctor.someFunction();
        }
    }
}
```

#### 说明

- `var map = doctor.totMidMap;` 会自动调用 `getTotMidMap()` 函数获取字段
- 同理当需要对 `totMidMap` 写入时，会自动调用 `setToMidMap()` 函数，而不需要显式调用
- 通过按钮点击调用 `someFunction()`，即 **Q_INVOKABLE** 函数。

### 4. 信号和槽机制

信号和槽机制用于在 C++ 类的属性变化时通知 QML，从而更新 UI。

#### 代码示例：信号和槽
```cpp
signals:
    void totMidMapChanged();
```

#### QML 中连接信号：

> <font size="6"> **该连接信号放在哪里？**</font>
>
> 
>
> `Connections` 对象应放置在需要响应信号的位置，通常是在需要与信号关联的对象或界面元素的作用范围内。它可以位于根对象、页面或特定控件中。
>
> #### 示例说明：
>
> ```
> qml复制代码Item {
>     width: 800
>     height: 600
> 
>     Doctor {
>         id: doctor
>     }
> 
>     // 使用 Connections 监听 doctor 对象的 totMidMapChanged 信号
>     Connections {
>         target: doctor
>         onTotMidMapChanged: {
>             console.log("totMidMap has changed");
>         }
>     }
> }
> ```
>
> ### 说明
>
> - `Connections` 的 `target` 属性指向要监听信号的对象（如 `doctor`）。
> - 当 `doctor` 对象的 `totMidMap` 发生变化时，会发出 `totMidMapChanged` 信号，QML 中的 `Connections` 组件的槽函数会响应并执行，例如打印一条消息。
>
> ### 关键点：
>
> 1. `Connections` 对象放置的位置可以根据逻辑需求来确定，一般放置在信号触发后的处理逻辑所需的界面部分。
> 2. 使用 `target` 属性指定需要监听的 C++ 对象，并将其信号与槽函数关联。
>
> 这样，当 C++ 对象的信号发出时，QML 中相应的函数就会被调用，从而实现信号与槽的通信。

```qml
Connections {
    target: doctor
    onTotMidMapChanged: {
        console.log("totMidMap has changed");
    }
}
```

#### 说明

- 当 `totMidMap` 发生变化时，`totMidMapChanged` 信号会被触发，QML 中的 `Connections` 对应的槽函数也会被执行。
