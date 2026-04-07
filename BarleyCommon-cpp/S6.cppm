export module BarleyCommon:S6;

import :Def;
import <array>;
import <string_view>;
import <optional>;

using std::array;
using std::optional;
using std::string_view;

namespace BarleyCommon::S6
{
	constexpr array<SeedType, static_cast<size_t>(CardCode::Last)> SeedTypeMap =
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

		SeedType::Peashooter,	SeedType::LilyPad,		SeedType::SpringEquinoxVineS6,	SeedType::DarkShroomS6,
		SeedType::MangosteenS6,	SeedType::ThymeWarpS6
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

	constexpr size_t NotNullCodeCNT = []() constexpr
	{
		size_t cnt = 0;
		for (auto type : SeedTypeMap)
			if (type != SeedType::None)
				++cnt;
		return cnt;
	}();
}

export namespace BarleyCommon::S6
{
	constexpr auto ValidCodes = []() constexpr
	{
		std::array<CardCode, NotNullCodeCNT> result;
		size_t idx = 0;
		for (int i = 0; auto type : SeedTypeMap)
		{
			if (type != SeedType::None)
				result[idx++] = static_cast<CardCode>(i);
			i++;
		}
		return result;
	}();

	CardCode SeedType2Code(const SeedType &type)
	{
		for (int i = 0; i < static_cast<int>(CardCode::Last); i++)
			if (SeedTypeMap[i] == type)
				return static_cast<CardCode>(i);

		if (type == SeedType::None)
			return CardCode::Nil;
		return CardCode::Unknown;
	}

	optional<SeedType> getType(const CardCode code)
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