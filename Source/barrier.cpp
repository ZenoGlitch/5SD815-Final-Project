#include "barrier.h"

void Barrier::Render(Texture2D texture) noexcept
{
	constexpr float texture_offset = 100.0f;
	DrawTexture(texture, position.x - texture_offset, position.y - texture_offset, WHITE);

	constexpr float text_offset_x = 21.0f;
	constexpr float text_offset_y = 10.0f;
	constexpr float font_size = 40.0f;
	DrawText(TextFormat("%i", health), position.x - text_offset_x, position.y + text_offset_y, font_size, RED);
}

bool Barrier::IsAlive() const noexcept
{
	if (health > 0)
	{
		return true;
	}
	return false;
}