#include "PaddleStrategy.h"

void PaddleStrategy::setTarget(std::shared_ptr<Object> trackedObject)
{
	this->trackedObject = trackedObject;
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
