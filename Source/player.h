#pragma once
#include "raylib.h"
#include "Resources.h"


constexpr static float player_radius = 50.0f;
class Player
{
	constexpr static float speed = 7.0f;
	int direction = 0;
	float timer = 0;

public:
	Player() noexcept;
	int activeTexture = 0;
	int lives = 3;
	float player_base_height = 70.0f;
	Vector2 position{ (GetScreenWidth() / 2.0f), (GetScreenHeight() - player_base_height) };
	void Render(Texture2D texture) noexcept;
	void Update() noexcept;

};