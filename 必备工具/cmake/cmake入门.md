# cmake 入门

## cmake 模板

最简单的多文件工程

```cmake
CMAKE_MINIMUM_REQUIRED(VERSION 3.17) # 设置最低的 cmake 版本

project(HELLO_WORLD VERSION 1.0.0) #　设置项目名和版本

# 设置 c++ 标准
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置输出的目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# 假如头文件和源文件
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

# 设置头文件目录，方便补全？
include_directories(include)

# 编译生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} main.cpp)
```

