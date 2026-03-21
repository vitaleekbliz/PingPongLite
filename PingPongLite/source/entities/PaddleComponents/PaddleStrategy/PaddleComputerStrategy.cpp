#include "PaddleComputerStrategy.h"

void PaddleComputerStrategy::track(SDL_FPoint* ownerPos)
{
	auto objectLock = trackedObject.lock();
	if (!objectLock)
		return;

	SDL_FPoint objPosition = objectLock->getPosition();

	float deltaTime = SDLHandler::get().getTick();

	float ballY = objPosition.y;

	float deltaY = ballY - ownerPos->y;

	float moveAmount = deltaTime * currentSpeed;

	if (moveAmount > std::abs(deltaY))
	{
		ownerPos->y = objPosition.y;
	}
	else
	{
		ownerPos->y += (deltaY > 0 ? 1 : -1) * moveAmount;
	}

	keepInBounds(ownerPos);
}
