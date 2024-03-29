#include "background.h"

const void Star::Render(float offset) const noexcept
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

const void Background::Render() const noexcept
{
	for (auto& star : Stars)
	{
		star.Render(scrollingOffset);
	}
}