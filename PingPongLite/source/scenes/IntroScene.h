#pragma once
#include "core/subsystems/FontHandler.h"
#include "entities/Board/Board.h"
#include "entities/Collectibles/subclasses/BlueStar.h"
#include "entities/Collectibles/subclasses/Potion.h"
#include "entities/Collectibles/subclasses/RedStar.h"
#include "entities/Paddle/Paddle.h"
#include "scenes/Scene.h"
#include <string.h>

class IntroScene : public Scene
{
  public:
	virtual void run() override;

  private:
	virtual void update() override;
	virtual void render() override;

	virtual void init() override;
	virtual void close() override;

	void renderCooldown();
	void renderNotes();

	SDL_FPoint boardSize = {1280.f, 720.f};
	// Object positions
	struct
	{
	  private:
		const float screenX = 1280;
		const float screenY = 720;
		const float halfX = screenX / 2;
		const float halfY = screenY / 2;

		struct
		{
			const float collectiblesCenter = -250.f;
			const float paddleEdge = 50.f;
			const float collectiblesBetween = 70.f;

			const float collectiblesRight = 300.f;
			const float paddleTop = 100.f;
			const float paddleLeft = 100.f;

		} offsets;

	  public:
		SDL_FPoint board = {halfX, halfY};

		SDL_FPoint computer = {offsets.paddleEdge, halfY};
		SDL_FPoint player = {screenX - offsets.paddleEdge, halfY};

		SDL_FPoint potion = {halfX + offsets.collectiblesCenter, halfY - offsets.collectiblesBetween};
		SDL_FPoint blueStar = {halfX + offsets.collectiblesCenter, halfY};
		SDL_FPoint redStar = {halfX + offsets.collectiblesCenter, halfY + offsets.collectiblesBetween};

		// Text
		SDL_FPoint textCooldown = {halfX, 100.f};
		SDL_FPoint textPosion = {potion.x + offsets.collectiblesRight, potion.y};
		SDL_FPoint textRedStar = {redStar.x + offsets.collectiblesRight, redStar.y};
		SDL_FPoint textBlueStar = {blueStar.x + offsets.collectiblesRight, blueStar.y};

		SDL_FPoint textPlayer = {player.x - offsets.paddleLeft, player.y - offsets.paddleTop};
		SDL_FPoint textComputer = {computer.x + offsets.paddleLeft, computer.y - offsets.paddleTop};

	} objectPositions;

	struct
	{
		SDL_Color orange = SDL_Color(215, 121, 82);
		SDL_Color blue = SDL_Color(82, 124, 215);
		SDL_Color grey = SDL_Color(211, 211, 211);
	} colors;

	struct
	{
		const char* player = "This is YOU";
		const char* computer = "This is Computer";
		const char* posion = "swaps paddles strategies <=>";
		const char* redStar = "adds to your score (+)";
		const char* blueStar = "adds to enemy score (-)";
	} notes;

	float sceneLifetime = 15.f;

	std::shared_ptr<Paddle> computer, player;
	std::shared_ptr<Board> board;
	std::shared_ptr<Collectible> potion;
	std::shared_ptr<Collectible> redStar;
	std::shared_ptr<Collectible> blueStar;
};
