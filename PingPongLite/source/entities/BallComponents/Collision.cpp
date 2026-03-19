#include "Collision.h"

void Collision::setPlayerReference(std::weak_ptr<Object> player)
{
	playerObject = player;
}

void Collision::setComputerReference(std::weak_ptr<Object> computer)
{
	computerObject = computer;
}

COLLITION Collision::checkForCollisions(SDL_FPoint* pos, SDL_FPoint* size)
{
	// Player collision
	bool playerCollision = false;
	if (auto playerLock = playerObject.lock())
	{
		playerCollision = checkCircleInsideBox(pos, size, playerLock->getCollider());
	}

	// Computer collision
	bool computerCollision = false;
	if (auto computerLock = computerObject.lock())
	{
		computerCollision = checkCircleInsideBox(pos, size, computerLock->getCollider());
	}

	// if not colliding with both exited collision zone
	if (!playerCollision && !computerCollision)
	{
		isCollidingPaddle = false;
	}

	// if touching any paddle
	else if ((playerCollision || computerCollision) && !isCollidingPaddle)
	{

		// blocks logic untill exiting collision zone
		isCollidingPaddle = true;

		if (playerCollision)
			return COLLITION::PLAYER;
		else if (computerCollision)
			return COLLITION::COMPUTER;
	}

	return COLLITION::NONE;
}

bool Collision::checkCircleInsideBox(SDL_FPoint* pos, SDL_FPoint* size, const SDL_FRect rect)
{
	// TODO calculate vector logic using boost qvm library

	// return true if ball center is inside the rectagle or line is intersecting rectengle
	if (SDL_PointInRectFloat(pos, &rect))
	{
		return true;
	}

	// TODO use boost library for clean code
	SDL_FPoint start = *pos;

	SDL_FPoint rectCenter = {rect.x + rect.w / 2, rect.y + rect.h / 2};

	// calculate vector 2d to the center of the square
	SDL_FPoint dirVector = {rectCenter.x - start.x, rectCenter.y - start.y};

	// normalize vector
	float length = sqrt(dirVector.x * dirVector.x + dirVector.y * dirVector.y);
	dirVector.x /= length;
	dirVector.y /= length;

	// get end pos of line
	float radius = size->x / 2;

	dirVector.x *= radius;
	dirVector.y *= radius;

	SDL_FPoint end = {start.x + dirVector.x, start.y + dirVector.y};

	// Draw a line to rectangle and get intersaction
	return SDL_GetRectAndLineIntersectionFloat(&rect, &start.x, &start.y, &end.x, &end.y);
}