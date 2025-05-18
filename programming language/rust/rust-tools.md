# tools

## cargo

> cargo 是 rust 的包管理工具

### 换源

下载换源, 在 `~/.cargo/config.toml` 添加

```toml
[source.crates-io]
replace-with = "ustc"

[source.ustc]
registry = "sparse+https://mirrors.ustc.edu.cn/crates.io-index/"
```



### 缓存清理

```powershell
cargo install cargo-cache   # 没装就装一下(第三方库)

cargo cache # 显示缓存
cargo cache --remove-dir all  # 清除所有缓存
```



对于项目内的缓存： `cargo clean` 可以把本项目的 `target` 文件夹给清理了

 

### 项目更新

如果项目中使用的 `crate` 跨越了一个小版本 (例如 `0.8.5 -> 0.9.0`)，则必须使用  ` cargo update` 来更新，否则 `cargo.lock` 文件不会改变，即编译时使用的 crate 版本不会变

