#pragma once
#include "components/ScoreDecorator.h"
#include "components/TimeDecorator.h"
#include "core/SDLHandler.h";
#include "entities/Object.h"
#include "entities/interfaces/StrategyObserver/StrategySubscriber.h"
#include "entities/interfaces/ballObserver/BallSubscriber.h"

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
