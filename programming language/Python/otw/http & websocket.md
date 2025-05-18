# Python 异步网络通信：aiohttp 与 websockets 库

## 1. 核心概念对比

| 特性         | aiohttp                           | websockets        |
| ------------ | --------------------------------- | ----------------- |
| **协议**     | HTTP/HTTPS                        | WebSocket         |
| **连接模式** | 短连接，请求-响应                 | 长连接，全双工    |
| **通信模式** | 同步请求-响应                     | 异步双向消息      |
| **用途**     | REST API 调用、HTTP 服务          | 实时通信、事件流  |
| **数据格式** | 支持多种格式，需指定 Content-Type | 文本/二进制数据帧 |
| **状态维护** | 通过 cookies、会话管理            | 通过持久连接      |

## 2. aiohttp 详解

### 2.1 核心组件

**ClientSession**: aiohttp 的核心类，提供 HTTP 客户端功能

```python
self.session = aiohttp.ClientSession()
```

- **作用**：管理 HTTP 连接、维护 cookies、处理请求头
- **生命周期**：需要显式关闭以释放资源
- **连接池**：自动管理底层连接池，复用连接提高效率

### 2.2 请求发送

```python
async with self.session.post(url, json=data, headers=headers) as response:
    result = await response.json()
```

- **HTTP 方法**：支持 get、post、put、delete 等所有 HTTP 方法
- **参数传递**：
  - `json`: 自动序列化并设置 Content-Type: application/json
  - `headers`: 请求头，包含认证信息等
  - `params`: URL 查询参数
  - `data`: 表单数据或原始数据
- **响应处理**：
  - `response.status`: HTTP 状态码
  - `response.json()`: 解析 JSON 响应
  - `response.text()`: 获取文本响应
  - `response.read()`: 获取原始字节数据

### 2.3 异常处理

```python
try:
    async with self.session.post(url, json=data) as response:
        if response.status != 200:
            raise Exception(f"Error {response.status}: {await response.text()}")
        result = await response.json()
except aiohttp.ClientError as e:
    # 网络错误处理
except Exception as e:
    # 其他错误处理
```

### 2.4 实战案例：LLM API 客户端

```python
class NewroLLMClient:
    def __init__(self, api_base_url, api_key=None):
        self.api_base_url = api_base_url
        self.api_key = api_key
        self.session = aiohttp.ClientSession()
    
    async def chat_completion(self, messages, model, temperature, max_tokens, top_p):
        url = f"{self.api_base_url}/chat/completions"
        headers = {
            "Content-Type": "application/json",
            "Authorization": f"Bearer {self.api_key}" if self.api_key else ""
        }
        data = {
            "model": model,
            "messages": messages,
            "temperature": temperature,
            "max_tokens": max_tokens,
            "top_p": top_p
        }
        
        async with self.session.post(url, json=data, headers=headers) as response:
            if response.status != 200:
                raise Exception(f"Error {response.status}: {await response.text()}")
            result = await response.json()
            return result.get("generated_text", "")
    
    async def close(self):
        await self.session.close()
        self.session = None
```

## 3. websockets 详解

### 3.1 核心组件

**WebSocketServerProtocol**: 服务器端 WebSocket 连接

```python
async def handler(self, websocket: WebSocketServerProtocol):
    # 处理 WebSocket 连接
```

- **作用**：代表单个 WebSocket 连接
- **生命周期**：连接建立到关闭的整个过程
- **事件驱动**：基于异步迭代器接收消息

### 3.2 消息处理

```python
async for message_str in websocket:
    # 处理接收到的消息
    await websocket.send(response_message)
```

- **接收消息**：使用 `async for` 迭代器模式
- **发送消息**：使用 `await websocket.send(message)`
- **消息类型**：文本串或二进制数据

### 3.3 连接管理

```python
self.server = await websockets.serve(
    self.handler,
    self.host,
    self.port,
    ping_interval=60,
    ping_timeout=60,
    max_size=50 * 1024 * 1024,
)
```

- **服务配置**：host、port、处理函数
- **心跳机制**：ping_interval 和 ping_timeout
- **消息大小**：max_size 限制单条消息大小
- **异常处理**：处理连接关闭和错误

### 3.4 实战案例：WebSocket 服务器

```python
class WebSocketServer:
    def __init__(self, host, port, broker):
        self.host = host
        self.port = port
        self.broker = broker
        self.server = None

    async def handler(self, websocket):
        try:
            # 发送欢迎消息
            await websocket.send(create_message(MessageType.SYSTEM_STATUS, 
                                {"message": "Connected to server"}))
            
            # 消息循环
            async for message_str in websocket:
                if not isinstance(message_str, str):
                    continue
                await self.broker.handle_message(websocket, message_str)
        except ConnectionClosed:
            pass
        finally:
            self.broker.unregister_connection(websocket)

    async def start(self):
        self.server = await websockets.serve(
            self.handler,
            self.host,
            self.port,
            max_size=50 * 1024 * 1024,
        )
```

## 4. 两种协议的应用场景与最佳实践

### 4.1 HTTP (aiohttp) 适用场景

- **REST API 交互**：与后端服务交互
- **资源获取**：下载文件、获取数据
- **无状态请求**：不需要持久连接的通信
- **服务探活**：健康检查、API 状态监控

### 4.2 WebSocket (websockets) 适用场景

- **实时通信**：聊天应用、实时通知
- **流式响应**：语音合成、大型文本生成
- **双向数据流**：游戏、协作编辑
- **事件订阅**：监听服务端事件

### 4.3 消息格式与数据传输

#### HTTP 中的数据传输

```python
# 请求格式
headers = {"Content-Type": "application/json", "Authorization": "Bearer token"}
data = {"key": "value"}

# 发送
async with session.post(url, json=data, headers=headers) as response:
    result = await response.json()
```

#### WebSocket 中的数据传输

```python
# JSON 字符串传输
message = json.dumps({
    "type": "TEXT_INPUT",
    "payload": {"text": "用户输入", "session_id": "123"},
    "request_id": "abc123"
})
await websocket.send(message)

# 接收与解析
async for message_str in websocket:
    data = json.loads(message_str)
    message_type = data.get("type")
    payload = data.get("payload")
```

### 4.4 处理大型消息

#### HTTP 大型响应处理

```python
async with session.get(url, stream=True) as response:
    # 分块读取
    with open(file_path, 'wb') as f:
        async for chunk in response.content.iter_chunked(1024):
            f.write(chunk)
```

#### WebSocket 大型消息处理

```python
# 设置足够大的消息尺寸
server = await websockets.serve(handler, host, port, max_size=50*1024*1024)

# 或实现分块传输
async def send_large_message(websocket, data, chunk_size=1024*1024):
    message = json.dumps(data)
    chunks = []
    
    total_chunks = (len(message) + chunk_size - 1) // chunk_size
    for i in range(total_chunks):
        start = i * chunk_size
        end = min((i + 1) * chunk_size, len(message))
        chunk = message[start:end]
        
        chunks.append({
            "type": "CHUNK",
            "index": i,
            "total": total_chunks,
            "data": chunk,
            "id": str(uuid.uuid4()) if i == 0 else chunks[0]["id"]
        })
    
    for chunk in chunks:
        await websocket.send(json.dumps(chunk))
```

## 5. 资源管理与最佳实践

### 5.1 连接生命周期管理

```python
# aiohttp 资源管理
try:
    session = aiohttp.ClientSession()
    # 使用 session
finally:
    await session.close()

# websockets 资源管理
try:
    server = await websockets.serve(handler, host, port)
    # 服务运行
finally:
    server.close()
    await server.wait_closed()
```

### 5.2 异常处理最佳实践

```python
# aiohttp 异常处理
try:
    async with session.get(url) as response:
        if response.status >= 400:
            error_text = await response.text()
            raise HttpException(response.status, error_text)
        return await response.json()
except aiohttp.ClientError as e:
    # 网络错误
except HttpException as e:
    # HTTP 错误
except Exception as e:
    # 其他错误

# websocket 异常处理
try:
    async for message in websocket:
        # 处理消息
except ConnectionClosedOK:
    # 正常关闭
except ConnectionClosedError as e:
    # 异常关闭
finally:
    # 清理资源
```

### 5.3 性能优化技巧

1. **连接池复用**：aiohttp 自动管理连接池
2. **限制并发请求**：使用信号量控制并发
3. **超时设置**：为所有请求设置合理超时
4. **压缩支持**：启用内容压缩减少传输量
5. **WebSocket 心跳**：保持连接活跃

```python
# 并发控制
semaphore = asyncio.Semaphore(10)  # 最多10个并发请求

async def fetch(url):
    async with semaphore:
        async with session.get(url, timeout=30) as response:
            return await response.json()
```

## 6. 总结与进阶提示

### 关键区别回顾

- **aiohttp**：HTTP 协议，适用于请求-响应模式，需要明确的 headers 和 data
- **websockets**：WebSocket 协议，适用于实时双向通信，消息基于帧传输
- **连接模式**：HTTP 通常是短连接、WebSocket 是长连接
- **状态管理**：HTTP 通过 cookies/会话，WebSocket 通过持久连接

### 进阶使用场景

1. **混合架构**：
   - WebSocket 用于实时通信
   - HTTP 用于资源获取和认证
   - 两者协同提供完整服务

2. **扩展功能**：
   - WebSocket 消息队列与缓冲
   - 自动重连与会话恢复
   - 消息压缩与优化传输
   - 流式响应处理

3. **安全考虑**：
   - WebSocket 认证与授权
   - 消息验证与加密
   - 速率限制与防滥用

异步网络通信库是构建高性能、响应式应用的核心组件，掌握 aiohttp 和 websockets 这两个库的使用，能够帮助开发者构建从简单 API 客户端到复杂实时通信系统的各种应用。