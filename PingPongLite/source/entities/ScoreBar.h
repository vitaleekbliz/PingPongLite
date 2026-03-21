#pragma once
#include "Object.h"
#include "ScoreComponents/ScoreDecorator.h"
#include "core/SDLHandler.h";
#include "interfaces/StrategyObserver/StrategySubscriber.h"
#include "interfaces/ballObserver/BallSubscriber.h"

class ScoreBar : public Object, public BallSubscriber, public StrategySubscriber
{
  public:
	ScoreBar();
	void update() override;
	void render() override;
	void onBallEvent(BallEvent event) override;
	void onStrategyChange();

	void setScoreDecoratorListeners(std::shared_ptr<TextureSubscriber> texture, std::shared_ptr<FontSubscriber> font);

  private:
	float roundDurationSeconds = 0;

	ScoreDecorator leftScore;
	ScoreDecorator rightScore;

	bool originalStrategy = true;

	SDL_FPoint timePos = {1280 / 2, 20};
};
