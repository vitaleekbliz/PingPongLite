#pragma once
#include "entities/Object.h"

class CollectiblePickedSubscriber
{
  public:
	virtual ~CollectiblePickedSubscriber() = default;
	virtual void onCollectiblePicked(std::weak_ptr<Object> collectible) = 0;
};