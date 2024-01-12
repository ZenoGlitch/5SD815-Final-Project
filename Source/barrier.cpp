#include "barrier.h"

const void Barrier::Render(Texture2D texture) const noexcept
{
	constexpr float texture_offset = 100.0f;
	DrawTextureV(texture, { position.x - texture_offset, position.y - texture_offset }, WHITE);

	constexpr float text_offset_x{ 21.0f };
	constexpr float text_offset_y { 10.0f };
	constexpr int font_size { 40 };
	DrawText(TextFormat("%i", health), static_cast<int>(position.x - text_offset_x), static_cast<int>(position.y + text_offset_y), font_size, RED);
}

bool Barrier::IsAlive() const noexcept
{
	if (health > 0)
	{
		return true;
	}
	return false;
}