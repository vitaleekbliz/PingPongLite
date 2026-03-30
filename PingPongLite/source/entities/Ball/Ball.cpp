#include "Ball.h"

Ball::Ball()
{
	setSize({30, 30});
	movement.reset(&position);
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
	movement.onPaddleHit(&position, size, paddleCollider);
}

void Ball::onBoundaryEvent(BOUNDARY event)
{
	switch (event)
	{
	case BOUNDARY::LEFT:
	case BOUNDARY::RIGHT:
		movement.reset(&position);
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