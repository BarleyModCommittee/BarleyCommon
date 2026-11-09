export module BarleyCommon:S7;

import :Index;
import :Def;

namespace BarleyCommon::S7
{
	constexpr array<SeedType, static_cast<size_t>(CardCode::Last)> SeedTypeMap =
	{
		SeedType::None,
		SeedType::Sunflower,
		SeedType::Wallnut,
		SeedType::PotatoMine,
		SeedType::SnowPea,
		SeedType::Chomper,
		SeedType::Repeater,
		SeedType::Puffshroom,
		SeedType::Sunshroom,
		SeedType::Fumeshroom,
		SeedType::Hypnoshroom,
		SeedType::Scaredyshroom,
		SeedType::Iceshroom,
		SeedType::None,
		SeedType::Squash,
		SeedType::Threepeater,
		SeedType::TangleKelp,
		SeedType::Torchwood,
		SeedType::Tallnut,
		SeedType::Seashroom,
		SeedType::Plantern,
		SeedType::Cactus,
		SeedType::Blover,
		SeedType::SplitPea,
		SeedType::Starfruit,
		SeedType::None,
		SeedType::Magnetshroom,
		SeedType::Cabbagepult,
		SeedType::None,
		SeedType::Kernelpult,
		SeedType::Garlic,
		SeedType::UmbrellaLeaf,
		SeedType::Marigold,
		SeedType::Melonpult,
		SeedType::GatlingPea,
		SeedType::Gloomshroom,
		SeedType::Cattail,
		SeedType::WinterMelon,
		SeedType::GoldMagnet,
		SeedType::Spikerock,
		SeedType::Explodenut,
		SeedType::Sprout,
		SeedType::LeftRepeater,
		SeedType::GiantWallnut,
		SeedType::Peashooter,
		SeedType::None,
		SeedType::None,
		SeedType::DarkShroom,
		SeedType::None,
		SeedType::ThymeWarp,
	};

	constexpr array<RoleType, static_cast<size_t>(CardCode::Last)> RoleTypeMap =
	{
		RoleType::None,
		RoleType::Support,
		RoleType::Durable,
		RoleType::CarryTypeA,
		RoleType::CarryTypeB,
		RoleType::Durable,
		RoleType::CarryTypeB,
		RoleType::CarryTypeB,
		RoleType::CarryTypeB,
		RoleType::CarryTypeA,
		RoleType::Resistance,
		RoleType::CarryTypeB,
		RoleType::Disabler,
		RoleType::None,
		RoleType::CarryTypeB,
		RoleType::CarryTypeB,
		RoleType::Disabler,
		RoleType::Support,
		RoleType::Durable,
		RoleType::CarryTypeB,
		RoleType::Support,
		RoleType::Durable,
		RoleType::Support,
		RoleType::CarryTypeB,
		RoleType::CarryTypeA,
		RoleType::None,
		RoleType::Resistance,
		RoleType::CarryTypeB,
		RoleType::None,
		RoleType::Disabler,
		RoleType::Durable,
		RoleType::Resistance,
		RoleType::Support,
		RoleType::CarryTypeA,
		RoleType::CarryTypeA,
		RoleType::CarryTypeA,
		RoleType::CarryTypeB,
		RoleType::CarryTypeA,
		RoleType::Support,
		RoleType::Durable,
		RoleType::Durable,
		RoleType::CarryTypeB,
		RoleType::CarryTypeB,
		RoleType::None,
		RoleType::Resistance,
		RoleType::None,
		RoleType::None,
		RoleType::CarryTypeB,
		RoleType::None,
		RoleType::Resistance,
	};
	constexpr size_t NotNullCodeCNT = 43;
}

export namespace BarleyCommon::S7
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
