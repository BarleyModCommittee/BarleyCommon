export module pvz_card_converter;

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

export namespace PvZConverter {

    // 卡片编码定义
    enum class CardCode : int {
        // 基础植物
        PEASHOOTER = 0,    // 豌豆射手
        SUNFLOWER = 1,     // 向日葵
        CHERRY_BOMB = 2,   // 樱桃炸弹
        WALL_NUT = 3,      // 坚果墙
        POTATO_MINE = 4,   // 土豆雷
        SNOW_PEA = 5,      // 寒冰射手
        CHOMPER = 6,       // 大嘴花
        REPEATER = 7,      // 双发射手
        PUFF_SHROOM = 8,   // 小喷菇
        SUN_SHROOM = 9,    // 阳光菇
        FUME_SHROOM = 10,  // 大喷菇
        GRAVE_BUSTER = 11, // 墓碑吞噬者
        HYPNOSHROOM = 12,  // 魅惑菇
        SCAREDY_SHROOM = 13, // 胆小菇
        ICE_SHROOM = 14,   // 寒冰菇
        DOOM_SHROOM = 15,  // 毁灭菇
        LILY_PAD = 16,     // 荷叶
        SQUASH = 17,       // 窝瓜
        THREE_PEATER = 18, // 三线射手
        TANGLE_KELP = 19,  // 缠绕海草
        JALAPENO = 20,     // 火爆辣椒
        SPIKEWEED = 21,    // 地刺
        TORCHWOOD = 22,    // 火炬树桩
        TALL_NUT = 23,     // 高坚果
        SEA_SHROOM = 24,   // 海蘑菇
        PLANTERN = 25,     // 灯笼草
        CACTUS = 26,       // 仙人掌
        BLOVER = 27,       // 三叶草
        SPLIT_PEA = 28,    // 裂荚射手
        STARFRUIT = 29,    // 星星果
        PUMPKIN = 30,      // 南瓜头
        MAGNET_SHROOM = 31, // 磁力菇
        CABBAGE_PULT = 32, // 卷心菜投手
        FLOWER_POT = 33,   // 花盆
        KERNEL_PULT = 34,  // 玉米投手
        COFFEE_BEAN = 35,  // 咖啡豆
        GARLIC = 36,       // 大蒜
        UMBRELLA_LEAF = 37, // 叶子保护伞
        MARIGOLD = 38,     // 金盏花
        MELON_PULT = 39,   // 西瓜投手
        GATLING_PEA = 40,  // 机枪射手
        TWIN_SUNFLOWER = 41, // 双子向日葵
        GLOOM_SHROOM = 42, // 忧郁菇
        CATTAIL = 43,      // 猫尾草
        WINTER_MELON = 44, // 冰冻西瓜
        GOLD_MAGNET = 45,  // 吸金磁
        SPIKEROCK = 46,    // 地刺王
        COB_CANNON = 47,   // 玉米加农炮
        IMITATER = 48,     // 模仿者
        EXPLODE_O_NUT = 49, // 爆炸坚果
        GIANT_WALLNUT = 50, // 巨型坚果墙
        GLOOM_VINE = 51,   // 忧郁藤蔓
        ANTI_GRAVITY = 52, // 反重力豆
        HAY = 76,          // 干草
        CLOVER = 77,       // 四叶草
        STICKY_RICE = 78,  // 糯米
        INVERSE = 79,      // 逆向草

        // 特殊编码
        EMPTY = -1,        // 空位
        UNKNOWN = -2       // 未知
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
        int t;             // 特殊参数
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
        {CardCode::PEASHOOTER, "豌豆射手"},
        {CardCode::SUNFLOWER, "向日葵"},
        {CardCode::CHERRY_BOMB, "樱桃炸弹"},
        {CardCode::WALL_NUT, "坚果墙"},
        {CardCode::POTATO_MINE, "土豆雷"},
        {CardCode::SNOW_PEA, "寒冰射手"},
        {CardCode::CHOMPER, "大嘴花"},
        {CardCode::REPEATER, "双发射手"},
        {CardCode::PUFF_SHROOM, "小喷菇"},
        {CardCode::SUN_SHROOM, "阳光菇"},
        {CardCode::FUME_SHROOM, "大喷菇"},
        {CardCode::GRAVE_BUSTER, "墓碑吞噬者"},
        {CardCode::HYPNOSHROOM, "魅惑菇"},
        {CardCode::SCAREDY_SHROOM, "胆小菇"},
        {CardCode::ICE_SHROOM, "寒冰菇"},
        {CardCode::DOOM_SHROOM, "毁灭菇"},
        {CardCode::LILY_PAD, "荷叶"},
        {CardCode::SQUASH, "窝瓜"},
        {CardCode::THREE_PEATER, "三线射手"},
        {CardCode::TANGLE_KELP, "缠绕海草"},
        {CardCode::JALAPENO, "火爆辣椒"},
        {CardCode::SPIKEWEED, "地刺"},
        {CardCode::TORCHWOOD, "火炬树桩"},
        {CardCode::TALL_NUT, "高坚果"},
        {CardCode::SEA_SHROOM, "海蘑菇"},
        {CardCode::PLANTERN, "灯笼草"},
        {CardCode::CACTUS, "仙人掌"},
        {CardCode::BLOVER, "三叶草"},
        {CardCode::SPLIT_PEA, "裂荚射手"},
        {CardCode::STARFRUIT, "星星果"},
        {CardCode::PUMPKIN, "南瓜头"},
        {CardCode::MAGNET_SHROOM, "磁力菇"},
        {CardCode::CABBAGE_PULT, "卷心菜投手"},
        {CardCode::FLOWER_POT, "花盆"},
        {CardCode::KERNEL_PULT, "玉米投手"},
        {CardCode::COFFEE_BEAN, "咖啡豆"},
        {CardCode::GARLIC, "大蒜"},
        {CardCode::UMBRELLA_LEAF, "叶子保护伞"},
        {CardCode::MARIGOLD, "金盏花"},
        {CardCode::MELON_PULT, "西瓜投手"},
        {CardCode::GATLING_PEA, "机枪射手"},
        {CardCode::TWIN_SUNFLOWER, "双子向日葵"},
        {CardCode::GLOOM_SHROOM, "忧郁菇"},
        {CardCode::CATTAIL, "猫尾草"},
        {CardCode::WINTER_MELON, "冰冻西瓜"},
        {CardCode::GOLD_MAGNET, "吸金磁"},
        {CardCode::SPIKEROCK, "地刺王"},
        {CardCode::COB_CANNON, "玉米加农炮"},
        {CardCode::IMITATER, "模仿者"},
        {CardCode::EXPLODE_O_NUT, "爆炸坚果"},
        {CardCode::GIANT_WALLNUT, "巨型坚果墙"},
        {CardCode::GLOOM_VINE, "忧郁藤蔓"},
        {CardCode::ANTI_GRAVITY, "反重力豆"},
        {CardCode::HAY, "干草"},
        {CardCode::CLOVER, "四叶草"},
        {CardCode::STICKY_RICE, "糯米"},
        {CardCode::INVERSE, "逆向草"},
        {CardCode::EMPTY, "空"},
        {CardCode::UNKNOWN, "未知"}
    };

    // 卡片组数据库（基于题目数据）
    export class CardSetDatabase {
    private:
        std::vector<CardSet> sets;

        // 将索引转换为实际位置（处理跳跃）
        std::size_t index_to_position(int index) const {
            static const std::array<int, 57> position_map = {
                0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
                20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
                38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
                // 跳跃到 76-79
                53, 54, 55, 56
            };

            if (index >= 0 && index <= 52) {
                return index;
            }
            else if (index >= 76 && index <= 79) {
                return 53 + (index - 76);
            }
            throw std::out_of_range(std::format("无效的卡片索引: {}", index));
        }

    public:
        CardSetDatabase() {
            initialize_sets();
        }

        void initialize_sets() {
            // S0 组
            sets.push_back({
                0, "S0",
                {"豌豆射手", "空", "空", "坚果墙", "土豆雷", "寒冰射手", "大嘴花", "双发射手",
                 "小喷菇", "空", "大喷菇", "空", "魅惑菇", "胆小菇", "空", "空", "荷叶", "窝瓜",
                 "三线射手", "空", "空", "地刺", "火炬树桩", "高坚果", "海蘑菇", "空", "仙人掌",
                 "空", "裂荚射手", "星星果", "南瓜头", "磁力菇", "卷心菜投手", "花盆", "玉米投手",
                 "空", "大蒜", "叶子保护伞", "空", "西瓜投手", "机枪射手", "空", "忧郁菇", "猫尾草",
                 "冰冻西瓜", "空", "地刺王", "空", "空", "空", "空", "空", "空", "空", "空", "空", "空"}
                });

            // S1 组
            sets.push_back({
                1, "S1",
                {"豌豆射手", "空", "空", "坚果墙", "土豆雷", "寒冰射手", "大嘴花", "双发射手",
                 "小喷菇", "空", "大喷菇", "空", "魅惑菇", "胆小菇", "空", "空", "荷叶", "窝瓜",
                 "三线射手", "空", "空", "空", "火炬树桩", "高坚果", "海蘑菇", "空", "仙人掌",
                 "空", "裂荚射手", "星星果", "南瓜头", "磁力菇", "卷心菜投手", "花盆", "玉米投手",
                 "空", "大蒜", "叶子保护伞", "空", "西瓜投手", "机枪射手", "空", "忧郁菇", "猫尾草",
                 "冰冻西瓜", "空", "地刺王", "空", "空", "空", "空", "空", "空", "空", "空", "空"}
                });

            // S2 组
            sets.push_back({
                2, "S2",
                {"豌豆射手", "空", "空", "坚果墙", "空", "寒冰射手", "大嘴花", "双发射手",
                 "空", "空", "大喷菇", "空", "魅惑菇", "胆小菇", "空", "空", "荷叶", "空",
                 "三线射手", "空", "空", "空", "火炬树桩", "高坚果", "空", "空", "仙人掌",
                 "空", "裂荚射手", "星星果", "南瓜头", "磁力菇", "卷心菜投手", "花盆", "玉米投手",
                 "空", "大蒜", "叶子保护伞", "空", "西瓜投手", "机枪射手", "空", "忧郁菇", "猫尾草",
                 "冰冻西瓜", "空", "地刺王", "空", "空", "空", "空", "空", "空", "空", "空", "空"}
                });

            // S3 组
            sets.push_back({
                3, "S3",
                {"豌豆射手", "机枪射手", "空", "坚果墙", "空", "寒冰射手", "大嘴花", "双发射手",
                 "小喷菇", "空", "大喷菇", "空", "魅惑菇", "胆小菇", "空", "空", "荷叶", "空",
                 "三线射手", "空", "空", "空", "火炬树桩", "高坚果", "海蘑菇", "空", "仙人掌",
                 "空", "裂荚射手", "星星果", "南瓜头", "磁力菇", "卷心菜投手", "花盆", "玉米投手",
                 "空", "大蒜", "叶子保护伞", "空", "西瓜投手", "机枪射手", "空", "忧郁菇", "猫尾草",
                 "冰冻西瓜", "空", "地刺王", "空", "空", "空", "空", "空", "空", "空", "空", "空"}
                });

            // S4 组
            sets.push_back({
                4, "S4",
                {"豌豆射手", "机枪射手", "空", "坚果墙", "空", "寒冰射手", "大嘴花", "双发射手",
                 "小喷菇", "空", "大喷菇", "空", "魅惑菇", "胆小菇", "空", "空", "荷叶", "空",
                 "三线射手", "空", "空", "空", "火炬树桩", "高坚果", "海蘑菇", "灯笼草", "仙人掌",
                 "空", "裂荚射手", "星星果", "南瓜头", "磁力菇", "卷心菜投手", "花盆", "玉米投手",
                 "空", "大蒜", "叶子保护伞", "金盏花", "西瓜投手", "机枪射手", "空", "忧郁菇", "猫尾草",
                 "冰冻西瓜", "吸金磁", "地刺王", "空", "空", "爆炸坚果", "空", "空", "空", "空", "空", "空"}
                });

            // S5 组
            sets.push_back({
                5, "S5",
                {"豌豆射手", "机枪射手", "空", "坚果墙", "土豆雷", "寒冰射手", "大嘴花", "双发射手",
                 "小喷菇", "空", "大喷菇", "空", "魅惑菇", "胆小菇", "分裂豆", "空", "荷叶", "空",
                 "三线射手", "空", "空", "空", "火炬树桩", "高坚果", "海蘑菇", "灯笼草", "仙人掌",
                 "三叶草", "裂荚射手", "星星果", "南瓜头", "磁力菇", "卷心菜投手", "花盆", "玉米投手",
                 "空", "大蒜", "叶子保护伞", "金盏花", "西瓜投手", "机枪射手", "空", "忧郁菇", "猫尾草",
                 "冰冻西瓜", "吸金磁", "地刺王", "空", "空", "爆炸坚果", "空", "空", "空", "空", "空", "空"}
                });

            // S6 组
            sets.push_back({
                6, "S6",
                {"豌豆射手", "机枪射手", "空", "坚果墙", "土豆雷", "寒冰射手", "大嘴花", "双发射手",
                 "小喷菇", "阳光菇", "大喷菇", "空", "魅惑菇", "胆小菇", "分裂豆", "空", "水晶兰", "窝瓜",
                 "三线射手", "缠绕海草", "空", "空", "火炬树桩", "高坚果", "海蘑菇", "灯笼草", "仙人掌",
                 "三叶草", "裂荚射手", "星星果", "空", "磁力菇", "卷心菜投手", "空", "玉米投手",
                 "空", "大蒜", "叶子保护伞", "金盏花", "西瓜投手", "机枪射手", "空", "忧郁菇", "猫尾草",
                 "冰冻西瓜", "吸金磁", "地刺王", "空", "空", "爆炸坚果", "空", "忧郁藤蔓", "反重力豆", "干草", "糯米", "逆向草"}
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
            return CardCode::UNKNOWN;
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
                    output.card_codes[i] = CardCode::UNKNOWN;
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