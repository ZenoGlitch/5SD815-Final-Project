#include "alien.h"

Alien::Alien(Vector2 p_position) noexcept : position(p_position), moveRight(true), active(true)
{

}

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

void Alien::Render(Texture2D texture) noexcept
{

	DrawTexture(texture, position.x - alien_radius, position.y - alien_radius, WHITE);
}