#pragma once
#include "raylib.h"
#include "vector"

// TODO: Make into a proper RAII class to prevent leaking of resources
struct Resources 
{
	void Load();
	//void Unload();

	std::vector<Texture2D> shipTextures;
	Texture2D alienTexture;
	Texture2D barrierTexture;
	Texture2D laserTexture;

};