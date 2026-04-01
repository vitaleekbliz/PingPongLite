#include "ChangeScorePublisher.h"

void ChangeScorePublisher::addChangeScoreListener(std::weak_ptr<ChangeScoreSubscriber> listener)
{
	changeScoreSubscribers.push_back(listener);
}

void ChangeScorePublisher::removeChangeScoreListener(std::shared_ptr<ChangeScoreSubscriber> listener)
{
	std::erase_if(changeScoreSubscribers, [&listener](const auto weakptr) -> bool {
		auto shared = weakptr.lock();
		return !shared || listener == shared;
	});
}
