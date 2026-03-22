#pragma once
#include "Object.h"
#include "PaddleComponents/PaddleStrategy/PaddleComputerStrategy.h"
#include "PaddleComponents/PaddleStrategy/PaddlePlayerStrategy.h"
#include "core/subsystems/FontHandler.h"
#include "core/subsystems/TextureHandler.h"
#include "interfaces/StrategyObserver/StrategyPublisher.h"
#include <memory>

class Paddle : public Object, public StrategyPublisher
{
  public:
	Paddle();
	void update() override;
	void render() override;

	void setOriginalStrategy(PADDLE_STRATEGY id, std::shared_ptr<Object> ball);
	void changeStrategy(PADDLE_STRATEGY id);

	virtual void notifyStrategyChange() override;

  private:
#pragma region Temp debug notification strategy swap
	const float cooldown = 15.f;
	float timer = cooldown;
	void DEBUG_handleControllerSwitch();
	void DEBUG_printWarning();
#pragma endregion

	std::weak_ptr<Object> trackingObject;
	PADDLE_STRATEGY currentStrategy;
	PADDLE_STRATEGY originalStrategy;

	std::shared_ptr<PaddleStrategy> strategy;
};
