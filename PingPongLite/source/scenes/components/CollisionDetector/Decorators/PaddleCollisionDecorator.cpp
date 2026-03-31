#include "PaddleCollisionDecorator.h"

void PaddleCollisionDecorator::addPaddles(std::weak_ptr<Object> paddleLeft, std::weak_ptr<Object> paddleRight)
{
	this->paddleLeft = paddleLeft;
	this->paddleRight = paddleRight;
}

std::optional<SDL_FRect> PaddleCollisionDecorator::resolvePaddleCollisions(const SDL_FRect& ballCollider)
{

	bool leftPaddleCollision = checkForObjectCollision(ballCollider, paddleLeft);
	bool rightPaddleCollision = checkForObjectCollision(ballCollider, paddleRight);

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

		return std::make_optional<SDL_FRect>(collider);
	}

	return {};
}
