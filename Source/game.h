#pragma once
#include "raylib.h"
#include "Resources.h"
#include "player.h"
#include "projectile.h"
#include "alien.h"
#include "barrier.h"
#include <vector>
#include <string>


enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};

struct PlayerData
{
	std::string name{};
	int score{0};
};

// TODO: Should star be part of background or should it be its own class?
struct Star
{
	Vector2 initPosition = { 0, 0 };
	Vector2 position = { 0, 0 };
	Color color { GRAY };
	float size { 0 };
	void Update(float starOffset);
	void Render();
};

// TODO: Break out Background into its own class
struct Background
{
	std::vector<Star> Stars;

	void Initialize(int starAmount);
	void Update(float offset);
	void Render();
};

struct Game
{
	// Gamestate
	State gameState { State::STARTSCREEN };	
	Resources resources;
	Background background;
	Player player;
	std::vector<Projectile> playerBeams;
	std::vector<Projectile> enemyBeams;
	std::vector<Barrier> Barriers;
	std::vector<Alien> Aliens;
	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };

	Vector2 alienPos;
	Vector2 cornerPos;
	float offset;

	int score { 0 };

	const int barrierCount { 5 };

	float shootTimer { 0 };

	bool newHighScore { false };

	void Start();
	void End() noexcept;

	void Continue();

	void Update();
	void RenderStartScreen();
	void RenderUI();
	void Render();

	void SpawnBarriers();
	void SpawnAliens();

	void HandleEnemyBeamCollision() noexcept;
	void HandlePlayerBeamCollision() noexcept;
	void HandleAllCollisions() noexcept;
	bool CheckNewHighScore() const noexcept;

	void InsertNewHighScore(std::string name);

	void SaveLeaderboard();

	void RemoveDeadEntities() noexcept;

	bool ShouldGameEnd() noexcept;


	//TEXTBOX ENTER
	char name[9 + 1] = "\0";      //One extra space required for null terminator char '\0'
	int letterCount = 0;

	Rectangle textBox = { 600, 500, 225, 50 };
	bool mouseOnText = false;

	int framesCounter = 0;

};