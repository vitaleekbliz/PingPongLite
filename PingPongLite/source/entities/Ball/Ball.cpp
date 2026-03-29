#include "Ball.h"

Ball::Ball()
{
	setSize({30, 30});
	reset();
}

void Ball::update()
{
	movement.applyMovement(&position);
}

void Ball::render()
{
	SDL_FRect destination = getCollider();
	TextureHandler::get().drawTexture(TEXTURE::BALL, destination, SDL_FLIP_NONE);
}

void Ball::onPaddleHit(const SDL_FRect& paddleCollider)
{
	AudioHandler::get().playAudio(SOUNDS::HIT);
	movement.onPaddleHit(&position, paddleCollider);
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
}