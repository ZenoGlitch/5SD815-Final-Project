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
	int initPositionX { 0 };
	Vector2 position { 0.0f, 0.0f };
	float size { 0.0f };
	void Update(float starOffset) noexcept;
	void Render() noexcept;
};

struct Background
{
	explicit Background(const int starAmount);
	Background(const Background& other) noexcept = delete;
	Background& operator=(const Background& other) noexcept = delete;
	Background(Background&& other) noexcept = delete;
	Background& operator=(Background&& other) noexcept = delete;
	~Background()
	{
		Stars.clear();
	}

	std::vector<Star> Stars;

	void Update(float offset) noexcept;
	void Render() noexcept;
};