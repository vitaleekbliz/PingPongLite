#pragma once
#include "Decorators/PaddleCollisionDecorator.h"
#include "PaddleHitObserver/PaddleHitPublisher.h"

class CollisionDetector : public PaddleHitPublisher
{
  public:
	CollisionDetector();
	void update();

	void setBallRef(std::weak_ptr<Object> ball);
	void addPaddles(std::weak_ptr<Object> paddleLeft, std::weak_ptr<Object> paddleRight);
	void addCollectable(std::weak_ptr<Object> item);

  private:
	virtual void notifyPaddleHit(const SDL_FRect& paddleCollider) override;

	std::shared_ptr<PaddleCollisionDecorator> paddleCollisions;
	std::weak_ptr<Object> ball;

	std::vector<std::weak_ptr<Object>> collectibles;
};
