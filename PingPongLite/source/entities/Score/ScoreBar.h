#pragma once
#include "components/ScoreDecorator.h"
#include "components/TimeDecorator.h"
#include "core/SDLHandler.h";
#include "entities/Object.h"
#include "entities/interfaces/BoundaryObserver/BoundarySubscriber.h"
#include "entities/interfaces/ChangeScoreObserver/ChangeScoreSubscriber.h"
#include "entities/interfaces/StrategyObserver/StrategySubscriber.h"

class ScoreBar : public Object, public BoundarySubscriber, public StrategySubscriber, public ChangeScoreSubscriber
{
  public:
	ScoreBar();
	void update() override;
	void render() override;
	virtual void onBoundaryEvent(BOUNDARY event) override;
	virtual void onStrategyChange() override;

	virtual void onAddScore(int value, bool computer) override;

  private:
	std::shared_ptr<ScoreDecorator> computerScore;
	std::shared_ptr<ScoreDecorator> playerScore;

	bool scoreSwapped = false;

	TimeDecorator time;
};
