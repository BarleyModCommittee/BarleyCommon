# BarleyCommon

麦版卡片编码与赛季编号定义库，目前支持 C++（CMake）和 lua 语言。

## 项目结构

```
BarleyCommon/
├── def.toml              # 配置文件
├── generate.py           # 代码生成入口
├── scripts/              # 生成器模块
│   ├── shared.py         # 共享工具函数
│   ├── gen_cpp.py        # C++ 代码生成
│   └── gen_lua.py        # Lua 代码生成
├── templates/            # 代码模板
├── BarleyCommon-cpp/     # 生成的 C++ 模块文件
└── BarleyCommon-lua/     # 生成的 Lua 模块文件
```

## 数据定义

数据定义使用 TOML 维护，默认包含以下常量定义：

- **CardCode** - 卡片编码（value / short / alias）
- **RoleType** - 角色类型（value / name）
- **SeedType** - 种子类型（value）
- **S1** / **S6** - 赛季数据（seed / role 可选键）

## 使用方法

### 生成代码

```bash
# 生成所有语言（默认）
python generate.py

# 仅生成 C++
python generate.py --lang cpp

# 仅生成 Lua
python generate.py --lang lua
```

### 环境要求

- Python >= 3.11

## 修改数据

1. 编辑 `def.toml`
2. 运行 `python generate.py`
3. 提交变更