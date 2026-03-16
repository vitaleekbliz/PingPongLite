#pragma once
#include <utility>

enum class ObjectID : char
{
	BALL,
	PADDLE,
	SCORE_BAR,
	BOARD
};
class Object
{
  public:
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
	virtual ~Object() = default;

	void setPosition(std::pair<float, float> pos);

  private:
	std::pair<float, float> position;
};
