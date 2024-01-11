#pragma once
#include "raylib.h"
#include <vector>

static inline float GetRandomValueF(float min, float max) noexcept
{
	const int iMin{ static_cast<int>(min) };
	const int iMax{ static_cast<int>(max) };
	return static_cast<float>(GetRandomValue(iMin, iMax));
}

static inline float GetRandomValueF(int min, int max) noexcept
{
	return static_cast<float>(GetRandomValue(min, max));
}

struct Star
{
	Vector2 position { 0.0f, 0.0f };
	float size { 0.0f };
	void Render(float offset) noexcept;
};

struct Background
{
	static const int starAmount { 600 };
	float scrollingOffset{ 0.0f };

	std::vector<Star> Stars;

	explicit Background() noexcept;
	void Update(float offset) noexcept;
	const void Render() noexcept;
};