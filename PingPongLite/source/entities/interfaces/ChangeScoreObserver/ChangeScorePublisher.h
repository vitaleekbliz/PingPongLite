#pragma once
#include "ChangeScoreSubscriber.h"
#include <memory>
#include <vector>

class ChangeScorePublisher
{
  public:
	virtual ~ChangeScorePublisher() = default;

	void addChangeScoreListener(std::weak_ptr<ChangeScoreSubscriber> listener);
	void removeChangeScoreListener(std::shared_ptr<ChangeScoreSubscriber> listener);

	virtual void notifyAddScore(int value, bool computer) = 0;

  protected:
	std::vector<std::weak_ptr<ChangeScoreSubscriber>> changeScoreSubscribers;
};
