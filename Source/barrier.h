#pragma once

#include "raylib.h"

constexpr static int barrier_radius = 60;
constexpr static float barrier_offset_from_screen = 250.0f;

struct Barrier
{
	Vector2 position {};
	
	int health { 50 };

	const void Render(Texture2D texture) noexcept;
	bool IsAlive() const noexcept;
};