#include "Ball.h"

Ball::Ball()
{
	setSize({30, 30});
	reset();
}

void Ball::update()
{
	movement.applyMovement(&position);

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

void Ball::onBoundaryEvent(BOUNDARY event)
{
	switch (event)
	{
	case BOUNDARY::LEFT:
	case BOUNDARY::RIGHT:
		reset();
		break;
	case BOUNDARY::TOP:
	case BOUNDARY::BOTTOM:
		AudioHandler::get().playAudio(SOUNDS::HIT);
		movement.onWallHit();
		break;
	default:
		break;
	}
}

void Ball::reset()
{
	// move back to movement decorator after adding collision system
	position = movement.basePosition;
	movement.setRandomDirection();
	movement.currentSpeed = movement.baseSpeed;
	isCollidingPaddle = false;
}