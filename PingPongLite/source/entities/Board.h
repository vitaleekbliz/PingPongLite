#pragma once
#include "Object.h"

class Board : public Object
{
  public:
	void update() override;
	void render() override;
};
