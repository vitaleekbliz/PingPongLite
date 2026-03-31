#pragma once
#include "entities/Object.h"

class CollectibleSpawnSubscriber
{
  public:
	virtual ~CollectibleSpawnSubscriber() = default;
	virtual void onCollectibleSpawned(std::weak_ptr<Object> collectable) = 0;
};