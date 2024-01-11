#include "alien.h"

void Alien::Update() noexcept
{
	if (moveRight)
	{
		position.x += alien_speed;

		if (position.x >= GetScreenWidthF())
		{
			moveRight = false;
			position.y += 50;
		}
	}
	else
	{
		position.x -= alien_speed;

		if (position.x <= 0)
		{
			moveRight = true;
			position.y += 50;
		}
	}
}

const void Alien::Render(Texture2D texture) noexcept
{
	DrawTexture(texture, position.x - alien_radius, position.y - alien_radius, WHITE);
}