export module BarleyCommon:Def;

import :Index;

export namespace BarleyCommon
{
	/// @enum CardCode
	/// @brief 卡片编码定义
	enum class CardCode : int
	{
		/// @brief 豌豆射手
		PeaShooter,
		/// @brief 向日葵
		Sunflower,
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
		/// @brief 冰川菇
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
		/// @brief 南瓜壳
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
		/// @brief 猫尾草
		Cattail,
		/// @brief 冰瓜
		WinterMelon,
		/// @brief 吸金磁
		GoldMagnet,
		/// @brief 地刺王
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

	enum class RoleType : uint8_t
	{
		None = 0,
		/// @brief Ⅰ 类输出
		CarryTypeA,
		/// @brief Ⅱ 类输出
		CarryTypeB,
		/// @brief 控制
		Disabler,
		/// @brief 辅助
		Support,
		/// @brief 前排
		Durable,
		/// @brief 抗性
		Resistance,
	};
}

namespace BarleyCommon
{
	enum class SeedType : int
	{
		None = -1,
		Peashooter = 0,
		Sunflower = 1,
		CherryBomb = 2,
		Wallnut = 3,
		PotatoMine = 4,
		SnowPea = 5,
		Chomper = 6,
		Repeater = 7,
		Puffshroom = 8,
		Sunshroom = 9,
		Fumeshroom = 10,
		GraveBuster = 11,
		Hypnoshroom = 12,
		Scaredyshroom = 13,
		Iceshroom = 14,
		Doomshroom = 15,
		LilyPad = 16,
		Squash = 17,
		Threepeater = 18,
		TangleKelp = 19,
		Jalapeno = 20,
		Spickweed = 21,
		Torchwood = 22,
		Tallnut = 23,
		Seashroom = 24,
		Plantern = 25,
		Cactus = 26,
		Blover = 27,
		SplitPea = 28,
		Starfruit = 29,
		Pumpkin = 30,
		Magnetshroom = 31,
		Cabbagepult = 32,
		FlowerPot = 33,
		Kernelpult = 34,
		CoffeeBean = 35,
		Garlic = 36,
		UmbrellaLeaf = 37,
		Marigold = 38,
		Melonpult = 39,
		GatlingPea = 40,
		TwinSunflower = 41,
		Gloomshroom = 42,
		Cattail = 43,
		WinterMelon = 44,
		GoldMagnet = 45,
		Spikerock = 46,
		CobCannon = 47,
		Imitater = 48,
		Explodenut = 49,
		GiantWallnut = 50,
		Sprout = 51,
		LeftRepeater = 52,
		SpringEquinoxVineS6 = 76,
		DarkShroomS6 = 77,
		MangosteenS6 = 78,
		ThymeWarpS6 = 79,
	};

	constexpr auto genCodeMap = []()
	{
		array<string_view, static_cast<size_t>(CardCode::Last)> map =
		{
		"豌", "葵", "坚", "雷", "寒", "嘴", "双",
		"小", "阳", "喷", "魅", "胆", "川", "莲",
		"窝", "三", "缠", "火", "高", "海", "灯",
		"掌", "叶", "裂", "星", "南", "磁", "卷",
		"盆", "玉", "蒜", "伞", "金", "瓜", "机",
		"曾", "猫", "冰", "吸", "刺", "爆", "飘",
		"反", "麦", "狙", "钻", "藤", "幽", "奶",
		"逆"
		};

		return map;
	};
	constexpr auto CodeMap = genCodeMap();
	constexpr array<string_view, static_cast<size_t>(CardCode::Last)> CodeNameMap =
	{
		"豌豆射手", "向日葵", "坚果墙", "土豆雷", "寒冰射手", "大嘴花", "双发射手",
		"小喷菇", "阳光菇", "大喷菇", "魅惑菇", "胆小菇", "冰川菇", "荷叶",
		"窝瓜", "三线射手", "缠绕海草", "火炬树桩", "高坚果", "海蘑菇", "路灯花",
		"仙人掌", "三叶草", "裂荚射手", "杨桃", "南瓜壳", "磁力菇", "卷心菜投手",
		"花盆", "玉米投手", "大蒜", "叶子保护伞", "金盏花", "西瓜投手", "机枪射手",
		"忧郁菇/忧郁南瓜", "猫尾草", "冰瓜", "吸金磁", "地刺王", "爆炸坚果", "火红莲",
		"反向双发", "大麦", "狙击豌豆", "晶钻菇", "春分藤", "幽冥菇", "奶山竹",
		"逆时草"
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
			if (CodeMap[i].compare(view) == 0)
				return static_cast<CardCode>(i);

		if (view.compare("空") == 0)
			return CardCode::Nil;
		if (view.compare("仙") == 0)
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
