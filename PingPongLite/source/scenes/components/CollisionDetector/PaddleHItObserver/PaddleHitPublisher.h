#pragma once
#include "PaddleHitSubscriber.h"
#include <algorithm>
#include <memory>
#include <vector>

class PaddleHitPublisher
{
  public:
	virtual ~PaddleHitPublisher() = default;

	void addPaddleHitListener(std::shared_ptr<PaddleHitSubscriber> listener);
	void removePaddleHitListener(std::shared_ptr<PaddleHitSubscriber> listener);

  protected:
	virtual void notifyPaddleHit(const SDL_FRect& paddleCollider) = 0;

	std::vector<std::weak_ptr<PaddleHitSubscriber>> paddleHitSubscribers;
};
