#pragma once
#include "BallSubscriber.h"
#include <algorithm>
#include <memory>
#include <vector>

class BallPublisher
{
  public:
	void addBallListener(std::shared_ptr<BallSubscriber> listener);
	void removeBallListener(std::shared_ptr<BallSubscriber> listener);

  protected:
	virtual void notify(BallEvent event) = 0;

	std::vector<std::weak_ptr<BallSubscriber>> ballSubscribers;
};
