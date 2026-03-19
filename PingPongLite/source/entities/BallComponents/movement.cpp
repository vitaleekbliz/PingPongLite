#include "Movement.h"

void Movement::setRandomDirection()
{
	// TODO use boost libary
	float& x = direction.x;
	float& y = direction.y;
	x = (std::rand() % 3) / 1.f - 1.f;
	y = (std::rand() % 3) / 1.f - 1.f;

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

void Movement::applyMovement(SDL_FPoint* pos)
{
	float deltaTime = SDLHandler::get().getTick();

	pos->x += deltaTime * currentSpeed * direction.x;
	pos->y += deltaTime * currentSpeed * direction.y;
}

void Movement::paddleHit(bool player)
{
	// Points to direction it should be moving
	direction.x = player ? -std::abs(direction.x) : std::abs(direction.x);
	accelerate();
}

BOUNDARY Movement::checkBoundaries(SDL_FPoint* pos)
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

void Movement::accelerate()
{
	currentSpeed *= speedMultiplier;
	if (currentSpeed > maxSpeed)
		currentSpeed = maxSpeed;
}
