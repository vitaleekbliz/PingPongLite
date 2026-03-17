#pragma once
#include "BallSubscriber.h"
#include <algorithm>
#include <memory>
#include <vector>

class BallPublisher
{
  public:
	void addListener(std::shared_ptr<BallSubscriber> listener);
	void removeListener(std::shared_ptr<BallSubscriber> listener);

  protected:
	virtual void notify(BallEvent event) = 0;

	std::vector<std::weak_ptr<BallSubscriber>> subscribers;
};
