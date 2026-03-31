#pragma once
#include "CollectibleSpawnSubscriber.h"
#include <vector>

class CollectibleSpawnedPublisher
{
  public:
	virtual ~CollectibleSpawnedPublisher() = default;
	virtual void notifyCollectibleSpawned(std::weak_ptr<Object> collectible) = 0;

	void addCollectibleSpawnListener(std::shared_ptr<CollectibleSpawnSubscriber> listener);
	void removeCollectibleSpawnListener(std::shared_ptr<CollectibleSpawnSubscriber> listener);

  protected:
	std::vector<std::weak_ptr<CollectibleSpawnSubscriber>> collectibleSpawnSubscribers;
};
