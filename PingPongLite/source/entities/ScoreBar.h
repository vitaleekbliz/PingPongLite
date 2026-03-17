#pragma once
#include "Object.h"
#include "interfaces/ballObserver/BallSubscriber.h"

class ScoreBar : public Object, public BallSubscriber
{
  public:
	ScoreBar();
	void update() override;
	void render() override;
	void onBallEvent(BallEvent event) override;

  private:
	void setupTexture();

	void drawTopBar();

	void changeScore(bool win);

	int roundDurationSeconds = 0;
	int computerScore = 0;
	int playerScore = 0;

	const std::string textureName = "ScoreBar.png";
	const int width = 600;
	const int height = 40;
};
