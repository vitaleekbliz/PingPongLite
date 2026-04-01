#pragma once
#include "CollectiblePickedSubscriber.h"
#include <algorithm>
#include <vector>

class CollectiblePickedPublisher
{
  public:
	virtual ~CollectiblePickedPublisher() = default;

	void addCollectiblePickedListener(std::shared_ptr<CollectiblePickedSubscriber> listener);
	void removeCollectiblePickedListener(std::shared_ptr<CollectiblePickedSubscriber> listener);

  protected:
	virtual void notifyCollectiblePicked(std::weak_ptr<Object> collectible) = 0;

	std::vector<std::weak_ptr<CollectiblePickedSubscriber>> collectiblePickedSubscribers;
};
