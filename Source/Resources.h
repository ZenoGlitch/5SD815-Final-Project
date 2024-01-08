#pragma once
#include "raylib.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <format>

using namespace std::literals::string_view_literals;

struct MyTexture
{
	Texture2D tex;
	explicit MyTexture(std::string_view path)
	{
		tex = LoadTexture(path.data());
		if (tex.id <= 0)
		{
			throw(std::runtime_error(std::format("Unable to load texture: {}"sv, path)));
		}
	}

	MyTexture(const MyTexture& other) noexcept = delete;
	MyTexture& operator=(const MyTexture& other) noexcept = delete;

	MyTexture(MyTexture&& other) noexcept
	{
		std::swap(other.tex, tex);
	}
	MyTexture& operator=(MyTexture&& other) noexcept
	{
		std::swap(other.tex, tex);
		return *this;
	}

	~MyTexture()
	{
		UnloadTexture(tex);
	}

	const Texture2D& get() const noexcept
	{
		return tex;
	}


};

const Texture2D& getTexture(const MyTexture& t) noexcept;


class Resources
{
public:
	std::vector<MyTexture> shipTextures;

	Resources();


	MyTexture alienTexture = MyTexture("./Assets/Alien.png"sv);
	MyTexture barrierTexture = MyTexture("./Assets/Barrier.png"sv);
	MyTexture laserTexture = MyTexture("./Assets/Laser.png"sv);

};