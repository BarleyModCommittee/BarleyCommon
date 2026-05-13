"""
BarleyCommon 代码生成 - Lua 模块
此脚本不应被单独调用，仅供 generate.py 导入使用
"""

from pathlib import Path
from typing import Any

from .shared import render_template


def generate_lua_cardcode_entries(cardcode: dict[str, Any]) -> str:
    """生成 Lua CardCode 表条目"""
    lines = []
    normal = []
    special = []
    for name, data in cardcode.items():
        if name in ("Last", "Nil", "Unknown"):
            special.append((name, data))
        else:
            normal.append((name, data))

    normal.sort(key=lambda x: x[1]["value"])

    for name, data in normal:
        alias = data.get("alias", "")
        lines.append(f"\t{name} = {data['value']},\t-- {alias}")

    if "Last" in dict(special):
        lines.append("\tLast = 50,\t\t\t-- 正常植物号码的总数")
        lines.append("")

    for name in ["Nil", "Unknown"]:
        if name in dict(special):
            data = dict(special)[name]
            comment = "空位 表示该赛季不存在该植物" if name == "Nil" else "未知 表示可能输入错误"
            lines.append(f"\t{name} = {data['value']},\t\t-- {comment}")

    return "\n".join(lines)


def generate_lua_roletype_entries(roletype: dict[str, Any]) -> str:
    """生成 Lua RoleType 表条目"""
    lines = []
    sorted_items = sorted(roletype.items(), key=lambda x: x[1]["value"])

    for name, data in sorted_items:
        comment_name = data.get("name", "")
        lines.append(f"\t{name} = {data['value']},\t-- {comment_name}")

    return "\n".join(lines)


def generate_lua_seedtype_entries(seedtype: dict[str, Any]) -> str:
    """生成 Lua SeedType 表条目"""
    lines = []
    sorted_items = sorted(seedtype.items(), key=lambda x: x[1])

    for name, value in sorted_items:
        lines.append(f"\t{name} = {value},")

    return "\n".join(lines)


def generate_lua_codemap_entries(cardcode: dict[str, Any]) -> str:
    """生成 Lua CodeMap 数组"""
    sorted_items = sorted(
        [(n, d) for n, d in cardcode.items() if n not in ("Last", "Nil", "Unknown")],
        key=lambda x: x[1]["value"],
    )

    result = []
    current_line = []
    for i, (name, data) in enumerate(sorted_items):
        short = data.get("short", "")
        current_line.append(f'"{short}"')
        if len(current_line) == 7 or i == len(sorted_items) - 1:
            comma = "," if i < len(sorted_items) - 1 else ""
            result.append("\t" + ", ".join(current_line) + comma)
            current_line = []

    return "\n".join(result)


def generate_lua_codenamemap_entries(cardcode: dict[str, Any]) -> str:
    """生成 Lua CodeNameMap 数组"""
    sorted_items = sorted(
        [(n, d) for n, d in cardcode.items() if n not in ("Last", "Nil", "Unknown")],
        key=lambda x: x[1]["value"],
    )

    result = []
    current_line = []
    for i, (name, data) in enumerate(sorted_items):
        alias = data.get("alias", "")
        current_line.append(f'"{alias}"')
        if len(current_line) == 7 or i == len(sorted_items) - 1:
            comma = "," if i < len(sorted_items) - 1 else ""
            result.append("\t" + ", ".join(current_line) + comma)
            current_line = []

    return "\n".join(result)


def generate_lua_seedtype_map(season_data: dict[str, Any], cardcode: dict[str, Any]) -> str:
    """生成 Lua 赛季 SeedTypeMap 数组"""
    cardcode_sorted = sorted(
        [(n, d) for n, d in cardcode.items() if n not in ("Last", "Nil", "Unknown")],
        key=lambda x: x[1]["value"],
    )

    lines = []
    for name, data in cardcode_sorted:
        seed = season_data.get(name, {}).get("seed", "None")
        lines.append(f"\tBarleyCommon.SeedType.{seed},")

    return "\n".join(lines)


def generate_lua_role_map(season_name: str, season_data: dict[str, Any], cardcode: dict[str, Any]) -> str:
    """生成 Lua 赛季 RoleTypeMap 数组"""
    cardcode_sorted = sorted(
        [(n, d) for n, d in cardcode.items() if n not in ("Last", "Nil", "Unknown")],
        key=lambda x: x[1]["value"],
    )

    lines = []
    for name, data in cardcode_sorted:
        role = season_data.get(name, {}).get("role", "None")
        lines.append(f"\tBarleyCommon.RoleType.{role},")

    block = f"\nBarleyCommon.{season_name}.RoleTypeMap = {{\n" + "\n".join(lines) + "\n}"
    return block


def generate_lua_get_role_function(season_name: str, has_role: bool) -> str:
    """生成 Lua getRole 函数"""
    if not has_role:
        return ""

    return f"""
function BarleyCommon.{season_name}.getRole(code)
    if code >= 0 and code < BarleyCommon.CardCode.Last then
        return BarleyCommon.{season_name}.RoleTypeMap[code + 1]
    end
    if code == BarleyCommon.CardCode.Nil then
        return BarleyCommon.RoleType.None
    end
    return nil
end"""


def generate_lua(output_dir: Path, templates_dir: Path, config: dict[str, Any]) -> None:
    """生成所有 Lua 文件"""
    cardcode = config["CardCode"]
    roletype = config["RoleType"]
    seedtype = config["SeedType"]

    # 生成赛季模块内容
    season_template = templates_dir / "season.lua.template"
    season_modules = []
    for season_name in ["S1", "S6"]:
        if season_name not in config:
            continue

        season_data = config[season_name]
        has_role = any("role" in v for v in season_data.values() if isinstance(v, dict))

        season_replacements = {
            "season_name": season_name,
            "seedtype_map_entries": generate_lua_seedtype_map(season_data, cardcode),
            "role_map_block": generate_lua_role_map(season_name, season_data, cardcode) if has_role else "",
            "get_role_function": generate_lua_get_role_function(season_name, has_role),
        }
        season_content = render_template(season_template, season_replacements)
        season_modules.append(season_content)
        print(f"  Generated {season_name} module (Lua)")

    # 生成主文件
    main_template = templates_dir / "BarleyCommon.lua.template"
    main_replacements = {
        "cardcode_entries": generate_lua_cardcode_entries(cardcode),
        "roletype_entries": generate_lua_roletype_entries(roletype),
        "seedtype_entries": generate_lua_seedtype_entries(seedtype),
        "codemap_entries": generate_lua_codemap_entries(cardcode),
        "codenamemap_entries": generate_lua_codenamemap_entries(cardcode),
        "season_modules": "\n".join(season_modules),
    }
    main_content = render_template(main_template, main_replacements)
    (output_dir / "BarleyCommon.lua").write_text(main_content, encoding="utf-8")
    print(f"  Generated BarleyCommon.lua")
