"""
BarleyCommon 代码生成 - 共享工具函数
供 gen_cpp.py 和 gen_lua.py 使用
"""

import tomllib
from pathlib import Path
from typing import Any


def load_config(config_path: Path) -> dict[str, Any]:
    """加载 TOML 配置文件"""
    with open(config_path, "rb") as f:
        return tomllib.load(f)


def render_template(template_path: Path, replacements: dict[str, str]) -> str:
    """渲染模板文件"""
    content = template_path.read_text(encoding="utf-8")
    for key, value in replacements.items():
        content = content.replace(f"{{{{ {key} }}}}", value)
    return content
