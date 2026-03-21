#include "BallPublisher.h"

void BallPublisher::addBallListener(std::shared_ptr<BallSubscriber> listener)
{
	ballSubscribers.push_back(listener);
}

void BallPublisher::removeBallListener(std::shared_ptr<BallSubscriber> listener)
{
	std::erase_if(ballSubscribers, [&listener](const auto& weakptr) {
		auto shared = weakptr.lock();
		return !shared || shared == listener;
	});
}
