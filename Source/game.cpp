#include "game.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>

static bool is_dead(const auto& entity) noexcept 
{
	return !entity.IsAlive();
}

static float lineLength(Vector2 A, Vector2 B) noexcept //Uses pythagoras to calculate the length of a line
{
	return std::sqrtf(std::powf(B.x - A.x, 2) + std::powf(B.y - A.y, 2));
}

void Game::Start()
{
	SpawnBarriers();
	SpawnAliens();
	score = 0;
	player.Reset();
	gameState = State::GAMEPLAY;
}

void Game::End() noexcept
{
	playerBeams.clear();
	enemyBeams.clear();
	Barriers.clear();
	Aliens.clear();
	newHighScore = CheckNewHighScore();
	gameState = State::ENDSCREEN;
}

void Game::Continue()
{
	SaveLeaderboard();
	gameState = State::STARTSCREEN;
}

void Game::Update()
{
	switch (gameState)
	{
	case State::STARTSCREEN:
		if (IsKeyReleased(KEY_SPACE))
		{
			Start();
		}
		break;

	case State::GAMEPLAY:
		if (ShouldGameEnd())
		{
			End();
		}

		player.Update();
		
		for (auto& alien : Aliens)
		{
			alien.Update();
		}

		SpawnAliens();

		offset = lineLength(player.position, cornerPos) * -1;
		background.Update(offset / 15);

		for (auto& eBeam : enemyBeams)
		{
			eBeam.Update();
		}

		for (auto& pBeam : playerBeams)
		{
			pBeam.Update();
		}

		HandleAllBeamCollisions();

		if (IsKeyPressed(KEY_SPACE))
		{
			SpawnPlayerBeams();
		}

		AliensShooting();

		RemoveDeadEntities();
		break;

	case State::ENDSCREEN:

		if (IsKeyReleased(KEY_ENTER) && !newHighScore)
		{
			Continue();
		}

		if (newHighScore)
		{
			if (CheckCollisionPointRec(GetMousePosition(), textBox))
			{
				mouseOnText = true;
			}
			else
			{
				mouseOnText = false;
			}

			if (mouseOnText)
			{
				SetMouseCursor(MOUSE_CURSOR_IBEAM);

				int key = GetCharPressed();

				// Check if more characters have been pressed on the same frame
				while (key > 0)
				{
					// NOTE: Only allow keys in range [32..125]
					if ((key >= 32) && (key <= 125) && (letterCount < 9))
					{
						name[letterCount] = static_cast<char>(key);
						name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
						letterCount++;
					}

					key = GetCharPressed();  // Check next character in the queue
				}

				//Remove chars 
				if (IsKeyPressed(KEY_BACKSPACE))
				{
					letterCount--;
					if (letterCount < 0) letterCount = 0;
					name[letterCount] = '\0';
				}
			}
			else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

			if (mouseOnText)
			{
				framesCounter++;
			}
			else
			{
				framesCounter = 0;
			}

			// If the name is right legth and enter is pressed, exit screen by setting highscore to false and add 
			// name + score to scoreboard
			if (letterCount > 0 && letterCount < 9 && IsKeyReleased(KEY_ENTER))
			{
				std::string nameEntry(name);

				InsertNewHighScore(nameEntry);

				newHighScore = false;
			}
		}

		break;
	default:
		//SHOULD NOT HAPPEN
		break;
	}
}

const void Game::RenderStartScreen() const noexcept
{
	constexpr int posX { 200 };
	constexpr int titlePosY { 100 };
	constexpr int titleFontSize { 160 };
	DrawText("SPACE INVADERS", posX, titlePosY, titleFontSize, YELLOW);

	constexpr int promptPosY { 350 };
	constexpr int promptFontSize { 40 };
	DrawText("PRESS SPACE TO BEGIN", posX, promptPosY, promptFontSize, YELLOW);
}

const void Game::RenderUI() const noexcept
{
	constexpr int fontSize { 40 };
	constexpr int linePosX { 50 };
	constexpr int firstLinePosY { 20 };
	constexpr int secondLinePosY { 70 };
	DrawText(TextFormat("Score: %i", score), linePosX, firstLinePosY, fontSize, YELLOW);
	DrawText(TextFormat("Lives: %i", player.lives), linePosX, secondLinePosY, fontSize, YELLOW);
}

const void Game::Render() const noexcept
{
	BeginDrawing();
	ClearBackground(BLACK);

	switch (gameState)
	{
	case State::STARTSCREEN:
		RenderStartScreen();

		break;

	case State::GAMEPLAY:

		background.Render();

		RenderUI();

		player.Render(resources.shipTextures[player.activeTexture].get());

		for (auto& eBeam : enemyBeams)
		{
			eBeam.Render(getTexture(resources.laserTexture));
		}

		for (auto& pBeam : playerBeams)
		{
			pBeam.Render(getTexture(resources.laserTexture));
		}

		for (auto& barrier : Barriers)
		{
			barrier.Render(getTexture(resources.barrierTexture));
		}

		for (auto& alien : Aliens)
		{
			alien.Render(getTexture(resources.alienTexture));
		}

		break;

	case State::ENDSCREEN:

		if (newHighScore)
		{
			DrawText("NEW HIGHSCORE!", 600, 300, 60, YELLOW);

			// BELOW CODE IS FOR NAME INPUT RENDER
			DrawText("PLACE MOUSE OVER INPUT BOX!", 600, 400, 20, YELLOW);

			DrawRectangleRec(textBox, LIGHTGRAY);
			if (mouseOnText)
			{
				// HOVER CONFIRMIATION
				DrawRectangleLinesEx(textBox, 1.0f, RED);
			}
			else
			{
				DrawRectangleLinesEx(textBox, 1.0f, DARKGRAY);
			}

			//Draw the name being typed out
			DrawText(name, static_cast<int>(textBox.x + 5), static_cast<int>(textBox.y + 8), 40, MAROON);

			//Draw the text explaining how many characters are used
			DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, 600, 20, YELLOW);

			

			if (mouseOnText)
			{
				if (letterCount < 9)
				{
					// Draw blinking underscore char
					if (((framesCounter / 20) % 2) == 0)
					{
						const int fontSize = 40;
						DrawText("_", static_cast<int>(textBox.x + 8 + MeasureText(name, fontSize)), static_cast<int>(textBox.y + 12), fontSize, MAROON);
					}
				}
				else
				{
					//Name needs to be shorter
					DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
				}
			}

			// Explain how to continue when name is input
			if (letterCount > 0 && letterCount < 9)
			{
				DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
			}
		}
		else {
			// If no highscore or name is entered, show scoreboard and call it a day
			DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);

			DrawText("LEADERBOARD", 50, 100, 40, YELLOW);

			for (int i = 0; i < Leaderboard.size(); i++)
			{
				const char* tempNameDisplay = Leaderboard.at(i).name.data(); //TODO: Don't use char*, use string_view instead. Also breaking the Law of Demeter
				DrawText(tempNameDisplay, 50, 140 + (i * 40), 40, YELLOW);
				DrawText(TextFormat("%i", Leaderboard.at(i).score), 350, 140 + (i * 40), 40, YELLOW);
			}
		}

		break;

	default:
		//SHOULD NOT HAPPEN
		break;
	}

	EndDrawing();
}

void Game::SpawnBarriers()
{
	const float barrier_distance = GetScreenWidthF() / (barrierCount + 1.0f);
	const float barrier_y_pos = GetScreenHeightF() - barrier_offset_from_screen;
	
	Barriers.reserve(barrierCount);
	for (int i = 0; i < barrierCount; i++)
	{
		Vector2 spawnPos{ barrier_distance * (i + 1), barrier_y_pos };
		Barriers.emplace_back(spawnPos);
	}
}

void Game::SpawnAliens()
{
	if (Aliens.empty())
	{
		Aliens.reserve(static_cast<int>(formationHeight * formationWidth));
		for (int row = 0; row < formationHeight; row++)
		{
			for (int col = 0; col < formationWidth; col++)
			{
				const Vector2 spawnPos{ formationX + (col * alienSpacing), formationY + (row * alienSpacing) };
				Aliens.emplace_back(spawnPos);
			}
		}
	}
}

void Game::SpawnPlayerBeams()
{
	const Vector2 spawnPosition{ player.position.x + player_radius / 2,player.position.y - projectile_height };
	constexpr int speed = 15;
	playerBeams.push_back(Projectile(spawnPosition, speed));
}

void Game::AliensShooting() //TODO: simplify?
{
	shootTimer += 1;
	if (shootTimer > 60 && !Aliens.empty())
	{
		const int randomAlienIndex = std::rand() % Aliens.size(); //TODO: Seed random

		Vector2 spawnPosition = Aliens.at(randomAlienIndex).position; //TODO: Breaking the Law of Demeter
		constexpr int speed = -15;

		enemyBeams.emplace_back(spawnPosition, speed);
		shootTimer = 0;
	}
}

void Game::HandleEnemyBeamCollision() noexcept
{
	for (auto& enemyBeam : enemyBeams)
	{
		for (auto& barrier : Barriers)
		{
			if (CheckCollisionCircleRec(barrier.position, barrier_radius, enemyBeam.rect))
			{
				enemyBeam.active = false;
				barrier.health -= 1;
			}
		}

		if (CheckCollisionCircleRec(player.position, player_radius, enemyBeam.rect))
		{
			enemyBeam.active = false;
			player.lives -= 1;
		}
	}
}

void Game::HandlePlayerBeamCollision() noexcept
{
	for (auto& playerBeam : playerBeams)
	{
		for (auto& barrier : Barriers)
		{
			if (CheckCollisionCircleRec(barrier.position, barrier_radius, playerBeam.rect))
			{
				playerBeam.active = false;
				barrier.health -= 1;
			}
		}

		for (auto& alien : Aliens)
		{
			if (CheckCollisionCircleRec(alien.position, alien_radius, playerBeam.rect))
			{
				playerBeam.active = false;
				alien.active = false;
				score += 100;
			}
		}
	}
}

void Game::HandleAllBeamCollisions() noexcept
{
	HandleEnemyBeamCollision();

	HandlePlayerBeamCollision();
}

bool Game::CheckNewHighScore() const noexcept
{
	return (score > Leaderboard.back().score);
}

void Game::InsertNewHighScore(std::string p_name) // future problems
{
	PlayerData newData;
	newData.name = p_name;
	newData.score = score;

	for (int i = 0; i < Leaderboard.size(); i++)
	{
		if (newData.score > Leaderboard.at(i).score) //TODO: Could we use find_if and swap instead?
		{ 
			Leaderboard.insert(Leaderboard.begin() + i, newData);

			Leaderboard.pop_back();

			return;
		}
	}
}

void Game::SaveLeaderboard() //TODO: This is obviously not fully implemented, fix or remove..!
{
	std::fstream file;

	file.open("Leaderboard"); //TODO: Add an actual file and the correct path

	if (!file)
	{
		std::cout << "file not found \n";
	}
	else
	{
		std::cout << "file found \n";
	}
}

void Game::RemoveDeadEntities() noexcept
{
	std::erase_if(playerBeams, is_dead<Projectile>);
	std::erase_if(enemyBeams, is_dead<Projectile>);
	std::erase_if(Aliens, is_dead<Alien>);
	std::erase_if(Barriers, is_dead<Barrier>);
}

bool Game::ShouldGameEnd() noexcept
{
	if (IsKeyReleased(KEY_Q))
	{
		return true;
	}
	if (player.lives < 1)
	{
		return true;
	}
	for (auto& alien : Aliens)
	{
		if (alien.position.y > GetScreenHeightF() - player.player_base_height)
		{
			return true;
		}
	}
	return false;
}