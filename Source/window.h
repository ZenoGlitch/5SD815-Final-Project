#pragma once

#include "raylib.h"
#include <string>

constexpr static int screenWidth = 1920;
constexpr static int screenHeight = 1080;

class Window
{
public:

	Window() noexcept
	{
		InitWindow(screenWidth, screenHeight, "SPACE INVADERS");
	}

	Window(int screen_widht, int screen_height, std::string_view title) noexcept
	{
		InitWindow(screen_widht, screen_height, title.data());
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