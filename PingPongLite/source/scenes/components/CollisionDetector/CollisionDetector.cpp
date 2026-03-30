#include "CollisionDetector.h"

CollisionDetector::CollisionDetector()
{
	paddleCollisions = std::make_shared<PaddleCollisionDecorator>();
}

void CollisionDetector::update()
{
	if (auto ballLock = ball.lock())
	{
		SDL_FRect ballCollider = ballLock->getCollider();
		std::optional<SDL_FRect> paddleCollider = paddleCollisions->resolvePaddleCollisions(ballCollider);
		if (paddleCollider.has_value())
		{
			notifyPaddleHit(paddleCollider.value());
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

void CollisionDetector::addCollectable(std::weak_ptr<Object> item)
{
	collectibles.push_back(item);
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
