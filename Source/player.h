#pragma once
#include "raylib.h"
#include "Resources.h"


constexpr static float player_radius { 50.0f };

class Player
{	
	constexpr static float speed { 7.0f };
	int direction { 0 };
	float timer { 0 };

public:
	constexpr static float player_base_height { 70.0f };

	int activeTexture { 0 };
	int lives { 3 };
	
	Vector2 position{ (GetScreenWidthF() / 2.0f), (GetScreenHeightF() - player_base_height) };
	void Update() noexcept;
	const void Render(Texture2D texture) const noexcept;
	void Reset() noexcept;
	bool IsAlive() const noexcept { return lives < 1; };

};