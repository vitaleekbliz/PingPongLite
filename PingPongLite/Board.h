#pragma once
#include "Object.h"

class Board : public Object
{
  public:
	void update(float deltaTime) override;
	void render() override;
};
