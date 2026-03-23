#include "BoundaryPublisher.h"

void BoundaryPublisher::addBoundaryListener(std::shared_ptr<BoundarySubscriber> listener)
{
	BoundarySubscribers.push_back(listener);
}

void BoundaryPublisher::removeBoundaryListener(std::shared_ptr<BoundarySubscriber> listener)
{
	std::erase_if(BoundarySubscribers, [&listener](const auto& weakptr) {
		auto shared = weakptr.lock();
		return !shared || shared == listener;
	});
}
