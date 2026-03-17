#include "BallPublisher.h"

void BallPublisher::addListener(std::shared_ptr<BallSubscriber> listener)
{
	subscribers.push_back(listener);
}

void BallPublisher::removeListener(std::shared_ptr<BallSubscriber> listener)
{
	std::erase_if(subscribers, [&listener](const auto& weakptr) {
		auto shared = weakptr.lock();
		return !shared || shared == listener;
	});
}
