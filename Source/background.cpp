#include "background.h"

void Star::Render(float offset) noexcept
{
	const Vector2 offsetPos{ position.x + (offset / size) , position.y};
	DrawCircleV(offsetPos, size, SKYBLUE);
}

Background::Background() noexcept
{
	Stars.reserve(starAmount);
	for (int i = 0; i < starAmount; i++)
	{
		constexpr int screen_offset = 150;
		const Vector2 pos = { GetRandomValueF(-screen_offset, GetScreenWidth() + screen_offset), GetRandomValueF(0, GetScreenHeight()) };
		const float size = GetRandomValueF(1, 4) / 2;

		Stars.emplace_back(pos, size);
	}
}

void Background::Update(float offset) noexcept
{
	scrollingOffset = offset;
}

void Background::Render() noexcept
{
	for (auto& star : Stars)
	{
		star.Render(scrollingOffset);
	}
}