#include "background.h"

void Star::Update(float starOffset) noexcept
{
	position.x = initPositionX + starOffset;
}

void Star::Render() noexcept
{
	DrawCircleV(position, size, SKYBLUE);
}

Background::Background(const int starAmount)
{
	Stars.reserve(starAmount);
	for (int i = 0; i < starAmount; i++)
	{
		constexpr int screen_offset = 150;
		const int initPosX = GetRandomValue(-screen_offset, GetScreenWidth() + screen_offset);
		const Vector2 pos = { initPosX, GetRandomValueF(0, GetScreenHeight()) };
		const float size = GetRandomValueF(1, 4) / 2;

		Stars.emplace_back(initPosX, pos, size);
	}
}

void Background::Update(float offset) noexcept
{
	for (auto& star : Stars)
	{
		star.Update(offset);
	}
}

void Background::Render() noexcept
{
	for (auto& star : Stars)
	{
		star.Render();
	}
}