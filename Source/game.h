#pragma once
#include "raylib.h"
#include "Resources.h"
#include "player.h"
#include "projectile.h"
#include "alien.h"
#include <vector>
#include <string>


enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};

enum struct EntityType // TODO: Remove this struct, types can be handled with proper use of classes
{
	PLAYER,
	ENEMY,
	PLAYER_PROJECTILE,
	ENEMY_PROJECTILE
};

struct PlayerData
{
	std::string name;
	int score;
};

// TODO: Break out Wall into its own class
struct Wall 
{
public: 
	Vector2 position; 
	Rectangle rec; 
	bool active; 
	Color color; 
	int health = 50;
	int radius = 60;


	void Render(Texture2D texture); 
	void Update(); 
};


// TODO: Should star be part of background or should it be its own class?
struct Star
{
	Vector2 initPosition = { 0, 0 };
	Vector2 position = { 0, 0 };
	Color color = GRAY;
	float size = 0;
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
	State gameState = {};

	// Score
	int score;

	// for later, make a file where you can adjust the number of walls (config file) 
	int wallCount = 5;

	//Aliens shooting
	float shootTimer = 0;


	bool newHighScore = false;
	

	void Start();
	void End();

	void Continue();

	void Update();
	void Render();

	void SpawnAliens();

	void HandleAllCollisions() noexcept;
	bool CheckNewHighScore() noexcept;

	void InsertNewHighScore(std::string name);

	void SaveLeaderboard();

	void RemoveDeadEntities();

	Resources resources;

	Player player;

	std::vector<Projectile> playerBeams;
	std::vector<Projectile> enemyBeams;

	std::vector<Wall> Walls;

	std::vector<Alien> Aliens;

	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };
	
	Background background;

	Vector2 alienPos; 
	Vector2 cornerPos;
	float offset;



	//TEXTBOX ENTER
	char name[9 + 1] = "\0";      //One extra space required for null terminator char '\0'
	int letterCount = 0;

	Rectangle textBox = { 600, 500, 225, 50 };
	bool mouseOnText = false;

	int framesCounter = 0;

};