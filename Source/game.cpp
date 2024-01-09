#include "game.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>

bool is_dead(const auto& entity) noexcept 
{
	return !entity.active;
}

// MATH FUNCTIONS
float lineLength(Vector2 A, Vector2 B) //Uses pythagoras to calculate the length of a line
{
	const float length = static_cast<float>(sqrtf(static_cast<float>(pow(B.x - A.x, 2) + pow(B.y - A.y, 2))));

	return length;
}

void Game::Start()
{
	// creating walls 
	float window_width = (float)GetScreenWidth(); 
	float window_height = (float)GetScreenHeight(); 
	float wall_distance = window_width / (wallCount + 1); 
	for (int i = 0; i < wallCount; i++)
	{
		Wall newWalls;
		newWalls.position.y = window_height - 250; 
		newWalls.position.x = wall_distance * (i + 1); 

		Walls.push_back(newWalls); 

	}

	//creating aliens
	SpawnAliens();
	

	//creating background
	Background newBackground;
	newBackground.Initialize(600);
	background = newBackground;

	//reset score
	score = 0;

	gameState = State::GAMEPLAY;

}

void Game::End()
{
	//SAVE SCORE AND UPDATE SCOREBOARD
	playerBeams.clear();
	enemyBeams.clear();
	Walls.clear();
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
		//Code 
		if (IsKeyReleased(KEY_SPACE))
		{
			Start();
		}

		break;
	case State::GAMEPLAY:
		//Code
		if (IsKeyReleased(KEY_Q))
		{
			End();
		}

		//Update Player
		player.Update();
		
		//Update Aliens and Check if they are past player
		for (int i = 0; i < Aliens.size(); i++)
		{
			Aliens[i].Update(); 

			if (Aliens[i].position.y > GetScreenHeight() - player.player_base_height)
			{
				End();
			}
		}

		//End game if player dies
		if (player.lives < 1)
		{
			End();
		}

		//Spawn new aliens if aliens run out
		if (Aliens.size() < 1)
		{
			SpawnAliens();
		}


		// Update background with offset
		cornerPos = { 0.0f, player.player_base_height };
		offset = lineLength(player.position, cornerPos) * -1;
		background.Update(offset / 15);


		//UPDATE PROJECTILES
		for (auto& eBeam : enemyBeams)
		{
			eBeam.Update();
		}

		for (auto& pBeam : playerBeams)
		{
			pBeam.Update();
		}

		//UPDATE WALLS
		//for (int i = 0; i < Walls.size(); i++)
		//{
		//	Walls[i].Update();
		//}

		for (auto& wall : Walls)
		{
			wall.Update();
		}

		//CHECK ALL COLLISONS HERE
		HandleAllCollisions();

		//MAKE PROJECTILE
		if (IsKeyPressed(KEY_SPACE))
		{
			const Vector2 spawnPosition{ player.position.x + player_radius / 2,player.position.y - projectile_height };
			constexpr int speed = 15;
			playerBeams.push_back(Projectile(spawnPosition, speed));
		}

		//Aliens Shooting
		shootTimer += 1;
		if (shootTimer > 59) //once per second
		{
			int randomAlienIndex = 0;

			if (Aliens.size() > 1)
			{
				randomAlienIndex = rand() % Aliens.size();
			}

			Vector2 spawnPosition = Aliens[randomAlienIndex].position;
			spawnPosition.y += 40;
			constexpr int speed = -15;

			enemyBeams.push_back(Projectile(spawnPosition, speed));
			shootTimer = 0;
		}

		RemoveDeadEntities();
		break;

	case State::ENDSCREEN:
		//Code
	
		//Exit endscreen
		if (IsKeyReleased(KEY_ENTER) && !newHighScore)
		{
			Continue();
		}

	

		if (newHighScore)
		{
			if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
			else mouseOnText = false;

			if (mouseOnText)
			{
				// Set the window's cursor to the I-Beam
				SetMouseCursor(MOUSE_CURSOR_IBEAM);

				// Get char pressed on the queue
				int key = GetCharPressed();

				// Check if more characters have been pressed on the same frame
				while (key > 0)
				{
					// NOTE: Only allow keys in range [32..125]
					if ((key >= 32) && (key <= 125) && (letterCount < 9))
					{
						name[letterCount] = (char)key;
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


void Game::Render()
{
	switch (gameState)
	{
	case State::STARTSCREEN:
		//Code
		DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);

		DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);


		break;
	case State::GAMEPLAY:
		//Code


		//background render LEAVE THIS AT TOP
		background.Render();

		//DrawText("GAMEPLAY", 50, 30, 40, YELLOW);
		DrawText(TextFormat("Score: %i", score), 50, 20, 40, YELLOW);
		DrawText(TextFormat("Lives: %i", player.lives), 50, 70, 40, YELLOW);

		//player rendering 
		player.Render(resources.shipTextures[player.activeTexture].get());

		//projectile rendering
		for (auto& eBeam : enemyBeams)
		{
			eBeam.Render(getTexture(resources.laserTexture));
		}

		for (auto& pBeam : playerBeams)
		{
			pBeam.Render(getTexture(resources.laserTexture));
		}

		// wall rendering 
		for (auto& wall : Walls)
		{
			wall.Render(getTexture(resources.barrierTexture));
		}

		//alien rendering  
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
			DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

			//Draw the text explaining how many characters are used
			DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, 600, 20, YELLOW);

			if (mouseOnText)
			{
				if (letterCount < 9)
				{
					// Draw blinking underscore char
					if (((framesCounter / 20) % 2) == 0)
					{
						DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
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
				char* tempNameDisplay = Leaderboard[i].name.data();
				DrawText(tempNameDisplay, 50, 140 + (i * 40), 40, YELLOW);
				DrawText(TextFormat("%i", Leaderboard[i].score), 350, 140 + (i * 40), 40, YELLOW);
			}
		}

		break;

	default:
		//SHOULD NOT HAPPEN
		break;
	}
}

void Game::SpawnAliens()
{
	for (int row = 0; row < formationHeight; row++)
	{
		for (int col = 0; col < formationWidth; col++)
		{
			const Vector2 spawnPos{ formationX + 450 + (col * alienSpacing), formationY + (row * alienSpacing) };
			Aliens.push_back(Alien(spawnPos));
		}
	}
}

void Game::HandleAllCollisions() noexcept
{
	for (auto& enemyBeam : enemyBeams)
	{
		for (auto& wall : Walls)
		{
			if (CheckCollisionCircleRec(wall.position, wall.radius, enemyBeam.rect))
			{
				enemyBeam.active = false;
				wall.health -= 1;
			}
		}

		if (CheckCollisionCircleRec(player.position, player_radius, enemyBeam.rect))
		{
			enemyBeam.active = false;
			player.lives -= 1;
		}
	}

	for (auto& playerBeam : playerBeams)
	{
		for (auto& wall : Walls)
		{
			if (CheckCollisionCircleRec(wall.position, wall.radius, playerBeam.rect))
			{
				playerBeam.active = false;
				wall.health -= 1;
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

bool Game::CheckNewHighScore() noexcept
{
	if (score > Leaderboard[4].score)
	{
		return true;
	}

	return false;
}

void Game::InsertNewHighScore(std::string p_name)
{
	PlayerData newData;
	newData.name = p_name;
	newData.score = score;

	for (int i = 0; i < Leaderboard.size(); i++)
	{
		if (newData.score > Leaderboard[i].score)
		{
			Leaderboard.insert(Leaderboard.begin() + i, newData);

			Leaderboard.pop_back();

			return;
		}
	}
}

void Game::SaveLeaderboard()
{
	// SAVE LEADERBOARD AS ARRAY

	// OPEN FILE
	std::fstream file;

	file.open("Leaderboard");

	if (!file)
	{
		std::cout << "file not found \n";
	}
	else
	{
		std::cout << "file found \n";
	}
	// CLEAR FILE

	// WRITE ARRAY DATA INTO FILE

	// CLOSE FILE
}

void Game::RemoveDeadEntities()
{
	std::erase_if(playerBeams, is_dead<Projectile>);
	std::erase_if(enemyBeams, is_dead<Projectile>);
	std::erase_if(Aliens, is_dead<Alien>);
	std::erase_if(Walls, is_dead<Wall>);
}

void Wall::Render(Texture2D texture)
{
	DrawTexturePro(texture,
		{
			0,
			0,
			704,
			704,
		},
		{
			position.x,
			position.y,
			200,
			200,
		}, { 100 , 100 },
		0,
		WHITE);

	DrawText(TextFormat("%i", health), position.x-21, position.y+10, 40, RED);
	
}

void Wall::Update() 
{
	// set walls as inactive when out of health
	if (health < 1)
	{
		active = false;
	}
}

//BACKGROUND
void Star::Update(float starOffset)
{
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;

}

void Star::Render()
{
	DrawCircle((int)position.x, (int)position.y, size, color);
}


void Background::Initialize(int starAmount)
{
	for (int i = 0; i < starAmount; i++)
	{
		Star newStar;

		newStar.initPosition.x = GetRandomValue(-150, GetScreenWidth() + 150);
		newStar.initPosition.y = GetRandomValue(0, GetScreenHeight());
		
		//random color?
		newStar.color = SKYBLUE;

		newStar.size = GetRandomValue(1, 4) / 2;

		Stars.push_back(newStar);

	}
}

void Background::Update(float offset)
{
	for (int i = 0; i < Stars.size(); i++)
	{
		Stars[i].Update(offset);
	}
}

void Background::Render()
{
	for (int i = 0; i < Stars.size(); i++)
	{
		Stars[i].Render();
	}
}
