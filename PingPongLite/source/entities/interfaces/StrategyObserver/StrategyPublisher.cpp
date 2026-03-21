#include "StrategyPublisher.h"

void StrategyPublisher::addStrategyListener(std::shared_ptr<StrategySubscriber> listener)
{
	strategySubscribers.push_back(listener);
}

void StrategyPublisher::removeStrategyListener(std::shared_ptr<StrategySubscriber> listener)
{
	std::erase_if(strategySubscribers, [&listener](const auto& weakptr) {
		auto shared = weakptr.lock();
		return !shared || shared == listener;
	});
}
