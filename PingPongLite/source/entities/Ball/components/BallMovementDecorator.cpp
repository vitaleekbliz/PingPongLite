#include "BallMovementDecorator.h"

void BallMovementDecorator::setRandomDirection()
{
	// TODO use boost libary to generate random angle
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

void BallMovementDecorator::onPaddleHit(SDL_FPoint* ballPos, SDL_FPoint ballSize, const SDL_FRect& paddleRect)
{
	// 1. force push ball outside the player collider
	float offset = paddleRect.w / 2 + ballSize.x / 2;
	offset *= (ballPos->x > paddleRect.x ? 1.f : -1.f);

	ballPos->x = paddleRect.x + offset;
	// 2. push ball from player center

	SDL_FPoint newDirection = SDL_FPoint();
	newDirection.x = ballPos->x - paddleRect.x;
	newDirection.y = ballPos->y - paddleRect.y;

	// normilize vector
	float length = std::sqrt(newDirection.x * newDirection.x + newDirection.y * newDirection.y);
	newDirection.x /= length;
	newDirection.y /= length;

	// Points to direction it should be moving
	direction = newDirection;

	accelerate();
}

void BallMovementDecorator::onWallHit()
{
	direction.y *= -1.f;
	clampVerticalVelocity();
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
	if (std::abs(direction.x) < 0.05)
		direction.x = 0.05; // Crutch points ball towards right slightly
	// PS. Paddle pushes the ball from its center, so its hard to hit ball perfectly horizontal

	// reduce angle to X axis
	direction.y /= verticalClampingFactor;
	direction.x *= verticalClampingFactor;

	// normalize vector
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	direction.x /= length;
	direction.y /= length;
}

void BallMovementDecorator::reset(SDL_FPoint* position)
{
	// move back to movement decorator after adding collision system
	*position = basePosition;
	setRandomDirection();
	currentSpeed = baseSpeed;
}