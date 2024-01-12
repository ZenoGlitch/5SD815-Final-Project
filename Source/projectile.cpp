#include "projectile.h"
#include "Resources.h"

Projectile::Projectile(Vector2 p_position, int p_speed) noexcept
	: speed(p_speed)
	, rect(Rectangle(p_position.x, p_position.y, projectile_width, projectile_height))
	, active(true)
{
}

const void Projectile::Render(Texture2D p_texture) const noexcept
{
	constexpr float offset = 25.0f;
	DrawTextureV(p_texture, { rect.x - offset, rect.y - offset }, WHITE);
}

void Projectile::Update() noexcept
{
	rect.y -= speed;

	if (rect.y < 0 || rect.y > GetScreenHeightF() + projectile_height)
	{
		active = false;
	}
}