#pragma once 
#include <iostream>
#include <string>
#include <fstream>

// TODO: Remove this entire class, not used anywhere in the application

struct Entity
{
	float x, y;

	void LoadLevelFromAFile(const std::string& filename);
};