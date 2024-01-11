#pragma once
#include "raylib.h"
#include "Resources.h"
#include "player.h"
#include "projectile.h"
#include "alien.h"
#include "barrier.h"
#include "background.h"
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

struct Game
{
	// Gamestate
	State gameState { State::STARTSCREEN };	
	Resources resources;
	Background background{600};
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
	void RenderStartScreen() noexcept;
	void RenderUI() noexcept;
	void Render();

	void SpawnBarriers();
	void SpawnAliens();

	void AliensShooting();

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