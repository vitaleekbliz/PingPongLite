#include "PaddleStrategy.h"

void PaddleStrategy::setTarget(const SDL_FPoint* ballPos)
{
	this->ballPos = ballPos;
}

void PaddleStrategy::keepInBounds(SDL_FPoint* ownerPos)
{
	if (ownerPos->y < topBoundary)
	{
		ownerPos->y = topBoundary;
	}
	else if (ownerPos->y > bottomBoundary)
	{
		ownerPos->y = bottomBoundary;
	}
}
