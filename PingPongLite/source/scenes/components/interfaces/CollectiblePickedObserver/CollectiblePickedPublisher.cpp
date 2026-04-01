#include "CollectiblePickedPublisher.h"

void CollectiblePickedPublisher::addCollectiblePickedListener(std::shared_ptr<CollectiblePickedSubscriber> listener)
{
	collectiblePickedSubscribers.push_back(listener);
}

void CollectiblePickedPublisher::removeCollectiblePickedListener(std::shared_ptr<CollectiblePickedSubscriber> listener)
{
	std::erase_if(collectiblePickedSubscribers, [&listener](const auto weakptr) -> bool {
		auto shared = weakptr.lock();
		return !shared || shared == listener;
	});
}
