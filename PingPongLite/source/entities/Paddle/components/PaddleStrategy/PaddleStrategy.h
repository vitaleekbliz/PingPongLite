#pragma once
#include "core/SDLHandler.h"
#include "entities/Object.h"
#include <memory>

enum class PADDLE_STRATEGY : char
{
	PLAYER,
	COMPUTER
};

class PaddleStrategy
{
  public:
	virtual ~PaddleStrategy();
	virtual void track(SDL_FPoint* ownerPos) = 0;
	void setTarget(std::shared_ptr<Object> trackedObject);

  protected:
	void keepInBounds(SDL_FPoint* ownerPos);
	std::weak_ptr<Object> trackedObject;

	int baseSpeed = 500;
	int currentSpeed = baseSpeed;

	const int topBoundary = 100;
	const int bottomBoundary = 660;
};
