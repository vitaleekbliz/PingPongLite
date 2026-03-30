#pragma once
#include "entities/Object.h"
#include <SDL3/SDL.h>
#include <memory>
#include <optional>
#include <vector>

class PaddleCollisionDecorator
{
  public:
	void addPaddles(std::weak_ptr<Object> paddleLeft, std::weak_ptr<Object> paddleRight);

	std::optional<SDL_FRect> resolvePaddleCollisions(const SDL_FRect& ballCollider);

  private:
	bool checkForPaddleCollision(const SDL_FRect& ballCollider, std::weak_ptr<Object> paddle);
	bool checkCircleInsideBox(const SDL_FRect& ball, const SDL_FRect& rect);

	std::weak_ptr<Object> paddleLeft;
	std::weak_ptr<Object> paddleRight;

	bool isCollidingPaddle = false;
};
