#pragma once
#include "raylib.h"
#include "Resources.h"

constexpr static float alien_radius { 30.0f };
constexpr static int alien_speed { 2 };

constexpr static float formationWidth  { 8.0f };
constexpr static float formationHeight { 5.0f };
constexpr static float alienSpacing    { 80.0f };
constexpr static float formationX      { 550.0f };
constexpr static float formationY      { 50.0f };

class Alien
{
public:
	Vector2 position = { 0, 0 };

	bool active { true };
	bool moveRight { true };

	void Update() noexcept;
	void Render(Texture2D texture) noexcept;
	bool IsAlive() const noexcept { return active; };
};


