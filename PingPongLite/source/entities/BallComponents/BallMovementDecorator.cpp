#include "BallMovementDecorator.h"

void BallMovementDecorator::setRandomDirection()
{
	// TODO use boost libary
	float& x = direction.x;
	float& y = direction.y;
	x = ((std::rand() % 100) - 50.f) / 50.f;
	y = ((std::rand() % 100) - 50.f) / 50.f;

	// Fixed length < 0 bug
	if (std::abs(x) < 0.5f)
	{
		x = (x < 0) ? -0.5f : 0.5f;
	}

	float length = std::sqrt(x * x + y * y);

	if (length > 0.0f)
	{
		x /= length;
		y /= length;
	}
	else
	{
		x = -1;
		y = 0;
	}
}

void BallMovementDecorator::applyMovement(SDL_FPoint* pos)
{
	float deltaTime = SDLHandler::get().getTick();

	pos->x += deltaTime * currentSpeed * direction.x;
	pos->y += deltaTime * currentSpeed * direction.y;
}

void BallMovementDecorator::onPaddleHit(bool isPlayer, SDL_FPoint* ballPos, SDL_FRect* paddleRect)
{
	// push ball from player
	SDL_FPoint paddleCenter = SDL_FPoint();
	paddleCenter.x = paddleRect->x + paddleRect->w / 2;
	paddleCenter.y = paddleRect->y + paddleRect->h / 2;

	// TODO use qvm library for vector rotation
	//---segment start
	SDL_FPoint newDirection = SDL_FPoint();
	newDirection.x = ballPos->x - paddleCenter.x;
	newDirection.y = ballPos->y - paddleCenter.y;

	// normilize vector
	float length = std::sqrt(newDirection.x * newDirection.x + newDirection.y * newDirection.y);
	newDirection.x /= length;
	newDirection.y /= length;
	//---segment end

	// Points to direction it should be moving
	direction = newDirection;

	accelerate();
}

void BallMovementDecorator::onWallHit()
{
	clampVerticalVelocity();
}

BOUNDARY BallMovementDecorator::checkBoundaries(SDL_FPoint* pos)
{
	if (pos->y < topBoundary)
	{
		// push ball back to screen
		pos->y = topBoundary;
		direction.y *= -1.0f;
		return BOUNDARY::TOP;
	}
	else if (pos->y > bottomBoundary)
	{
		// push ball back to screen
		pos->y = bottomBoundary;
		direction.y *= -1.0f;
		return BOUNDARY::BOTTOM;
	}
	else if (pos->x <= leftBoundary)
	{
		return BOUNDARY::LEFT;
	}
	else if (pos->x >= rightBoundary)
	{
		return BOUNDARY::RIGHT;
	}

	return BOUNDARY::NONE;
}

void BallMovementDecorator::accelerate()
{
	currentSpeed *= speedMultiplier;
	if (currentSpeed > maxSpeed)
		currentSpeed = maxSpeed;
}

void BallMovementDecorator::clampVerticalVelocity()
{
	// if any axis velocity is zero ball is stuck on axis infinitely
	if (!direction.x)
		direction.x = 0.05f; // Crutch points ball towards right slightly
	// PS. Paddle pushes the ball from its center, so its hard to hit ball perfectly horizontal

	// change reduce angle to X axis
	direction.y /= verticalClampingFactor;
	direction.x *= verticalClampingFactor;

	// normalize vector
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	direction.x /= length;
	direction.y /= length;
}
