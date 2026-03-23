#pragma once
#include "components/ScoreDecorator.h"
#include "components/TimeDecorator.h"
#include "core/SDLHandler.h";
#include "entities/Object.h"
#include "entities/interfaces/BoundaryObserver/BoundarySubscriber.h"
#include "entities/interfaces/StrategyObserver/StrategySubscriber.h"

class ScoreBar : public Object, public BoundarySubscriber, public StrategySubscriber
{
  public:
	ScoreBar();
	void update() override;
	void render() override;
	virtual void onBoundaryEvent(BOUNDARY event) override;
	virtual void onStrategyChange() override;

  private:
	ScoreDecorator leftScore;
	ScoreDecorator rightScore;

	TimeDecorator time;
};
