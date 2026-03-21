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
#pragma region TEST DEBUG strategy call request
	float deltaTime = SDLHandler::get().getTick();
	static const float cooldown = 15.f;
	static float timer = cooldown;

	timer -= deltaTime;
	if (timer < 0.f)
	{
		timer = cooldown;
		originalGoal = !originalGoal;
	}
#pragma endregion
	applyMovement(&position);

	switch (checkBoundaries(&position))
	{
	case BOUNDARY::TOP:
		notify(BallEvent::WALL_HIT);
		onWallHit();
		break;

	case BOUNDARY::BOTTOM:
		notify(BallEvent::WALL_HIT);
		onWallHit();
		break;

	case BOUNDARY::LEFT:
		notify((originalGoal ? BallEvent::GOAL_LEFT : BallEvent::GOAL_RIGHT));
		reset();
		break;

	case BOUNDARY::RIGHT:
		notify((originalGoal ? BallEvent::GOAL_RIGHT : BallEvent::GOAL_LEFT));
		reset();
		break;
	}

	SDL_FRect collidingWith = SDL_FRect();
	switch (checkForCollisions(&position, &size, collidingWith))
	{
	case COLLITION::PLAYER:
		notify(BallEvent::PADDLE_HIT);
		onPaddleHit(true, &position, &collidingWith);
		break;
	case COLLITION::COMPUTER:
		notify(BallEvent::PADDLE_HIT);
		onPaddleHit(false, &position, &collidingWith);
		break;
	}
}

void Ball::render()
{
	SDL_FRect destination = getCollider();
	requestDrawTexture(TEXTURE::BALL, destination, SDL_FLIP_NONE);
}

void Ball::reset()
{
	position = basePosition;
	setRandomDirection();
	currentSpeed = baseSpeed;
	isCollidingPaddle = false;
}