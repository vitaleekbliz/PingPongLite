#pragma once
#include "BoundarySubscriber.h"
#include <algorithm>
#include <memory>
#include <vector>

class BoundaryPublisher
{
  public:
	virtual ~BoundaryPublisher() = default;
	void addBoundaryListener(std::shared_ptr<BoundarySubscriber> listener);
	void removeBoundaryListener(std::shared_ptr<BoundarySubscriber> listener);

  protected:
	virtual void notify(BOUNDARY event) = 0;

	std::vector<std::weak_ptr<BoundarySubscriber>> BoundarySubscribers;
};
