#pragma once
#include "Object.h"
#include "core/SDLHandler.h";
#include "interfaces/ballObserver/BallSubscriber.h"

class ScoreBar : public Object, public BallSubscriber
{
  public:
	void update() override;
	void render() override;
	void onBallEvent(BallEvent event) override;

  private:
	float roundDurationSeconds = 0;
	int computerScore = 0;
	int playerScore = 0;

	struct UI
	{
	  public:
		SDL_FRect leftBar = {0, 0, 600, 40};
		SDL_FRect rightBar = {680, 2, 600, 40};
		SDL_FPoint scoreLeft = {300, 20};
		SDL_FPoint scoreRight = {1280 - 300, 20};
		SDL_FPoint time = {1280 / 2, 20};
	} ui;
};
