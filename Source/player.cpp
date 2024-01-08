#include "player.h"

Player::Player() noexcept
{

}

void Player::Render(Texture2D tex) noexcept
{
	constexpr float offset = 50.0f;
	DrawTexture(tex, position.x - offset, position.y - offset, WHITE);
}

void Player::Update() noexcept
{
	//Movement
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
	else if (position.x > GetScreenWidth() - player_radius)
	{
		position.x = GetScreenWidth() - player_radius;
	}


	//Determine frame for animation
	timer += GetFrameTime();

	if (timer > 0.4 && activeTexture == 2)
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