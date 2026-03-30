#include "CollisionDetection.h"

void CollisionDetection::update()
{
	if (auto ballLock = ball.lock())
	{
		SDL_FRect ballCollider = ballLock->getCollider();
		resolvePaddleCollisions(ballCollider);
	}
}

void CollisionDetection::setBallRef(std::weak_ptr<Object> ball)
{
	this->ball = ball;
}

void CollisionDetection::addPaddles(std::weak_ptr<Object> paddleLeft, std::weak_ptr<Object> paddleRight)
{
	this->paddleLeft = paddleLeft;
	this->paddleRight = paddleRight;
}

void CollisionDetection::addCollectable(std::weak_ptr<Object> item)
{
	collectibles.push_back(item);
}

void CollisionDetection::notifyPaddleHit(const SDL_FRect& paddleCollider)
{
	for (auto it = paddleHitSubscribers.begin(); it != paddleHitSubscribers.end();)
	{
		if (auto lock = it->lock())
		{
			lock->onPaddleHit(paddleCollider);
			it++;
		}
		else
		{
			it = paddleHitSubscribers.erase(it);
		}
	}
}

void CollisionDetection::resolvePaddleCollisions(const SDL_FRect& ballCollider)
{

	bool leftPaddleCollision = checkForPaddleCollision(ballCollider, paddleLeft);
	bool rightPaddleCollision = checkForPaddleCollision(ballCollider, paddleRight);

	// if not colliding with both exited collision zone
	if (!leftPaddleCollision && !rightPaddleCollision)
	{
		isCollidingPaddle = false;
	}

	// if touching any paddle
	else if ((leftPaddleCollision || rightPaddleCollision) && !isCollidingPaddle)
	{

		// blocks logic untill exiting collision zone
		isCollidingPaddle = true;

		SDL_FRect collider =
			(leftPaddleCollision ? paddleLeft.lock()->getCollider() : paddleRight.lock()->getCollider());

		notifyPaddleHit(collider);
	}
}

bool CollisionDetection::checkForPaddleCollision(const SDL_FRect& ballCollider, std::weak_ptr<Object> paddle)
{
	if (auto paddleLock = paddle.lock())
	{
		SDL_FRect paddleCollider = paddleLock->getCollider();

		return checkCircleInsideBox(ballCollider, paddleCollider);
	}
	return false;
}

bool CollisionDetection::checkCircleInsideBox(const SDL_FRect& ball, const SDL_FRect& rect)
{
	// TODO calculate vector logic using boost qvm library
	SDL_FPoint circle = SDL_FPoint(ball.x, ball.y);

	SDL_FRect rectScreen = SDL_FRect(rect.x - rect.w / 2, rect.y - rect.h / 2, rect.w, rect.h);

	// return true if ball center is inside the rectagle or line is intersecting rectengle
	if (SDL_PointInRectFloat(&circle, &rectScreen))
	{
		return true;
	}

	SDL_FPoint& start = circle;

	// calculate vector 2d to the center of the square
	SDL_FPoint dirVector = {rect.x - start.x, rect.y - start.y};

	// normalize vector
	float length = sqrt(dirVector.x * dirVector.x + dirVector.y * dirVector.y);
	dirVector.x /= length;
	dirVector.y /= length;

	// get end pos of line
	float radius = ball.h / 2;

	dirVector.x *= radius;
	dirVector.y *= radius;

	SDL_FPoint end = {start.x + dirVector.x, start.y + dirVector.y};

	// Draw a line to rectangle and get intersaction
	return SDL_GetRectAndLineIntersectionFloat(&rectScreen, &start.x, &start.y, &end.x, &end.y);
}
