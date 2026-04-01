#pragma once
#include "components/PaddleStrategy/PaddleComputerStrategy.h"
#include "components/PaddleStrategy/PaddlePlayerStrategy.h"
#include "core/subsystems/FontHandler.h"
#include "core/subsystems/TextureHandler.h"
#include "entities/Object.h"
#include "entities/interfaces/StrategyObserver/StrategySubscriber.h"
#include <memory>

class Paddle : public Object, public StrategySubscriber
{
  public:
	Paddle();
	void update() override;
	void render() override;

	void setOriginalStrategy(PADDLE_STRATEGY id, std::shared_ptr<Object> ball);
	virtual void onStrategyChange() override;

  private:
	void changeStrategy(PADDLE_STRATEGY id);

	std::weak_ptr<Object> trackingObject;
	PADDLE_STRATEGY currentStrategy = PADDLE_STRATEGY::COMPUTER;
	PADDLE_STRATEGY originalStrategy = PADDLE_STRATEGY::COMPUTER;

	std::shared_ptr<PaddleStrategy> strategy;
};
