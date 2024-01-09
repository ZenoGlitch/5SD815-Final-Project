#pragma once

#include "raylib.h"

constexpr static int barrier_radius = 60;

struct Barrier
{
public:

	Vector2 position {};
	bool active { true };

	int health { 50 };

	void Render(Texture2D texture) noexcept;
	void Update() noexcept;
};