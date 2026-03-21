#include "BallPublisher.h"

void BallPublisher::addBallListener(std::shared_ptr<BallSubscriber> listener)
{
	subscribers.push_back(listener);
}

void BallPublisher::removeBallListener(std::shared_ptr<BallSubscriber> listener)
{
	std::erase_if(subscribers, [&listener](const auto& weakptr) {
		auto shared = weakptr.lock();
		return !shared || shared == listener;
	});
}
