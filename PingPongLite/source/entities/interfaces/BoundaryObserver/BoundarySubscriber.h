#pragma once

enum class BOUNDARY : char
{
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

class BoundarySubscriber
{
  public:
	virtual ~BoundarySubscriber() = default;
	virtual void onBoundaryEvent(BOUNDARY event) = 0;
};
