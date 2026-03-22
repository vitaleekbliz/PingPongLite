#pragma once
#include "Object.h"
#include "ScoreComponents/ScoreDecorator.h"
#include "ScoreComponents/TimeDecorator.h"
#include "core/SDLHandler.h";
#include "interfaces/StrategyObserver/StrategySubscriber.h"
#include "interfaces/ballObserver/BallSubscriber.h"

class ScoreBar : public Object, public BallSubscriber, public StrategySubscriber
{
  public:
	ScoreBar();
	void update() override;
	void render() override;
	virtual void onBallEvent(BallEvent event) override;
	virtual void onStrategyChange() override;

  private:
	ScoreDecorator leftScore;
	ScoreDecorator rightScore;

	TimeDecorator time;
};
