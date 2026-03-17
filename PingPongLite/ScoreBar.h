#pragma once
#include "Object.h"
class ScoreBar : public Object
{
  public:
	ScoreBar();
	void update(float deltaTime) override;
	void render() override;

  private:
	int roundDurationSeconds;
};
