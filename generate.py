#!/usr/bin/env python3
"""
BarleyCommon 代码生成脚本
从 def.toml 读取配置，生成 C++ / Lua 模块文件
"""

import tomllib
import sys
from pathlib import Path
from typing import Any


def load_config(config_path: Path) -> dict[str, Any]:
    """加载 TOML 配置文件"""
    with open(config_path, "rb") as f:
        return tomllib.load(f)


def generate_cardcode_entries(cardcode: dict[str, Any]) -> str:
    """生成 CardCode 枚举条目"""
    lines = []
    # 按 value 排序，但 Last/Nil/Unknown 放最后
    normal = []
    special = []
    for name, data in cardcode.items():
        if name in ("Last", "Nil", "Unknown"):
            special.append((name, data))
        else:
            normal.append((name, data))

    normal.sort(key=lambda x: x[1]["value"])
    special.sort(key=lambda x: x[1]["value"])

    for name, data in normal:
        alias = data.get("alias", "")
        lines.append(f"\t\t/// @brief {alias}")
        lines.append(f"\t\t{name},")

    # Last 放在普通条目最后
    if "Last" in dict(special):
        lines.append("\t\t/// @brief 正常植物号码的总数")
        lines.append("\t\tLast,")
        lines.append("")

    return "\n".join(lines)


def generate_roletype_entries(roletype: dict[str, Any]) -> str:
    """生成 RoleType 枚举条目"""
    lines = []
    sorted_items = sorted(roletype.items(), key=lambda x: x[1]["value"])

    for name, data in sorted_items:
        comment_name = data.get("name", "")
        if name == "None":
            lines.append(f"\t\tNone = 0,")
        else:
            lines.append(f"\t\t/// @brief {comment_name}")
            lines.append(f"\t\t{name},")

    return "\n".join(lines)


def generate_seedtype_entries(seedtype: dict[str, Any]) -> str:
    """生成 SeedType 枚举条目"""
    lines = []
    sorted_items = sorted(seedtype.items(), key=lambda x: x[1])

    for name, value in sorted_items:
        if name == "None":
            lines.append(f"\t\tNone = -1,")
        else:
            lines.append(f"\t\t{name} = {value},")

    return "\n".join(lines)


def generate_codemap_entries(cardcode: dict[str, Any]) -> str:
    """生成 CodeMap 短名称数组"""
    sorted_items = sorted(
        [(n, d) for n, d in cardcode.items() if n not in ("Last", "Nil", "Unknown")],
        key=lambda x: x[1]["value"],
    )

    # 每行 7 个
    result = []
    current_line = []
    for i, (name, data) in enumerate(sorted_items):
        short = data.get("short", "")
        current_line.append(f'"{short}"')
        if len(current_line) == 7 or i == len(sorted_items) - 1:
            comma = "," if i < len(sorted_items) - 1 else ""
            result.append("\t\t" + ", ".join(current_line) + comma)
            current_line = []

    return "\n".join(result)


def generate_codenamemap_entries(cardcode: dict[str, Any]) -> str:
    """生成 CodeNameMap 全名数组"""
    sorted_items = sorted(
        [(n, d) for n, d in cardcode.items() if n not in ("Last", "Nil", "Unknown")],
        key=lambda x: x[1]["value"],
    )

    # 每行 7 个
    result = []
    current_line = []
    for i, (name, data) in enumerate(sorted_items):
        alias = data.get("alias", "")
        current_line.append(f'"{alias}"')
        if len(current_line) == 7 or i == len(sorted_items) - 1:
            comma = "," if i < len(sorted_items) - 1 else ""
            result.append("\t\t" + ", ".join(current_line) + comma)
            current_line = []

    return "\n".join(result)


def generate_seedtype_map(season_data: dict[str, Any], cardcode: dict[str, Any]) -> str:
    """生成赛季的 SeedTypeMap 数组"""
    # 构建完整的映射，缺失的为 None
    cardcode_sorted = sorted(
        [(n, d) for n, d in cardcode.items() if n not in ("Last", "Nil", "Unknown")],
        key=lambda x: x[1]["value"],
    )

    lines = []
    for i, (name, data) in enumerate(cardcode_sorted):
        seed = season_data.get(name, {}).get("seed", "None")
        lines.append(f"\t\tSeedType::{seed},")

    return "\n".join(lines)


def generate_role_map(season_data: dict[str, Any], cardcode: dict[str, Any]) -> str:
    """生成赛季的 RoleTypeMap 数组"""
    cardcode_sorted = sorted(
        [(n, d) for n, d in cardcode.items() if n not in ("Last", "Nil", "Unknown")],
        key=lambda x: x[1]["value"],
    )

    lines = []
    for name, data in cardcode_sorted:
        role = season_data.get(name, {}).get("role", "None")
        lines.append(f"\t\tRoleType::{role},")

    block = """
	constexpr array<RoleType, static_cast<size_t>(CardCode::Last)> RoleTypeMap =
	{
""" + "\n".join(lines) + """
	};"""
    return block


def count_valid_codes(season_data: dict[str, Any]) -> int:
    """计算赛季中有效卡片数量"""
    return sum(1 for v in season_data.values() if v.get("seed") != "None")


def generate_get_role_function(season_name: str, has_role: bool) -> str:
    """生成 getRole 函数（仅当赛季有 role 字段时）"""
    if not has_role:
        return ""

    return f"""
	optional<RoleType> getRole(const CardCode code)
	{{
		if (code >= static_cast<CardCode>(0) && code < CardCode::Last)
			return RoleTypeMap[static_cast<int>(code)];

		switch (code)
		{{
		case CardCode::Nil:
			return RoleType::None;
		default:
			return std::nullopt;
		}}
	}}"""


def render_template(template_path: Path, replacements: dict[str, str]) -> str:
    """渲染模板文件"""
    content = template_path.read_text(encoding="utf-8")
    for key, value in replacements.items():
        content = content.replace(f"{{{{ {key} }}}}", value)
    return content


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

    # 保持 Nil 在 Unknown 之前的顺序
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


def generate_lua(output_dir: Path, config: dict[str, Any]) -> None:
    """生成所有 Lua 文件"""
    templates_dir = Path(__file__).parent / "templates"
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


def generate_cpp(output_dir: Path, config: dict[str, Any]) -> None:
    """生成所有 C++ 文件"""
    templates_dir = Path(__file__).parent / "templates"
    cardcode = config["CardCode"]
    roletype = config["RoleType"]
    seedtype = config["SeedType"]

    # 生成 Index.cppm
    index_template = templates_dir / "Index.cppm.template"
    index_content = render_template(index_template, {})
    (output_dir / "Index.cppm").write_text(index_content, encoding="utf-8")
    print(f"  Generated Index.cppm")

    # 生成 Def.cppm
    def_template = templates_dir / "Def.cppm.template"
    def_replacements = {
        "cardcode_entries": generate_cardcode_entries(cardcode),
        "roletype_entries": generate_roletype_entries(roletype),
        "seedtype_entries": generate_seedtype_entries(seedtype),
        "codemap_entries": generate_codemap_entries(cardcode),
        "codenamemap_entries": generate_codenamemap_entries(cardcode),
    }
    def_content = render_template(def_template, def_replacements)
    (output_dir / "Def.cppm").write_text(def_content, encoding="utf-8")
    print(f"  Generated Def.cppm")

    # 生成赛季文件
    season_template = templates_dir / "S_season.cppm.template"
    for season_name in ["S1", "S6"]:
        if season_name not in config:
            continue

        season_data = config[season_name]
        has_role = any("role" in v for v in season_data.values() if isinstance(v, dict))

        season_replacements = {
            "season_name": season_name,
            "seedtype_map_entries": generate_seedtype_map(season_data, cardcode),
            "role_map_block": generate_role_map(season_data, cardcode) if has_role else "",
            "valid_count": str(count_valid_codes(season_data)),
            "get_role_function": generate_get_role_function(season_name, has_role),
        }
        season_content = render_template(season_template, season_replacements)
        (output_dir / f"{season_name}.cppm").write_text(season_content, encoding="utf-8")
        print(f"  Generated {season_name}.cppm")


def main():
    root_dir = Path(__file__).parent
    config_path = root_dir / "def.toml"

    if not config_path.exists():
        print(f"Error: Config file not found: {config_path}", file=sys.stderr)
        sys.exit(1)

    print(f"Loading config: {config_path}")
    config = load_config(config_path)

    # 生成 C++ 文件
    cpp_output_dir = root_dir / "BarleyCommon-cpp"
    print(f"Generating C++ files to: {cpp_output_dir}")
    cpp_output_dir.mkdir(parents=True, exist_ok=True)
    generate_cpp(cpp_output_dir, config)

    # 生成 Lua 文件
    lua_output_dir = root_dir / "BarleyCommon-lua"
    print(f"Generating Lua files to: {lua_output_dir}")
    lua_output_dir.mkdir(parents=True, exist_ok=True)
    generate_lua(lua_output_dir, config)

    print("Done!")


if __name__ == "__main__":
    main()