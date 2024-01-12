#include "player.h"

void Player::Update() noexcept
{
	direction = 0;
	if (IsKeyDown(KEY_LEFT))
	{
		direction--;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		direction++;
	}

	position.x += speed * direction;

	if (position.x < player_radius)
	{
		position.x = player_radius;
	}
	else if (position.x > GetScreenWidthF() - player_radius)
	{
		position.x = GetScreenWidthF() - player_radius;
	}

	timer += GetFrameTime();

	if (timer > 0.4 && activeTexture == 2) // TODO: make class that handles animations separately
	{
		activeTexture = 0;
		timer = 0;
	}
	else if (timer > 0.4)
	{
		activeTexture++;
		timer = 0;
	}
}

void Player::Render(Texture2D tex) const noexcept
{
	DrawTextureV(tex, { position.x - player_radius, position.y - player_radius }, WHITE);
}

void Player::Reset() noexcept
{
	lives = 3;
	position.x = (GetScreenWidthF() / 2.0f);
}