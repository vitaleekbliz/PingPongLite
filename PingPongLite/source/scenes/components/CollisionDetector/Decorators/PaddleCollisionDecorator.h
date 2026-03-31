#pragma once
#include "CollisionDecorator.h"

class PaddleCollisionDecorator : public CollisionDecorator
{
  public:
	void addPaddles(std::weak_ptr<Object> paddleLeft, std::weak_ptr<Object> paddleRight);

	std::optional<SDL_FRect> resolvePaddleCollisions(const SDL_FRect& ballCollider);

  private:
	std::weak_ptr<Object> paddleLeft;
	std::weak_ptr<Object> paddleRight;

	bool isCollidingPaddle = false;
};
