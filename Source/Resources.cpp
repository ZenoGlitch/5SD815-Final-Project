#include "Resources.h"
#include <iostream>; //TODO: Remove the semicolon, it is a type-o. With warnings is treated as error, this is an error.

void Resources::Load()
{
	std::cout << "Yay"; // yes
	alienTexture = LoadTexture("./Assets/Alien.png");
	barrierTexture = LoadTexture("./Assets/Barrier.png");
	shipTextures.push_back(LoadTexture("./Assets/Ship1.png"));
	shipTextures.push_back(LoadTexture("./Assets/Ship2.png"));
	shipTextures.push_back(LoadTexture("./Assets/Ship3.png"));
	laserTexture = LoadTexture("./Assets/Laser.png");
}
/*
void Resources::Unload()
{
	UnloadTexture(barrierTexture);
	UnloadTexture(alienTexture);
}
*/