# python 打包

## cx_Freeze 打包

先在环境中安装 `pip install cx_Freeze`

在项目目录下配置 `setup.py` 文件

```python
# 使用 cx_Freeze 打包
# python setup.py build

from cx_Freeze import setup, Executable

setup(
    name="neneWiFiCracker",  # 应用程序名称
    version="1.0",       # 版本号
    description="wifi 字典爆破",  # 描述
    executables=[Executable("window.py")]  # 主脚本文件
)

# 高级设置
# build_exe_options = {
#     "packages": ["os", "tkinter"],  # 需要打包的额外包
#     "excludes": ["tkinter.test"],   # 不需要打包的包
#     "include_files": ["config.json"]  # 需要包含的文件或文件夹
# }

# 设置图标
# executables = [Executable("window.py", base="Win32GUI", icon="app.ico")]
```



运行 `python setup.py build` 进行打包， 可以在同目录下找到 `build` 目录，里面包含所有依赖和可执行文件。





## Pyinstaller 打包

安装 `pip install pyinstaller`

- 打包项目

```powershell
pyinstaller --onefile --noconsole --icon=app.ico --name=<Application Name> \
    --add-data="<data_path>;<target_path>" \
    --hidden-import=module1 \
    --hidden-import=module2 \
    main.py
```



- 快速打包单文件脚本

```powershell
pyinstaller -F -n appname -i app.icon py_script.py
```







- `--onefile` 或 `-F` ：将所有内容打包到一个单独的 `.exe` 文件中
- `--noconsole` :用于GUI程序，隐藏控制台
- `--hidden-import=module1` 和 `--hidden-import=module2`：手动指定需要打包的模块（如果 PyInstaller 未能自动检测到）
- `--icon=app.ico` 或 `-i`：指定应用程序图标
- `--name=MyApplication` 或  `-n`：指定生成的 `.exe` 文件的名称
- `--add-data="data;data"`：将 `data` 文件夹打包到目标路径 `data` 下（Windows 使用分号 `;`，Linux 和 macOS 使用冒号 `:`）



**依赖项问题**：如果项目中使用了特殊的库（如 `PyQt`、`Pillow` 等），可能需要额外配置或指定路径。



其他常用的可选参数：

- `--onedir` 或 `-D` ： 把所有内容打包到一个文件夹中
- `--specpath` ： 指定 spec 文件的路径， spec 文件可以用于配置打包行为



