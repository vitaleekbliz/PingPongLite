#pragma once

class StrategySubscriber
{
  public:
	virtual ~StrategySubscriber() = default;
	virtual void onStrategyChange() = 0;
};