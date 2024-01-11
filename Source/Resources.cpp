#include "Resources.h"


Resources::Resources()
{
	shipTextures.reserve(3);
	shipTextures.emplace_back("./Assets/Ship1.png"sv);
	shipTextures.emplace_back("./Assets/Ship2.png"sv);
	shipTextures.emplace_back("./Assets/Ship3.png"sv);
}

const Texture2D& getTexture(const MyTexture& t) noexcept
{
	return t.get();
}