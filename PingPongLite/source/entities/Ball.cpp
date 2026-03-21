#include "Ball.h"

Ball::Ball()
{
	size.x = 30;
	size.y = 30;

	reset();
}

void Ball::notify(BallEvent event)
{
	for (auto it = ballSubscribers.begin(); it != ballSubscribers.end();)
	{
		if (auto observer = it->lock())
		{
			observer->onBallEvent(event);
			it++;
		}
		else
		{
			it = ballSubscribers.erase(it);
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
	case BOUNDARY::BOTTOM:
		AudioHandler::get().playAudio(SOUNDS::HIT);
		notify(BallEvent::WALL_HIT);
		onWallHit();
		break;

	case BOUNDARY::LEFT:
		// TEMP correct the way ball decorators behave and add strategy change Observer to them
		AudioHandler::get().playAudio((originalGoal ? SOUNDS::WIN : SOUNDS::LOSE));
		notify(BallEvent::GOAL_LEFT);
		reset();
		break;

	case BOUNDARY::RIGHT:
		// TEMP correct the way ball decorators behave and add strategy change Observer to them
		AudioHandler::get().playAudio((originalGoal ? SOUNDS::LOSE : SOUNDS::WIN));
		notify(BallEvent::GOAL_RIGHT);
		reset();
		break;
	}

	SDL_FRect collidingWith = SDL_FRect();
	switch (checkForCollisions(&position, &size, collidingWith))
	{
	case COLLITION::PLAYER:
		AudioHandler::get().playAudio(SOUNDS::HIT);
		notify(BallEvent::PADDLE_HIT);
		onPaddleHit(&position, &collidingWith);
		break;
	case COLLITION::COMPUTER:
		AudioHandler::get().playAudio(SOUNDS::HIT);
		notify(BallEvent::PADDLE_HIT);
		onPaddleHit(&position, &collidingWith);
		break;
	}
}

void Ball::render()
{
	SDL_FRect destination = getCollider();
	TextureHandler::get().drawTexture(TEXTURE::BALL, destination, SDL_FLIP_NONE);
}

void Ball::reset()
{
	position = basePosition;
	setRandomDirection();
	currentSpeed = baseSpeed;
	isCollidingPaddle = false;
}