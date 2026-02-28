module;

#include <vector>
#include <string>
#include <stdexcept>
#include <format>
#include <map>
#include <concepts>
#include <algorithm>

export module BarleyCommon;

import <array>;
import <ranges>;
import <string>;
import <string_view>;
import <utility>;

using std::array;
using std::pair;
using std::string;
using std::string_view;

export namespace BarleyCommon
{
	/// @enum CardCode
	/// @brief 卡片编码定义
	enum class CardCode : int
	{
		/// @brief 豌豆射手
		PeaShooter,
		/// @brief 向日葵
		SunFlower,
		/// @brief 坚果墙
		WallNut,
		/// @brief 土豆雷
		PotatoMine,
		/// @brief 寒冰射手
		SnowPea,
		/// @brief 大嘴花
		Chomper,
		/// @brief 双发射手
		Repeater,
		/// @brief 小喷菇
		PuffShroom,
		/// @brief 阳光菇
		SunShroom,
		/// @brief 大喷菇
		FumeShroom,
		/// @brief 魅惑菇
		HypnoShroom,
		/// @brief 胆小菇
		ScaredyShroom,
		/// @brief 寒冰菇
		IceShroom,
		/// @brief 荷叶
		LilyPad,
		/// @brief 窝瓜
		Squash,
		/// @brief 三线射手
		Threepeater,
		/// @brief 缠绕海草
		TangleKelp,
		/// @brief 火炬树桩
		Torchwood,
		/// @brief 高坚果
		TallNut,
		/// @brief 海蘑菇
		SeaShroom,
		/// @brief 路灯花
		Plantern,
		/// @brief 仙人掌
		Cactus,
		/// @brief 三叶草
		Blover,
		/// @brief 裂荚射手
		SplitPea,
		/// @brief 杨桃
		Starfruit,
		/// @brief 南瓜头
		Pumpkin,
		/// @brief 磁力菇
		MagnetShroom,
		/// @brief 卷心菜投手
		CabbagePult,
		/// @brief 花盆
		FlowerPot,
		/// @brief 玉米投手
		KernelPult,
		/// @brief 大蒜
		Garlic,
		/// @brief 叶子保护伞
		UmbrellaLeaf,
		/// @brief 金盏花
		Marigold,
		/// @brief 西瓜投手
		MelonPult,
		/// @brief 机枪射手
		GatlingPea,
		/// @brief 忧郁菇/忧郁南瓜
		GloomShroom,
		/// @brief 香蒲
		Cattail,
		/// @brief 冰瓜
		WinterMelon,
		/// @brief 吸金磁
		GoldMagnet,
		/// @brief 钢地刺
		SpikeRock,
		/// @brief 爆炸坚果
		Explode_O_Nut,
		/// @brief 火红莲
		Endoflame,
		/// @brief 反向双发
		LeftRepeater,
		/// @brief 大麦
		Barley,
		/// @brief 狙击豌豆
		SniperShooter,
		/// @brief 晶钻菇
		DiamondShroom,
		/// @brief 春分藤
		SpringEquinoxVine,
		/// @brief 幽冥菇
		DarkShroom,
		/// @brief 奶山竹
		Mangosteen,
		/// @brief 逆时草
		ThymeWarp,
		/// @brief 正常植物号码的总数
		Last,

		// 特殊编码
		Nil = -1,        // 空位 表示该赛季不存在该植物
		Unknown = -2       // 未知 表示可能输入错误
	};

    // 卡片组定义
    struct CardSet {
        int set_id;
        std::string name;
        std::array<std::string, 57> cards;  // 57个位置（0-52, 76-79）
    };

    // 输入结构
    struct GameInput {
        int set_number;    // Sn 中的 n
        std::array<int, 5> card_codes;  // a, b, c, d, e
        int t;             // 时间t 如果需要？
    };

    // 输出结构
    struct GameOutput {
        std::array<std::string, 5> card_names;
        std::array<CardCode, 5> card_codes;
        int t;
        std::string set_name;

        // 格式化输出
        std::string to_string() const {
            return std::format("({}, {}, {}, {}, {}, {}, {})",
                card_names[0], card_names[1], card_names[2],
                card_names[3], card_names[4], t, set_name);
        }
    };

    // 卡片编码到名称的映射
    export const std::map<CardCode, std::string> CARD_NAMES = {
        {CardCode::PeaShooter,       "豌豆射手"},
        {CardCode::WallNut,          "坚果墙"},
        {CardCode::PotatoMine,       "土豆雷"},
        {CardCode::SnowPea,          "寒冰射手"},
        {CardCode::Chomper,          "大嘴花"},
        {CardCode::Repeater,         "双发射手"},
        {CardCode::PuffShroom,       "小喷菇"},
        {CardCode::SunShroom,        "阳光菇"},
        {CardCode::FumeShroom,       "大喷菇"},
        {CardCode::HypnoShroom,      "魅惑菇"},
        {CardCode::ScaredyShroom,    "胆小菇"},
        {CardCode::IceShroom,        "寒冰菇"},
        {CardCode::LilyPad,          "荷叶"},
        {CardCode::Squash,           "窝瓜"},
        {CardCode::Threepeater,      "三线射手"},
        {CardCode::TangleKelp,       "缠绕海草"},
        {CardCode::Torchwood,        "火炬树桩"},
        {CardCode::TallNut,          "高坚果"},
        {CardCode::SeaShroom,        "海蘑菇"},
        {CardCode::Plantern,         "路灯花"},
        {CardCode::Cactus,           "仙人掌"},
        {CardCode::Blover,           "三叶草"},
        {CardCode::SplitPea,         "裂荚射手"},
        {CardCode::Starfruit,        "杨桃"},
        {CardCode::Pumpkin,          "南瓜头"},
        {CardCode::MagnetShroom,     "磁力菇"},
        {CardCode::CabbagePult,      "卷心菜投手"},
        {CardCode::FlowerPot,        "花盆"},
        {CardCode::KernelPult,       "玉米投手"},
        {CardCode::Garlic,           "大蒜"},
        {CardCode::UmbrellaLeaf,     "叶子保护伞"},
        {CardCode::Marigold,         "金盏花"},
        {CardCode::MelonPult,        "西瓜投手"},
        {CardCode::GatlingPea,       "机枪射手"},
        {CardCode::GloomShroom,      "忧郁菇"},
        {CardCode::Cattail,          "猫尾草"},
        {CardCode::WinterMelon,      "冰瓜"},
        {CardCode::GoldMagnet,       "吸金磁"},
        {CardCode::SpikeRock,        "地刺王"},
        {CardCode::Explode_O_Nut,    "爆炸坚果"},
        {CardCode::SpikeRock,        "地刺王"},
        {CardCode::Barley,           "巨大坚果"},
        {CardCode::Endoflame,        "幼苗"},
        {CardCode::LeftRepeater,     "反向双发"},
        {CardCode::SpringEquinoxVine,"春分藤"},
        {CardCode::DarkShroom,       "幽冥菇"},
        {CardCode::Mangosteen,       "奶山竹"},
        {CardCode::ThymeWarp,        "逆时草"},
        {CardCode::Nil,         "空"},
        {CardCode::Unknown,        "未知"}
    };

    // 卡片组数据库（基于题目数据）
    export class CardSetDatabase {
    private:
        std::vector<CardSet> sets;

        // 将索引转换为实际位置（处理跳跃）
        std::size_t index_to_position(int indexBPT) const {
            static const std::array<int, 57> position_map = {
                0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
                20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
                38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
                // 跳跃到 76-79
                53, 54, 55, 56
            };

            if (indexBPT >= 0 && indexBPT <= 52) {
                return indexBPT;
            }
            else if (indexBPT >= 76 && indexBPT <= 79) {
                return 53 + (indexBPT - 76);
            }
            throw std::out_of_range(std::format("无效的卡片索引: {}", indexBPT));
        }

    public:
        CardSetDatabase() {
            initialize_sets();
        }

        void initialize_sets() {
            // S0 
            sets.push_back({
                0, "S0",
                {"豌", "空", "空", "坚", "雷", "寒", "嘴" ,"双",
                 "小", "空", "喷", "空", "魅", "胆", "空" ,"空", 
                 "荷", "窝", "三", "空", "空", "地", "火" ,"高", 
                 "海", "空", "仙", "空", "裂", "星", "南+","磁", 
                 "卷", "盆", "玉", "空", "蒜", "伞", "空" ,"瓜",
                 "机", "空" ,"曾", "猫", "冰", "空", "刺" ,"空",
                 "空", "空", "空", "空", "空", "空", "空" ,"空",
                 "空"}
                });

            // S1 
            sets.push_back({
                1, "S1",
                {"豌", "空", "空", "坚", "雷", "寒", "嘴" ,"双",
                 "小", "空", "喷", "空", "魅", "胆", "空" ,"空",
                 "荷", "窝", "三", "空", "空", "空", "火" ,"高",
                 "海", "空", "仙", "空", "裂", "星", "南+","磁",
                 "卷", "盆", "玉", "空", "蒜", "伞", "空" ,"瓜",
                 "机", "空", "曾", "猫", "冰", "空", "刺" ,"空",
                 "空", "空", "空", "空", "空", "空", "空" ,"空",
                 "空"}
                });

            // S2 
            sets.push_back({
                2, "S2",
                {"豌", "空", "空", "坚", "空", "寒", "嘴" ,"双",
                 "空", "空", "喷", "空", "魅", "胆", "空" ,"空",
                 "荷", "空", "三", "空", "空", "空", "火" ,"高",
                 "空", "空", "仙", "空", "裂", "星", "南+","磁",
                 "卷", "盆", "玉", "空", "蒜", "伞", "空" ,"瓜",
                 "机", "空", "曾", "猫", "冰", "空", "刺" ,"空",
                 "空", "空", "空", "空", "空", "空", "空" ,"空",
                 "空"}
                });

            // S3 
            sets.push_back({
                3, "S3",
                {"豌", "麦", "空", "坚", "空", "寒", "嘴" ,"双",
                 "小", "空", "喷", "空", "魅", "胆", "空" ,"空",
                 "荷", "空", "三", "空", "空", "空", "火" ,"高",
                 "海", "空", "仙", "空", "裂", "星", "南+","磁",
                 "卷", "盆", "玉", "空", "蒜", "伞", "空" ,"瓜",
                 "机", "空", "曾", "猫", "冰", "空", "刺" ,"空",
                 "空", "空", "空", "空", "空", "空", "空" ,"空",
                 "空"}
                });

            // S4 
            sets.push_back({
                4, "S4",
                {"狙", "麦", "空" ,"坚", "空", "寒", "嘴" ,"双",
                 "小", "空", "喷" ,"空", "魅", "胆", "空" ,"空",
                 "荷", "空", "三" ,"空", "空", "空", "火" ,"高",
                 "海", "灯", "仙" ,"空", "裂", "星", "南+","磁",
                 "卷", "盆", "玉" ,"空", "蒜", "伞", "金" ,"瓜",
                 "机", "空", "曾+","猫", "冰", "吸", "刺" ,"空",
                 "空", "爆", "空" ,"空", "空", "空", "空" ,"空",
                 "空"}
                });

            // S5 
            sets.push_back({
                5, "S5",
                {"狙", "麦", "空" ,"坚", "雷", "寒", "嘴" ,"双",
                 "小", "空", "喷" ,"空", "魅", "胆", "川" ,"空",
                 "荷", "空", "三" ,"空", "空", "空", "火" ,"高",
                 "海", "灯", "仙" ,"叶", "裂", "星", "南+","磁",
                 "卷", "盆", "玉" ,"空", "蒜", "伞", "金" ,"瓜",
                 "机", "空", "曾+","猫", "冰", "吸", "刺" ,"空",
                 "空", "爆", "空" ,"空", "空", "空", "空" ,"空",
                 "空"}
                });

            // S6 
            sets.push_back({
                6, "S6",
                {"狙", "麦", "空", "坚", "雷", "寒", "嘴", "双",
                 "小", "阳", "喷", "空", "魅", "胆", "川", "空",
                 "晶", "窝", "三", "草", "空", "空", "火", "高",
                 "海", "灯", "仙", "叶", "裂", "星", "空", "磁",
                 "卷", "空", "玉", "空", "蒜", "伞", "金", "瓜",
                 "机", "空", "曾", "猫", "冰", "吸", "刺", "空",
                 "空", "爆", "空", "飘", "反", "藤", "幽", "奶",
                 "逆"}
                });

            // S7
            sets.push_back({
                7, "S7",
                {"狙", "空", "空", "坚", "雷", "寒", "嘴", "双",
                 "小", "阳", "喷", "空", "魅", "胆", "川", "空",
                 "空", "窝", "三", "草", "空", "空", "火", "高",
                 "海", "灯", "仙", "叶", "裂", "星", "空", "磁",
                 "卷", "空", "玉", "空", "蒜", "伞", "金", "瓜",
                 "机", "空", "曾", "猫", "冰", "吸", "刺", "空",
                 "空", "爆", "麦", "飘", "反", "藤", "幽", "奶",
                 "逆"} //(？
                });
        }

        // 获取指定组的卡片名称
        std::string get_card_name(int set_id, int card_index) const {
            if (set_id < 0 || set_id >= static_cast<int>(sets.size())) {
                throw std::out_of_range(std::format("无效的组ID: {}", set_id));
            }

            auto pos = index_to_position(card_index);
            if (pos >= sets[set_id].cards.size()) {
                throw std::out_of_range(std::format("卡片索引超出范围: {}", card_index));
            }

            return sets[set_id].cards[pos];
        }

        // 获取卡片组信息
        const CardSet& get_card_set(int set_id) const {
            if (set_id < 0 || set_id >= static_cast<int>(sets.size())) {
                throw std::out_of_range(std::format("无效的组ID: {}", set_id));
            }
            return sets[set_id];
        }

        // 获取所有组信息
        std::vector<CardSet> get_all_sets() const {
            return sets;
        }

        // 根据名称查找卡片编码
        CardCode find_card_code(const std::string& name) const {
            for (const auto& [code, card_name] : CARD_NAMES) {
                if (card_name == name) {
                    return code;
                }
            }
            return CardCode::Unknown;
        }
    };

    // 主转换器类
    export class PvZCardConverter {
    private:
        CardSetDatabase database;

    public:
        PvZCardConverter() = default;

        // 核心转换函数
        GameOutput convert(const GameInput& input) const {
            GameOutput output;
            output.set_name = database.get_card_set(input.set_number).name;
            output.t = input.t;

            // 转换每个卡片编码
            for (size_t i = 0; i < input.card_codes.size(); ++i) {
                try {
                    std::string card_name = database.get_card_name(
                        input.set_number,
                        input.card_codes[i]
                    );

                    output.card_names[i] = card_name;
                    output.card_codes[i] = database.find_card_code(card_name);
                }
                catch (const std::exception& e) {
                    output.card_names[i] = "无效卡片";
                    output.card_codes[i] = CardCode::Unknown;
                }
            }

            return output;
        }

        // 批量转换
        std::vector<GameOutput> batch_convert(
            const std::vector<GameInput>& inputs
        ) const {
            std::vector<GameOutput> results;
            results.reserve(inputs.size());

            for (const auto& input : inputs) {
                results.push_back(convert(input));
            }

            return results;
        }

        // 显示卡片组信息
        std::string display_card_set(int set_id) const {
            const auto& card_set = database.get_card_set(set_id);
            std::string result = std::format("{}:\n", card_set.name);

            // 显示所有卡片
            for (int i = 0; i <= 52; ++i) {
                result += std::format("#{}: {}\n", i,
                    database.get_card_name(set_id, i));
            }

            // 显示特殊卡片 (76-79)
            for (int i = 76; i <= 79; ++i) {
                result += std::format("#{}: {}\n", i,
                    database.get_card_name(set_id, i));
            }

            return result;
        }

        // 验证输入有效性
        bool validate_input(const GameInput& input) const {
            if (input.set_number < 0 || input.set_number > 6) {
                return false;
            }

            for (int code : input.card_codes) {
                if (code < -1 || (code > 52 && (code < 76 || code > 79))) {
                    return false;
                }
            }

            return true;
        }
    };

    // 便捷函数
    export GameOutput convert_cards(
        int set_number,
        int a, int b, int c, int d, int e,
        int t
    ) {
        PvZCardConverter converter;
        GameInput input{
            set_number,
            {a, b, c, d, e},
            t
        };

        return converter.convert(input);
    }

    // 输入解析器
    export class InputParser {
    public:
        static GameInput parse_string(const std::string& input_str) {
            // 格式: "n,a,b,c,d,e,t"
            std::vector<int> values;
            std::string token;

            for (char ch : input_str) {
                if (ch == ',') {
                    if (!token.empty()) {
                        values.push_back(std::stoi(token));
                        token.clear();
                    }
                }
                else if (std::isdigit(ch) || ch == '-') {
                    token += ch;
                }
            }

            if (!token.empty()) {
                values.push_back(std::stoi(token));
            }

            if (values.size() != 7) {
                throw std::invalid_argument(
                    std::format("输入需要7个参数，得到{}个", values.size())
                );
            }

            return GameInput{
                values[0],  // n
                {values[1], values[2], values[3], values[4], values[5]},  // a,b,c,d,e
                values[6]   // t
            };
        }
    };
}

namespace BarleyCommon
{
	constexpr auto genCodeMap = []()
	{
		array<string_view, static_cast<size_t>(CardCode::Last)> map =
		{
			"豌", "葵", "坚", "雷", "寒", "嘴", "双",
			"小", "阳", "大", "魅", "胆", "川",
			"莲", "窝", "三", "缠", "火", "高",
			"海", "灯", "掌", "叶", "裂", "星", "南", "磁",
			"卷", "盆", "玉", "蒜", "伞", "金", "瓜",
			"机", "曾", "猫", "冰", "吸", "刺",
			"爆", "飘", "反", "麦",
			"狙", "钻", "藤", "幽", "奶", "逆"
		};

		return map;
	};
	constexpr auto CodeMap = genCodeMap();
	constexpr array<string_view, static_cast<size_t>(CardCode::Last)> CodeNameMap = 
	{
		"豌豆射手", "向日葵", "坚果墙", "土豆雷", "寒冰射手", "大嘴花", "双发射手",
		"小喷菇", "阳光菇", "大喷菇", "魅惑菇", "胆小菇", "冰川菇",
		"荷叶", "窝瓜", "三线射手", "缠绕海草", "火炬树桩", "高坚果",
		"海蘑菇", "路灯花", "仙人掌", "三叶草", "裂荚射手", "杨桃", "南瓜壳", "磁力菇",
		"卷心菜投手", "花盆", "玉米投手", "大蒜", "叶子保护伞", "金盏花", "西瓜投手",
		"机枪射手", "忧郁菇", "猫尾草", "冰瓜", "吸金磁", "地刺王",
		"爆炸坚果", "火红莲", "反向双发", "大麦",
		"狙击豌豆", "晶钻菇", "春分藤", "幽冥菇", "奶山竹", "逆时草"
	};
}

export namespace BarleyCommon
{
	string_view toShortName(const CardCode code)
	{
		if (code >= static_cast<CardCode>(0) && code < CardCode::Last)
			return CodeMap[static_cast<int>(code)];

		switch (code)
		{
		case CardCode::Nil:
			return "空";
		default:
			return "Invalid";
		}
	}

	CardCode ShortName2Code(const string_view& view)
	{
		for (int i = 0; i < static_cast<int>(CardCode::Last); i++)
			if (CodeMap[i] == view)
				return static_cast<CardCode>(i);

		if (view == "空")
			return CardCode::Nil;
		if (view == "仙")
			return CardCode::Cactus;
		return CardCode::Unknown;
	}

	string_view getName(const CardCode code)
	{
		if (code >= static_cast<CardCode>(0) && code < CardCode::Last)
			return CodeNameMap[static_cast<int>(code)];

		switch (code)
		{
		case CardCode::Nil:
			return "空";
		default:
			return "Invalid";
		}
	}
}

/*

int main() {
    ////////////// 创建转换器
    PvZCardConverter converter;
    
    ////////////// 转换单个输入
    std::cout << "=== 示例1: 单个转换 ===\n";
    GameInput input1{3, {0, 1, 2, 3, 4}, 100};
    auto output1 = converter.convert(input1);
    std::cout << "输入: S" << input1.set_number << "组，卡片[" 
              << input1.card_codes[0] << "," << input1.card_codes[1] << ","
              << input1.card_codes[2] << "," << input1.card_codes[3] << ","
              << input1.card_codes[4] << "], t=" << input1.t << "\n";
    std::cout << "输出: " << output1.to_string() << "\n\n";
    
    ////////////// 批量转换
    std::cout << "=== 示例2: 批量转换 ===\n";
    std::vector<GameInput> batch_inputs = {
        {0, {0, 7, 18, 22, 29}, 50},
        {1, {3, 5, 6, 23, 30}, 75},
        {2, {0, 4, 8, 16, 39}, 100},
        {6, {76, 77, 78, 79, 40}, 200}
    };
    
    auto batch_outputs = converter.batch_convert(batch_inputs);
    
    for (const auto& output : batch_outputs) {
        std::cout << output.to_string() << "\n";
    }
    std::cout << "\n";



    return 0;
}

*/