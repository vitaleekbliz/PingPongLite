#include "PaddleComputerStrategy.h"

void PaddleComputerStrategy::track(SDL_FPoint* ownerPos)
{
	if (!ballPos)
		return;

	float deltaTime = SDLHandler::get().getTick();

	float ballY = ballPos->y;

	float deltaY = ballY - ownerPos->y;

	float moveAmount = deltaTime * currentSpeed;

	if (moveAmount > std::abs(deltaY))
	{
		ownerPos->y = ballPos->y;
	}
	else
	{
		ownerPos->y += (deltaY > 0 ? 1 : -1) * moveAmount;
	}

	keepInBounds(ownerPos);
}
