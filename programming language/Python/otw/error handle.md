


# Python异常处理

## 异常处理基础

Python中的异常处理通过 `try/except` 语句块实现，捕获程序执行过程中发生的错误并采取适当措施。

```python
try:
    # 可能产生异常的代码
    result = operation()
except Exception as e:
    # 处理异常的代码
    print(f"发生错误: {e}")
```

## 常见的异常处理模式

### 1. 记录并继续（吞下异常）

```python
try:
    result = risky_operation()
except Exception as e:
    logger.error(f"操作失败: {e}")
    result = default_value  # 提供默认值或回退方案
```

**适用场景**：非关键操作，错误可接受且有合理默认行为

**缺点**：隐藏问题，可能导致难以调试的错误

### 2. 记录并重新抛出（简单转发）

```python
try:
    content = await api_client.request()
except Exception as e:
    logger.error(f"API请求失败: {e}")
    raise  # 不带参数的raise - 重新抛出当前异常
```

**适用场景**：
- 希望记录异常但由上层代码决定如何处理
- 保留完整的原始异常信息和堆栈跟踪

**优点**：
- 保留完整的原始异常信息
- 责任分离：当前层负责记录，上层决定处理方式
- 易于调试，错误传播透明

### 3. 异常转换（带链接）

```python
try:
    data = parse_json(text)
except JSONDecodeError as e:
    raise DataFormatError("数据格式无效") from e
```

**语法**：`raise NewException from original_exception`

**用途**：
- 提供更有意义的业务级异常
- 隐藏实现细节，但保留技术信息用于调试
- 异常分类和层次化

**工作原理**：
- 创建新异常
- 设置原始异常为新异常的`__cause__`属性
- 调试时可看到完整异常链

## 异常处理最佳实践

1. **具体优先于一般**：先捕获具体异常，再捕获一般异常
   ```python
   try:
       # 代码
   except ValueError as e:
       # 处理值错误
   except IOError as e:
       # 处理IO错误
   except Exception as e:
       # 处理其他所有异常
   ```

2. **避免空except**：总是指定要捕获的异常类型
   ```python
   # 不推荐
   try:
       data = process()
   except:  # 捕获所有异常，包括KeyboardInterrupt
       pass
   ```

3. **使用finally清理资源**：
   ```python
   try:
       file = open("data.txt")
       process_file(file)
   except IOError as e:
       logger.error(f"无法处理文件: {e}")
   finally:
       if 'file' in locals() and file:
           file.close()  # 无论是否发生异常都会执行
   ```

4. **使用上下文管理器**：
   ```python
   # 自动处理资源清理
   with open("data.txt") as file:
       process_file(file)
   ```

5. **仅捕获预期异常**：不要使用异常处理来控制正常流程

## 实际应用案例

从`LocalModelService`类的实现中提取的异常处理模式：

```python
async def process(self, text: str, session_id: str, **kwargs) -> str:
    """处理用户文本并返回AI响应"""
    if not self.is_ready():
        self.logger.error("LLM service not initialized")
        raise RuntimeError("LLM service not initialized")
    
    try:
        # 业务逻辑...
        response_content = await self._process_normal(model, messages, temperature, max_tokens, top_p)
        # 更新状态...
        return response_content
    except Exception as e:
        self.logger.error(f"Error calling API: {e}")
        # 注意：这里没有重新抛出异常，接口会返回None
        # 这可能是有意为之，防止错误影响上层应用
```

在内部方法中的处理：

```python
async def _process_normal(self, model: str, messages: List[Dict[str, str]], 
                         temperature: float, max_tokens: int, top_p: float) -> str:
    """非流式处理API请求"""
    try:
        content = await self.client.chat_completion(...)
        self.logger.info(f"Successfully got response: '{content[:50]}...'")
        return content
    except Exception as e:
        self.logger.error(f"Error in _process_normal: {e}")
        raise  # 重新抛出给process方法处理
```

通过这种分层异常处理，内部方法负责记录详细错误并重新抛出，而公共API方法决定是否向调用者暴露错误。