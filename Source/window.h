#pragma once

#include "raylib.h"
#include <string>
#include <assert.h>

constexpr static int screenWidth = 1920;
constexpr static int screenHeight = 1080;
constexpr static std::string_view APP_NAME = "SPACE INVADERS";

struct Window
{
	Window(int screen_width, int screen_height, std::string_view title) noexcept
	{
		InitWindow(screen_width, screen_height, title.data());
		SetTargetFPS(60);
	}
	
	Window() noexcept : Window(screenWidth, screenHeight, APP_NAME)
	{
		SetTargetFPS(60);
	}

	Window(const Window& other) noexcept = delete;
	Window& operator=(const Window& other) noexcept = delete;
	Window(Window&& other) = delete;
	Window& operator=(Window&& other) = delete;

	~Window() noexcept 
	{
		CloseWindow();
	}

	bool ShouldClose() const noexcept
	{
		return WindowShouldClose();
	}
};