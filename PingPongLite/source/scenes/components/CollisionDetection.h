#pragma once
#include "PaddleHitObserver/PaddleHitPublisher.h"
#include "entities/Object.h"
#include <SDL3/SDL.h>
#include <memory>
#include <vector>

class CollisionDetection : public PaddleHitPublisher
{
  public:
	void update();

	void setBallRef(std::weak_ptr<Object> ball);
	void addPaddles(std::weak_ptr<Object> paddleLeft, std::weak_ptr<Object> paddleRight);
	void addCollectable(std::weak_ptr<Object> item);

  private:
	virtual void notifyPaddleHit(const SDL_FRect& paddleCollider) override;

	void resolvePaddleCollisions(const SDL_FRect& ballCollider);
	bool checkForPaddleCollision(const SDL_FRect& ballCollider, std::weak_ptr<Object> paddle);

	bool checkCircleInsideBox(const SDL_FRect& ball, const SDL_FRect& rect);

	std::weak_ptr<Object> ball;
	std::weak_ptr<Object> paddleLeft;
	std::weak_ptr<Object> paddleRight;
	bool isCollidingPaddle = false;

	std::vector<std::weak_ptr<Object>> collectibles;
};
