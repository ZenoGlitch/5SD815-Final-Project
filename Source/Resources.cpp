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

//void Resources::Load()
//{
//	alienTexture = LoadTexture("./Assets/Alien.png");
//	barrierTexture = LoadTexture("./Assets/Barrier.png");
//	shipTextures.push_back(LoadTexture("./Assets/Ship1.png"));
//	shipTextures.push_back(LoadTexture("./Assets/Ship2.png"));
//	shipTextures.push_back(LoadTexture("./Assets/Ship3.png"));
//	laserTexture = LoadTexture("./Assets/Laser.png");
//}

/*
void Resources::Unload()
{
	UnloadTexture(barrierTexture);
	UnloadTexture(alienTexture);
}
*/