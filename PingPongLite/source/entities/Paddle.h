#pragma once
#include "Object.h"
#include "PaddleComponents/PaddleStrategy/PaddleComputerStrategy.h"
#include "PaddleComponents/PaddleStrategy/PaddlePlayerStrategy.h"
#include "core/subsystems/FontHandler.h"
#include "core/subsystems/TextureHandler.h"
#include <memory>

class Paddle : public Object
{
  public:
	Paddle();
	void update() override;
	void render() override;

	void setOriginalStrategy(PADDLE_STRATEGY id, const SDL_FPoint* ballPos);
	void changeStrategy(PADDLE_STRATEGY id);

  private:
#pragma region Temp debug notification strategy swap
	const float cooldown = 15.f;
	float timer = cooldown;
	void DEBUG_handleControllerSwitch();
	void DEBUG_printWarning();
#pragma endregion

	const SDL_FPoint* ballPos = nullptr;
	PADDLE_STRATEGY currentStrategy;
	PADDLE_STRATEGY originalStrategy;

	std::shared_ptr<PaddleStrategy> strategy;
};
