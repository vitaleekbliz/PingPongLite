#include "PaddlePlayerStrategy.h"

void PaddlePlayerStrategy::track(SDL_FPoint* ownerPos)
{
	float deltaTime = SDLHandler::get().getTick();
	float mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	float distanceToMouse = mouseY - ownerPos->y;
	float moveAmount = deltaTime * currentSpeed;
	if (moveAmount > std::abs(distanceToMouse))
	{
		ownerPos->y = mouseY;
	}
	else
	{
		ownerPos->y += (distanceToMouse > 0 ? 1 : -1) * moveAmount;
	}

	keepInBounds(ownerPos);

	// TODO remove debug
#if defined(_DEBUG) && 0
	ownerPos->x = mouseX;
	ownerPos->y = mouseY;
#endif // _DEBUG
}
