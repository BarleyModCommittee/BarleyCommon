-- BarleyCommon Lua 库
-- 由 generate.py 自动生成，请勿手动修改

local BarleyCommon = {}

-- CardCode 卡片编码
BarleyCommon.CardCode = {
	PeaShooter = 0,	-- 豌豆射手
	SunFlower = 1,	-- 向日葵
	WallNut = 2,	-- 坚果墙
	PotatoMine = 3,	-- 土豆雷
	SnowPea = 4,	-- 寒冰射手
	Chomper = 5,	-- 大嘴花
	Repeater = 6,	-- 双发射手
	PuffShroom = 7,	-- 小喷菇
	SunShroom = 8,	-- 阳光菇
	FumeShroom = 9,	-- 大喷菇
	HypnoShroom = 10,	-- 魅惑菇
	ScaredyShroom = 11,	-- 胆小菇
	IceShroom = 12,	-- 冰川菇
	LilyPad = 13,	-- 荷叶
	Squash = 14,	-- 窝瓜
	Threepeater = 15,	-- 三线射手
	TangleKelp = 16,	-- 缠绕海草
	Torchwood = 17,	-- 火炬树桩
	TallNut = 18,	-- 高坚果
	SeaShroom = 19,	-- 海蘑菇
	Plantern = 20,	-- 路灯花
	Cactus = 21,	-- 仙人掌
	Blover = 22,	-- 三叶草
	SplitPea = 23,	-- 裂荚射手
	Starfruit = 24,	-- 杨桃
	Pumpkin = 25,	-- 南瓜壳
	MagnetShroom = 26,	-- 磁力菇
	CabbagePult = 27,	-- 卷心菜投手
	FlowerPot = 28,	-- 花盆
	KernelPult = 29,	-- 玉米投手
	Garlic = 30,	-- 大蒜
	UmbrellaLeaf = 31,	-- 叶子保护伞
	Marigold = 32,	-- 金盏花
	MelonPult = 33,	-- 西瓜投手
	GatlingPea = 34,	-- 机枪射手
	GloomShroom = 35,	-- 忧郁菇/忧郁南瓜
	Cattail = 36,	-- 猫尾草
	WinterMelon = 37,	-- 冰瓜
	GoldMagnet = 38,	-- 吸金磁
	SpikeRock = 39,	-- 地刺王
	Explode_O_Nut = 40,	-- 爆炸坚果
	Endoflame = 41,	-- 火红莲
	LeftRepeater = 42,	-- 反向双发
	Barley = 43,	-- 大麦
	SniperShooter = 44,	-- 狙击豌豆
	DiamondShroom = 45,	-- 晶钻菇
	SpringEquinoxVine = 46,	-- 春分藤
	DarkShroom = 47,	-- 幽冥菇
	Mangosteen = 48,	-- 奶山竹
	ThymeWarp = 49,	-- 逆时草
	Last = 50,			-- 正常植物号码的总数

	Nil = -1,		-- 空位 表示该赛季不存在该植物
	Unknown = -2,		-- 未知 表示可能输入错误
}

-- RoleType 角色类型
BarleyCommon.RoleType = {
	None = 0,	-- 无
	CarryTypeA = 1,	-- Ⅰ 类输出
	CarryTypeB = 2,	-- Ⅱ 类输出
	Disabler = 3,	-- 控制
	Support = 4,	-- 辅助
	Durable = 5,	-- 前排
	Resistance = 6,	-- 抗性
}

-- SeedType 种子类型
BarleyCommon.SeedType = {
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
}

-- 短名称映射
BarleyCommon.CodeMap = {
	"豌", "葵", "坚", "雷", "寒", "嘴", "双",
	"小", "阳", "喷", "魅", "胆", "川", "莲",
	"窝", "三", "缠", "火", "高", "海", "灯",
	"掌", "叶", "裂", "星", "南", "磁", "卷",
	"盆", "玉", "蒜", "伞", "金", "瓜", "机",
	"曾", "猫", "冰", "吸", "刺", "爆", "飘",
	"反", "麦", "狙", "钻", "藤", "幽", "奶",
	"逆"
}

-- 全名映射
BarleyCommon.CodeNameMap = {
	"豌豆射手", "向日葵", "坚果墙", "土豆雷", "寒冰射手", "大嘴花", "双发射手",
	"小喷菇", "阳光菇", "大喷菇", "魅惑菇", "胆小菇", "冰川菇", "荷叶",
	"窝瓜", "三线射手", "缠绕海草", "火炬树桩", "高坚果", "海蘑菇", "路灯花",
	"仙人掌", "三叶草", "裂荚射手", "杨桃", "南瓜壳", "磁力菇", "卷心菜投手",
	"花盆", "玉米投手", "大蒜", "叶子保护伞", "金盏花", "西瓜投手", "机枪射手",
	"忧郁菇/忧郁南瓜", "猫尾草", "冰瓜", "吸金磁", "地刺王", "爆炸坚果", "火红莲",
	"反向双发", "大麦", "狙击豌豆", "晶钻菇", "春分藤", "幽冥菇", "奶山竹",
	"逆时草"
}

function BarleyCommon.toShortName(code)
    if code >= 0 and code < BarleyCommon.CardCode.Last then
        return BarleyCommon.CodeMap[code + 1]
    end
    if code == BarleyCommon.CardCode.Nil then
        return "空"
    end
    return "Invalid"
end

function BarleyCommon.ShortName2Code(view)
    for i = 0, BarleyCommon.CardCode.Last - 1 do
        if BarleyCommon.CodeMap[i + 1] == view then
            return i
        end
    end
    if view == "空" then
        return BarleyCommon.CardCode.Nil
    end
    if view == "仙" then
        return BarleyCommon.CardCode.Cactus
    end
    return BarleyCommon.CardCode.Unknown
end

function BarleyCommon.getName(code)
    if code >= 0 and code < BarleyCommon.CardCode.Last then
        return BarleyCommon.CodeNameMap[code + 1]
    end
    if code == BarleyCommon.CardCode.Nil then
        return "空"
    end
    return "Invalid"
end

-- S1 赛季数据
BarleyCommon.S1 = {}

BarleyCommon.S1.SeedTypeMap = {
	BarleyCommon.SeedType.Peashooter,
	BarleyCommon.SeedType.None,
	BarleyCommon.SeedType.Wallnut,
	BarleyCommon.SeedType.PotatoMine,
	BarleyCommon.SeedType.SnowPea,
	BarleyCommon.SeedType.Chomper,
	BarleyCommon.SeedType.Repeater,
	BarleyCommon.SeedType.Puffshroom,
	BarleyCommon.SeedType.None,
	BarleyCommon.SeedType.Fumeshroom,
	BarleyCommon.SeedType.Hypnoshroom,
	BarleyCommon.SeedType.Scaredyshroom,
	BarleyCommon.SeedType.Iceshroom,
	BarleyCommon.SeedType.LilyPad,
	BarleyCommon.SeedType.Squash,
	BarleyCommon.SeedType.Threepeater,
	BarleyCommon.SeedType.None,
	BarleyCommon.SeedType.Torchwood,
	BarleyCommon.SeedType.Tallnut,
	BarleyCommon.SeedType.Seashroom,
	BarleyCommon.SeedType.None,
	BarleyCommon.SeedType.Cactus,
	BarleyCommon.SeedType.None,
	BarleyCommon.SeedType.SplitPea,
	BarleyCommon.SeedType.Starfruit,
	BarleyCommon.SeedType.Pumpkin,
	BarleyCommon.SeedType.Magnetshroom,
	BarleyCommon.SeedType.Cabbagepult,
	BarleyCommon.SeedType.FlowerPot,
	BarleyCommon.SeedType.Kernelpult,
	BarleyCommon.SeedType.Garlic,
	BarleyCommon.SeedType.UmbrellaLeaf,
	BarleyCommon.SeedType.None,
	BarleyCommon.SeedType.Melonpult,
	BarleyCommon.SeedType.GatlingPea,
	BarleyCommon.SeedType.Gloomshroom,
	BarleyCommon.SeedType.Cattail,
	BarleyCommon.SeedType.WinterMelon,
	BarleyCommon.SeedType.None,
	BarleyCommon.SeedType.Spikerock,
	BarleyCommon.SeedType.Explodenut,
	BarleyCommon.SeedType.None,
	BarleyCommon.SeedType.None,
	BarleyCommon.SeedType.Sunflower,
	BarleyCommon.SeedType.None,
	BarleyCommon.SeedType.None,
	BarleyCommon.SeedType.None,
	BarleyCommon.SeedType.None,
	BarleyCommon.SeedType.None,
	BarleyCommon.SeedType.None,
}


function BarleyCommon.S1.SeedType2Code(type)
    for i = 0, #BarleyCommon.S1.SeedTypeMap do
        if BarleyCommon.S1.SeedTypeMap[i + 1] == type then
            return i
        end
    end
    if type == BarleyCommon.SeedType.None then
        return BarleyCommon.CardCode.Nil
    end
    return BarleyCommon.CardCode.Unknown
end

function BarleyCommon.S1.getType(code)
    if code >= 0 and code < BarleyCommon.CardCode.Last then
        return BarleyCommon.S1.SeedTypeMap[code + 1]
    end
    if code == BarleyCommon.CardCode.Nil then
        return BarleyCommon.SeedType.None
    end
    return nil
end


-- S6 赛季数据
BarleyCommon.S6 = {}

BarleyCommon.S6.SeedTypeMap = {
	BarleyCommon.SeedType.None,
	BarleyCommon.SeedType.None,
	BarleyCommon.SeedType.Wallnut,
	BarleyCommon.SeedType.PotatoMine,
	BarleyCommon.SeedType.SnowPea,
	BarleyCommon.SeedType.Chomper,
	BarleyCommon.SeedType.Repeater,
	BarleyCommon.SeedType.Puffshroom,
	BarleyCommon.SeedType.Sunshroom,
	BarleyCommon.SeedType.Fumeshroom,
	BarleyCommon.SeedType.Hypnoshroom,
	BarleyCommon.SeedType.Scaredyshroom,
	BarleyCommon.SeedType.Iceshroom,
	BarleyCommon.SeedType.None,
	BarleyCommon.SeedType.Squash,
	BarleyCommon.SeedType.Threepeater,
	BarleyCommon.SeedType.TangleKelp,
	BarleyCommon.SeedType.Torchwood,
	BarleyCommon.SeedType.Tallnut,
	BarleyCommon.SeedType.Seashroom,
	BarleyCommon.SeedType.Plantern,
	BarleyCommon.SeedType.Cactus,
	BarleyCommon.SeedType.Blover,
	BarleyCommon.SeedType.SplitPea,
	BarleyCommon.SeedType.Starfruit,
	BarleyCommon.SeedType.None,
	BarleyCommon.SeedType.Magnetshroom,
	BarleyCommon.SeedType.Cabbagepult,
	BarleyCommon.SeedType.None,
	BarleyCommon.SeedType.Kernelpult,
	BarleyCommon.SeedType.Garlic,
	BarleyCommon.SeedType.UmbrellaLeaf,
	BarleyCommon.SeedType.Marigold,
	BarleyCommon.SeedType.Melonpult,
	BarleyCommon.SeedType.GatlingPea,
	BarleyCommon.SeedType.Gloomshroom,
	BarleyCommon.SeedType.Cattail,
	BarleyCommon.SeedType.WinterMelon,
	BarleyCommon.SeedType.GoldMagnet,
	BarleyCommon.SeedType.Spikerock,
	BarleyCommon.SeedType.Explodenut,
	BarleyCommon.SeedType.Sprout,
	BarleyCommon.SeedType.LeftRepeater,
	BarleyCommon.SeedType.Sunflower,
	BarleyCommon.SeedType.Peashooter,
	BarleyCommon.SeedType.LilyPad,
	BarleyCommon.SeedType.SpringEquinoxVineS6,
	BarleyCommon.SeedType.DarkShroomS6,
	BarleyCommon.SeedType.MangosteenS6,
	BarleyCommon.SeedType.ThymeWarpS6,
}

BarleyCommon.S6.RoleTypeMap = {
	BarleyCommon.RoleType.None,
	BarleyCommon.RoleType.None,
	BarleyCommon.RoleType.Durable,
	BarleyCommon.RoleType.CarryTypeA,
	BarleyCommon.RoleType.Disabler,
	BarleyCommon.RoleType.Durable,
	BarleyCommon.RoleType.CarryTypeB,
	BarleyCommon.RoleType.CarryTypeB,
	BarleyCommon.RoleType.CarryTypeA,
	BarleyCommon.RoleType.CarryTypeA,
	BarleyCommon.RoleType.Resistance,
	BarleyCommon.RoleType.CarryTypeB,
	BarleyCommon.RoleType.Support,
	BarleyCommon.RoleType.None,
	BarleyCommon.RoleType.CarryTypeB,
	BarleyCommon.RoleType.CarryTypeB,
	BarleyCommon.RoleType.Disabler,
	BarleyCommon.RoleType.Support,
	BarleyCommon.RoleType.Durable,
	BarleyCommon.RoleType.CarryTypeB,
	BarleyCommon.RoleType.Support,
	BarleyCommon.RoleType.Durable,
	BarleyCommon.RoleType.Support,
	BarleyCommon.RoleType.CarryTypeB,
	BarleyCommon.RoleType.CarryTypeB,
	BarleyCommon.RoleType.None,
	BarleyCommon.RoleType.Resistance,
	BarleyCommon.RoleType.CarryTypeB,
	BarleyCommon.RoleType.None,
	BarleyCommon.RoleType.Disabler,
	BarleyCommon.RoleType.Durable,
	BarleyCommon.RoleType.Resistance,
	BarleyCommon.RoleType.Support,
	BarleyCommon.RoleType.CarryTypeA,
	BarleyCommon.RoleType.CarryTypeA,
	BarleyCommon.RoleType.CarryTypeA,
	BarleyCommon.RoleType.CarryTypeB,
	BarleyCommon.RoleType.Disabler,
	BarleyCommon.RoleType.Support,
	BarleyCommon.RoleType.Durable,
	BarleyCommon.RoleType.Durable,
	BarleyCommon.RoleType.CarryTypeB,
	BarleyCommon.RoleType.CarryTypeB,
	BarleyCommon.RoleType.None,
	BarleyCommon.RoleType.Resistance,
	BarleyCommon.RoleType.CarryTypeB,
	BarleyCommon.RoleType.Support,
	BarleyCommon.RoleType.CarryTypeB,
	BarleyCommon.RoleType.CarryTypeB,
	BarleyCommon.RoleType.Resistance,
}

function BarleyCommon.S6.SeedType2Code(type)
    for i = 0, #BarleyCommon.S6.SeedTypeMap do
        if BarleyCommon.S6.SeedTypeMap[i + 1] == type then
            return i
        end
    end
    if type == BarleyCommon.SeedType.None then
        return BarleyCommon.CardCode.Nil
    end
    return BarleyCommon.CardCode.Unknown
end

function BarleyCommon.S6.getType(code)
    if code >= 0 and code < BarleyCommon.CardCode.Last then
        return BarleyCommon.S6.SeedTypeMap[code + 1]
    end
    if code == BarleyCommon.CardCode.Nil then
        return BarleyCommon.SeedType.None
    end
    return nil
end

function BarleyCommon.S6.getRole(code)
    if code >= 0 and code < BarleyCommon.CardCode.Last then
        return BarleyCommon.S6.RoleTypeMap[code + 1]
    end
    if code == BarleyCommon.CardCode.Nil then
        return BarleyCommon.RoleType.None
    end
    return nil
end


return BarleyCommon
