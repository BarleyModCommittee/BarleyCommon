#!/usr/bin/env python3
"""
BarleyCommon 代码生成脚本
从 def.toml 读取配置，生成 C++ / Lua 模块文件
"""

import argparse
import sys
from pathlib import Path

from scripts.shared import load_config
from scripts.gen_cpp import generate_cpp
from scripts.gen_lua import generate_lua


def main():
    parser = argparse.ArgumentParser(description="BarleyCommon 代码生成脚本")
    parser.add_argument(
        "--lang",
        choices=["cpp", "lua", "all"],
        default="all",
        help="指定生成的语言 (默认: all)",
    )
    args = parser.parse_args()

    root_dir = Path(__file__).parent
    config_path = root_dir / "def.toml"
    templates_dir = root_dir / "templates"

    if not config_path.exists():
        print(f"Error: Config file not found: {config_path}", file=sys.stderr)
        sys.exit(1)

    print(f"Loading config: {config_path}")
    config = load_config(config_path)

    if args.lang in ("cpp", "all"):
        cpp_output_dir = root_dir / "BarleyCommon-cpp"
        print(f"Generating C++ files to: {cpp_output_dir}")
        cpp_output_dir.mkdir(parents=True, exist_ok=True)
        generate_cpp(cpp_output_dir, templates_dir, config)

    if args.lang in ("lua", "all"):
        lua_output_dir = root_dir / "BarleyCommon-lua"
        print(f"Generating Lua files to: {lua_output_dir}")
        lua_output_dir.mkdir(parents=True, exist_ok=True)
        generate_lua(lua_output_dir, templates_dir, config)

    print("Done!")


if __name__ == "__main__":
    main()
