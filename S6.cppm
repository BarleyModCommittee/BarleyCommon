export module BarleyCommon:S6;

import index;
import :Def;
import <array>;
import <string_view>;
import <optional>;

using std::array;
using std::optional;
using std::string_view;

namespace SeedType
{
	using Type2 = SeedType;
	inline constexpr Type2 SpringEquinoxVine = Type2(0x4C);
	inline constexpr Type2 NetherShroom = Type2(0x4D);
	inline constexpr Type2 Mangosteen = Type2(0x4E);
	inline constexpr Type2 ThymeWarp = Type2(0x4F);
}

export namespace BarleyCommon::S6
{
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
		Resistance
	};
}

namespace BarleyCommon::S6
{
	constexpr array<SeedType::SeedType, static_cast<size_t>(CardCode::Last)> SeedTypeMap =
	{
		SeedType::None,			SeedType::None,			SeedType::Wallnut,		SeedType::PotatoMine,
								SeedType::SnowPea,		SeedType::Chomper,		SeedType::Repeater,

		SeedType::Puffshroom,	SeedType::Sunshroom,	SeedType::Fumeshroom,
		SeedType::Hypnoshroom,	SeedType::Scaredyshroom,SeedType::Iceshroom,

		SeedType::None,			SeedType::Squash,		SeedType::Threepeater,	SeedType::TangleKelp,
														SeedType::Torchwood,	SeedType::Tallnut,

		SeedType::Seashroom,	SeedType::Plantern,		SeedType::Cactus,		SeedType::Blover,
		SeedType::SplitPea,		SeedType::Starfruit,	SeedType::None,			SeedType::Magnetshroom,

		SeedType::Cabbagepult,	SeedType::None,			SeedType::Kernelpult,
		SeedType::Garlic,		SeedType::UmbrellaLeaf, SeedType::Marigold,		SeedType::Melonpult,

		SeedType::GatlingPea,							SeedType::Gloomshroom,	SeedType::Cattail,
		SeedType::WinterMelon,	SeedType::GoldMagnet,	SeedType::Spikerock,

		SeedType::Explodenut,	SeedType::Sprout,		SeedType::LeftRepeater,	SeedType::Sunflower,

		SeedType::Peashooter,	SeedType::LilyPad,		SeedType::SpringEquinoxVine,	SeedType::NetherShroom,
		SeedType::Mangosteen,	SeedType::ThymeWarp
	};

	constexpr array<RoleType, static_cast<size_t>(CardCode::Last)> RoleTypeMap =
	{
		RoleType::None,			RoleType::None,			RoleType::Durable,		RoleType::CarryTypeA,
								RoleType::Disabler,		RoleType::Durable,		RoleType::CarryTypeB,

		RoleType::CarryTypeB,	RoleType::CarryTypeA,	RoleType::CarryTypeA,
		RoleType::Resistance,	RoleType::CarryTypeB,	RoleType::Support,

		RoleType::None,			RoleType::CarryTypeB,	RoleType::CarryTypeB,	RoleType::Disabler,
														RoleType::Support,		RoleType::Durable,

		RoleType::CarryTypeB,	RoleType::Support,		RoleType::Durable,		RoleType::Support,
		RoleType::CarryTypeB,	RoleType::CarryTypeB,	RoleType::None,			RoleType::Resistance,

		RoleType::CarryTypeB,	RoleType::None,			RoleType::Disabler,
		RoleType::Durable,		RoleType::Resistance,	RoleType::Support,		RoleType::CarryTypeA,

		RoleType::CarryTypeA,							RoleType::CarryTypeA,	RoleType::CarryTypeB,
		RoleType::Disabler,		RoleType::Support,		RoleType::Durable,

		RoleType::Durable,		RoleType::CarryTypeB,	RoleType::CarryTypeB,	RoleType::None,

		RoleType::Resistance,	RoleType::CarryTypeB,	RoleType::Support,		RoleType::CarryTypeB,
		RoleType::CarryTypeB,	RoleType::Resistance
	};
}

export namespace BarleyCommon::S6
{
	CardCode SeedType2Code(const SeedType::SeedType &type)
	{
		for (int i = 0; i < static_cast<int>(CardCode::Last); i++)
			if (SeedTypeMap[i] == type)
				return static_cast<CardCode>(i);

		if (type == SeedType::None)
			return CardCode::Nil;
		return CardCode::Unknown;
	}

	optional<SeedType::SeedType> getType(const CardCode code)
	{
		if (code >= static_cast<CardCode>(0) && code < CardCode::Last)
			return SeedTypeMap[static_cast<int>(code)];

		switch (code)
		{
		case CardCode::Nil:
			return SeedType::None;
		default:
			return std::nullopt;
		}
	}

	optional<RoleType> getRole(const CardCode code)
	{
		if (code >= static_cast<CardCode>(0) && code < CardCode::Last)
			return RoleTypeMap[static_cast<int>(code)];

		switch (code)
		{
		case CardCode::Nil:
			return RoleType::None;
		default:
			return std::nullopt;
		}
	}
}