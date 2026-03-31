#include "CollectibleSpawnedPublisher.h"

void CollectibleSpawnedPublisher::addCollectibleSpawnListener(std::shared_ptr<CollectibleSpawnSubscriber> listener)
{
	collectibleSpawnSubscribers.push_back(listener);
}

void CollectibleSpawnedPublisher::removeCollectibleSpawnListener(std::shared_ptr<CollectibleSpawnSubscriber> listener)
{
	std::erase_if(collectibleSpawnSubscribers, [&listener](const auto& weakptr) -> bool {
		auto shared = weakptr.lock();
		return !shared || listener == shared;
	});
}
