"""
BarleyCommon 代码生成 - C++ 模块
此脚本不应被单独调用，仅供 generate.py 导入使用
"""

from pathlib import Path
from typing import Any

from .shared import render_template


def generate_cardcode_entries(cardcode: dict[str, Any]) -> str:
    """生成 CardCode 枚举条目"""
    lines = []
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
    cardcode_sorted = sorted(
        [(n, d) for n, d in cardcode.items() if n not in ("Last", "Nil", "Unknown")],
        key=lambda x: x[1]["value"],
    )

    lines = []
    for name, data in cardcode_sorted:
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


def generate_cpp(output_dir: Path, templates_dir: Path, config: dict[str, Any]) -> None:
    """生成所有 C++ 文件"""
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
