#pragma once
#include "StrategySubscriber.h"
#include <algorithm>
#include <memory>
#include <vector>

class StrategyPublisher
{
  public:
	void addStrategyListener(std::shared_ptr<StrategySubscriber> strategyListener);
	void removeStrategyListener(std::shared_ptr<StrategySubscriber> strategyListener);

  protected:
	virtual void notify() = 0;

	std::vector<std::weak_ptr<StrategySubscriber>> strategySubscribers;
};
