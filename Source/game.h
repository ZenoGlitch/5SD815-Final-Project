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

struct PlayerData // TODO: Get rid of this
{
	std::string name{""};
	int score { 0 };
};

struct Game
{
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
	Vector2 cornerPos { 0.0f, player.player_base_height };
	float offset;

	int score { 0 };

	static const int barrierCount { 5 };

	float shootTimer { 0 };

	bool newHighScore { false };

	void Start();
	void End() noexcept;

	void Continue();

	void Update();
	void RenderStartScreen() noexcept;
	void RenderUI() noexcept;
	void Render() noexcept;

	void SpawnBarriers();
	void SpawnAliens();
	void SpawnPlayerBeams();

	void AliensShooting();

	void HandleEnemyBeamCollision() noexcept;
	void HandlePlayerBeamCollision() noexcept;
	void HandleAllBeamCollisions() noexcept;
	bool CheckNewHighScore() const noexcept;

	void InsertNewHighScore(std::string name);

	void SaveLeaderboard();

	void RemoveDeadEntities() noexcept;

	bool ShouldGameEnd() noexcept;
	
	//TODO: Create a separate class for Leaderboard
	//TODO: use string and/or string_view to handle text
	char name[9 + 1] = "\0";      //One extra space required for null terminator char '\0'
	int letterCount = 0;

	std::string name2 = "";
	Rectangle textBox = { 600, 500, 225, 50 };
	bool mouseOnText = false;

	int framesCounter = 0;

};