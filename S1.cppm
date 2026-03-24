export module BarleyCommon:S1;

import :index;
import :Def;
import <array>;
import <string_view>;
import <optional>;

using std::array;
using std::optional;
using std::string_view;

namespace BarleyCommon::S1
{
	constexpr array<SeedType::SeedType, static_cast<size_t>(CardCode::Last)> SeedTypeMap =
	{
		SeedType::Peashooter,	SeedType::None,			SeedType::Wallnut,		SeedType::PotatoMine,
								SeedType::SnowPea,		SeedType::Chomper,		SeedType::Repeater,

		SeedType::Puffshroom,	SeedType::None,			SeedType::Fumeshroom,
		SeedType::Hypnoshroom,	SeedType::Scaredyshroom,SeedType::Iceshroom,

		SeedType::LilyPad,		SeedType::Squash,		SeedType::Threepeater,	SeedType::None,
														SeedType::Torchwood,	SeedType::Tallnut,

		SeedType::Seashroom,	SeedType::None,			SeedType::Cactus,		SeedType::None,
		SeedType::SplitPea,		SeedType::Starfruit,	SeedType::Pumpkin,		SeedType::Magnetshroom,

		SeedType::Cabbagepult,	SeedType::FlowerPot,	SeedType::Kernelpult,
		SeedType::Garlic,		SeedType::UmbrellaLeaf, SeedType::None,			SeedType::Melonpult,

		SeedType::GatlingPea,							SeedType::Gloomshroom,	SeedType::Cattail,
		SeedType::WinterMelon,	SeedType::None,			SeedType::Spikerock,

		SeedType::Explodenut,	SeedType::None,			SeedType::None,			SeedType::Sunflower,

		SeedType::None,			SeedType::None,			SeedType::None,			SeedType::None,
		SeedType::None,			SeedType::None
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

export namespace BarleyCommon::S1
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
}