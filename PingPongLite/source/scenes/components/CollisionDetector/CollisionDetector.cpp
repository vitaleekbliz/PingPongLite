#include "CollisionDetector.h"

CollisionDetector::CollisionDetector()
{
	paddleCollisions = std::make_shared<PaddleCollisionDecorator>();
	collectiblesCollisions = std::make_shared<CollectiblesCollisionDecorator>();
}

void CollisionDetector::update()
{
	if (auto ballLock = ball.lock())
	{
		// 1. Paddle collisions
		SDL_FRect ballCollider = ballLock->getCollider();
		std::optional<SDL_FRect> paddleCollider = paddleCollisions->resolvePaddleCollisions(ballCollider);
		if (paddleCollider.has_value())
		{
			notifyPaddleHit(paddleCollider.value());
		}

		// 2. Collectibles collisions

		std::optional<std::weak_ptr<Object>> touchingCollectible =
			collectiblesCollisions->resolveCollisions(ballCollider);
		if (touchingCollectible.has_value())
		{
			// TODO notify collectible is touched by the ball
			printf("TOUCHING\n");
		}
	}
}

void CollisionDetector::setBallRef(std::weak_ptr<Object> ball)
{
	this->ball = ball;
}

void CollisionDetector::addPaddles(std::weak_ptr<Object> paddleLeft, std::weak_ptr<Object> paddleRight)
{
	paddleCollisions->addPaddles(paddleLeft, paddleRight);
}

void CollisionDetector::onCollectibleSpawned(std::weak_ptr<Object> collectable)
{
	collectiblesCollisions->addCollectable(collectable);
}

void CollisionDetector::notifyPaddleHit(const SDL_FRect& paddleCollider)
{
	for (auto it = paddleHitSubscribers.begin(); it != paddleHitSubscribers.end();)
	{
		if (auto lock = it->lock())
		{
			lock->onPaddleHit(paddleCollider);
			it++;
		}
		else
		{
			it = paddleHitSubscribers.erase(it);
		}
	}
}
