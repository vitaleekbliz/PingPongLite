#pragma once

class ChangeScoreSubscriber
{
  public:
	virtual ~ChangeScoreSubscriber() = default;
	virtual void onAddScore(int value, bool computer) = 0;
};