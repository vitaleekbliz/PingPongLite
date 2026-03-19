#include "Ball.h"

Ball::Ball()
{
	size.x = 30;
	size.y = 30;

	reset();
}

void Ball::notify(BallEvent event)
{
	for (auto it = subscribers.begin(); it != subscribers.end();)
	{
		if (auto observer = it->lock())
		{
			observer->onBallEvent(event);
			it++;
		}
		else
		{
			it = subscribers.erase(it);
		}
	}
}

void Ball::update()
{
	applyMovement(&position);

	switch (checkBoundaries(&position))
	{
	case BOUNDARY::TOP:
		notify(BallEvent::WALL_HIT);
		break;

	case BOUNDARY::BOTTOM:
		notify(BallEvent::WALL_HIT);
		break;

	case BOUNDARY::LEFT:
		notify(BallEvent::GOAL_LEFT);
		reset();
		break;

	case BOUNDARY::RIGHT:
		notify(BallEvent::GOAL_RIGHT);
		reset();
		break;
	}

	switch (checkForCollisions(&position, &size))
	{
	case COLLITION::PLAYER:
		notify(BallEvent::PADDLE_HIT);
		onPaddleHit(true);
		break;
	case COLLITION::COMPUTER:
		notify(BallEvent::PADDLE_HIT);
		onPaddleHit(false);
		break;
	case COLLITION::NONE:
		break;
	default:
		break;
	}
}

void Ball::render()
{
	SDL_FRect destination = getCollider();
	requestDraw(TEXTURE::BALL, destination, SDL_FLIP_NONE);
}

void Ball::reset()
{
	position = basePosition;
	setRandomDirection();
	currentSpeed = baseSpeed;
	isCollidingPaddle = false;
}