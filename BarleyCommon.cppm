export module BarleyCommon;

//export void MyFunc(); 

#include <vector>
#include <string>
#include <stdexcept>
#include <format>
#include <array>
#include <map>
#include <ranges>
#include <concepts>
#include <string_view>
#include <algorithm>

export namespace BarleyPlantType {

    // 卡片编码定义
    enum class CardCode : int {
        // 基础植物
        Plant00 = 0,    // 豌豆射手
        Plant01 = 1,    // 向日葵
        Plant02 = 2,    // 樱桃炸弹
        Plant03 = 3,    // 坚果墙
        Plant04 = 4,    // 土豆雷
        Plant05 = 5,    // 寒冰射手
        Plant06 = 6,    // 大嘴花
        Plant07 = 7,    // 双发射手
        Plant08 = 8,    // 小喷菇
        Plant09 = 9,    // 阳光菇
        Plant10 = 10,   // 大喷菇
        Plant11 = 11,   // 墓碑吞噬者
        Plant12 = 12,   // 魅惑菇
        Plant13 = 13,   // 胆小菇
        Plant14 = 14,   // 寒冰菇
        Plant15 = 15,   // 毁灭菇
        Plant16 = 16,   // 荷叶
        Plant17 = 17,   // 窝瓜
        Plant18 = 18,   // 三线射手
        Plant19 = 19,   // 缠绕海草
        Plant20 = 20,   // 火爆辣椒
        Plant21 = 21,   // 地刺
        Plant22 = 22,   // 火炬树桩
        Plant23 = 23,   // 高坚果
        Plant24 = 24,   // 海蘑菇
        Plant25 = 25,   // 路灯花
        Plant26 = 26,   // 仙人掌
        Plant27 = 27,   // 三叶草
        Plant28 = 28,   // 裂荚射手
        Plant29 = 29,   // 杨桃
        Plant30 = 30,   // 南瓜头
        Plant31 = 31,   // 磁力菇
        Plant32 = 32,   // 卷心菜投手
        Plant33 = 33,   // 花盆
        Plant34 = 34,   // 玉米投手
        Plant35 = 35,   // 咖啡豆
        Plant36 = 36,   // 大蒜
        Plant37 = 37,   // 叶子保护伞
        Plant38 = 38,   // 金盏花
        Plant39 = 39,   // 西瓜投手
        Plant40 = 40,   // 机枪射手
        Plant41 = 41,   // 双子向日葵
        Plant42 = 42,   // 忧郁菇
        Plant43 = 43,   // 猫尾草
        Plant44 = 44,   // 冰瓜
        Plant45 = 45,   // 吸金磁
        Plant46 = 46,   // 地刺王
        Plant47 = 47,   // 玉米加农炮
        Plant48 = 48,   // 模仿者
        Plant49 = 49,   // 爆炸坚果
        Plant50 = 50,   // 巨大坚果
        Plant51 = 51,   // 幼苗
        Plant52 = 52,   // 反向双发
        ///////////////////////////
        Plant76 = 76,   // 春分藤
        Plant77 = 77,   // 幽冥菇
        Plant78 = 78,   // 奶山竹
        Plant79 = 79,   // 逆时草

        // 特殊编码
        Empty = -1,        // 空位 表示该赛季不存在该植物
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
        {CardCode::Plant00, "豌豆射手"},
        {CardCode::Plant01, "向日葵"},
        {CardCode::Plant02, "樱桃炸弹"},
        {CardCode::Plant03, "坚果墙"},
        {CardCode::Plant04, "土豆雷"},
        {CardCode::Plant05, "寒冰射手"},
        {CardCode::Plant06, "大嘴花"},
        {CardCode::Plant07, "双发射手"},
        {CardCode::Plant08, "小喷菇"},
        {CardCode::Plant09, "阳光菇"},
        {CardCode::Plant10, "大喷菇"},
        {CardCode::Plant11, "墓碑吞噬者"},
        {CardCode::Plant12, "魅惑菇"},
        {CardCode::Plant13, "胆小菇"},
        {CardCode::Plant14, "寒冰菇"},
        {CardCode::Plant15, "毁灭菇"},
        {CardCode::Plant16, "荷叶"},
        {CardCode::Plant17, "窝瓜"},
        {CardCode::Plant18, "三线射手"},
        {CardCode::Plant19, "缠绕海草"},
        {CardCode::Plant20, "火爆辣椒"},
        {CardCode::Plant21, "地刺"},
        {CardCode::Plant22, "火炬树桩"},
        {CardCode::Plant23, "高坚果"},
        {CardCode::Plant24, "海蘑菇"},
        {CardCode::Plant25, "路灯花"},
        {CardCode::Plant26, "仙人掌"},
        {CardCode::Plant27, "三叶草"},
        {CardCode::Plant28, "裂荚射手"},
        {CardCode::Plant29, "杨桃"},
        {CardCode::Plant30, "南瓜头"},
        {CardCode::Plant31, "磁力菇"},
        {CardCode::Plant32, "卷心菜投手"},
        {CardCode::Plant33, "花盆"},
        {CardCode::Plant35, "咖啡豆"},
        {CardCode::Plant36, "大蒜"},
        {CardCode::Plant37, "叶子保护伞"},
        {CardCode::Plant38, "金盏花"},
        {CardCode::Plant39, "西瓜投手"},
        {CardCode::Plant40, "机枪射手"},
        {CardCode::Plant41, "双子向日葵"},
        {CardCode::Plant42, "忧郁菇"},
        {CardCode::Plant43, "猫尾草"},
        {CardCode::Plant44, "冰瓜"},
        {CardCode::Plant45, "吸金磁"},
        {CardCode::Plant46, "地刺王"},
        {CardCode::Plant47, "玉米加农炮"},
        {CardCode::Plant48, "模仿者"},
        {CardCode::Plant49, "爆炸坚果"},
        {CardCode::Plant50, "巨大坚果"},
        {CardCode::Plant51, "幼苗"},
        {CardCode::Plant52, "反向双发"},
        {CardCode::Plant76, "春分藤"},
        {CardCode::Plant77, "幽冥菇"},
        {CardCode::Plant78, "奶山竹"},
        {CardCode::Plant79, "逆时草"},
        {CardCode::Empty,   "空"},
        {CardCode::Unknown, "未知"}
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
                 "空", "空", "空", "空", "空", "空", "空" ,"空"}
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
                 "空", "空", "空", "空", "空", "空", "空" ,"空"}
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
                 "空", "空", "空", "空", "空", "空", "空" ,"空"}
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
                 "空", "空", "空", "空", "空", "空", "空" ,"空"}
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
                 "空", "爆", "空" ,"空", "空", "空", "空" ,"空"}
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
                 "空", "爆", "空" ,"空", "空", "空", "空" ,"空"}
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
                 "空", "爆", "空", "飘", "反", "藤", "幽", "奶"}
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