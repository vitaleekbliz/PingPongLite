#include "Ball.h"

Ball::Ball()
{
	setSize({30, 30});
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
	movement.applyMovement(&position);

	switch (movement.checkBoundaries(&position))
	{
	case BOUNDARY::TOP:
	case BOUNDARY::BOTTOM:
		AudioHandler::get().playAudio(SOUNDS::HIT);
		notify(BallEvent::WALL_HIT);
		movement.onWallHit();
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

#pragma region Add state machine after completing collision system
	bool playerCollision = player.checkForCollisions(&position, &size);
	bool computerCollision = computer.checkForCollisions(&position, &size);

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

		AudioHandler::get().playAudio(SOUNDS::HIT);
		notify(BallEvent::PADDLE_HIT);
		if (playerCollision)
		{
			movement.onPaddleHit(&position, player.getPaddleCollider());
		}
		else
		{
			movement.onPaddleHit(&position, computer.getPaddleCollider());
		}
	}
#pragma endregion
}

void Ball::render()
{
	SDL_FRect destination = getCollider();
	TextureHandler::get().drawTexture(TEXTURE::BALL, destination, SDL_FLIP_NONE);
}

void Ball::setPaddleReferences(std::shared_ptr<Object> player, std::shared_ptr<Object> computer)
{
	this->player.setPaddleReference(player);
	this->computer.setPaddleReference(computer);
}

void Ball::reset()
{
	// move back to movement decorator after adding collision system
	position = movement.basePosition;
	movement.setRandomDirection();
	movement.currentSpeed = movement.baseSpeed;
	isCollidingPaddle = false;
}