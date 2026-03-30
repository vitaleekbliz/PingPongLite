#include "PaddleHitPublisher.h"

void PaddleHitPublisher::addPaddleHitListener(std::shared_ptr<PaddleHitSubscriber> listener)
{
	paddleHitSubscribers.push_back(listener);
}

void PaddleHitPublisher::removePaddleHitListener(std::shared_ptr<PaddleHitSubscriber> listener)
{
	std::erase_if(paddleHitSubscribers, [&listener](const auto& weakptr) {
		auto shared = weakptr.lock();
		return !shared || shared == listener;
	});
}
