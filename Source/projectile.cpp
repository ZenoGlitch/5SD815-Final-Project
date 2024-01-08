#include "projectile.h"

Projectile::Projectile(Vector2 p_position, int p_speed) noexcept
	: position(p_position)
	, speed(p_speed)
	, rect(Rectangle(p_position.x, p_position.y, 10, 50))
	, active(true)
{

}

void Projectile::Render(Texture2D p_texture) noexcept
{
	constexpr float offset = 25.0f;
	DrawTexture(p_texture, position.x - offset, position.y - offset, WHITE);
	/*DrawRectangleRec(rect, WHITE);*/
}

void Projectile::Update() noexcept
{
	position.y -= speed;

	rect.x = position.x;
	rect.y = position.y;

	if (position.y < 0 || position.y > 1500)
	{
		active = false;
	}
}