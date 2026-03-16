#pragma once
#include "Ball.h"
#include "Object.h"
#include "Paddle.h"
#include <memory>

class Creator
{
  public:
	std::unique_ptr<Object> create(ObjectID id);

  private:
};
