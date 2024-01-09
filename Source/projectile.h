#pragma once

#include "raylib.h"

constexpr static int projectile_width { 10 };
constexpr static int projectile_height { 50 };

class Projectile
{
	Vector2 position = { 0, 0 };
	int speed { 15 };

public:
	Projectile(Vector2 p_position, int p_speed) noexcept;

	void Update() noexcept;
	void Render(Texture2D texture) noexcept;
	Rectangle rect;
	bool active { true };
	bool IsAlive() const noexcept { return active; };
};