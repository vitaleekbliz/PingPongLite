#pragma once
#include "Decorators/CollectiblesCollisionDecorator.h"
#include "Decorators/PaddleCollisionDecorator.h"
#include "PaddleHitObserver/PaddleHitPublisher.h"
#include "scenes/components/interfaces/CollectiblePickedObserver/CollectiblePickedPublisher.h"
#include "scenes/components/interfaces/CollectibleSpawnObserver/CollectibleSpawnSubscriber.h"

class CollisionDetector : public PaddleHitPublisher,
						  public CollectibleSpawnSubscriber,
						  public CollectiblePickedPublisher
{
  public:
	CollisionDetector();
	void update();

	void setBallRef(std::weak_ptr<Object> ball);
	void addPaddles(std::weak_ptr<Object> paddleLeft, std::weak_ptr<Object> paddleRight);

	virtual void onCollectibleSpawned(std::weak_ptr<Object> collectable) override;
	virtual void notifyCollectiblePicked(std::weak_ptr<Object> collectible) override;

  private:
	virtual void notifyPaddleHit(const SDL_FRect& paddleCollider) override;

	std::shared_ptr<PaddleCollisionDecorator> paddleCollisions;
	std::shared_ptr<CollectiblesCollisionDecorator> collectiblesCollisions;
	std::weak_ptr<Object> ball;
};
