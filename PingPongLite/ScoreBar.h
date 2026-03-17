#pragma once
#include "BallSubscriber.h"
#include "Object.h"

class ScoreBar : public Object, public BallSubscriber
{
  public:
	ScoreBar();
	void update() override;
	void render() override;
	void onBallEvent(BallEvent event) override;

  private:
	void drawTopBar();

	void changeScore(bool win);

	int roundDurationSeconds;
	int computerScore;
	int playerScore;
};
