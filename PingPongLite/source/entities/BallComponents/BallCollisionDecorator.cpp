#include "BallCollisionDecorator.h"

void BallCollisionDecorator::setPaddleReference(std::weak_ptr<Object> paddle)
{
	this->paddle = paddle;
}

SDL_FRect BallCollisionDecorator::getPaddleCollider()
{
	if (auto paddleLock = paddle.lock())
	{
		return paddleLock->getCollider();
	}
}

bool BallCollisionDecorator::checkForCollisions(SDL_FPoint* ballPos, SDL_FPoint* ballSize)
{
	auto paddleLock = paddle.lock();
	if (!paddleLock)
	{
		return false;
	}
	return checkCircleInsideBox(ballPos, ballSize, paddleLock->getCollider());
}

bool BallCollisionDecorator::checkCircleInsideBox(SDL_FPoint* pos, SDL_FPoint* size, SDL_FRect rect)
{
	// TODO calculate vector logic using boost qvm library

	// convert global position to screen position
	rect.x -= rect.w / 2;
	rect.y -= rect.h / 2;

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