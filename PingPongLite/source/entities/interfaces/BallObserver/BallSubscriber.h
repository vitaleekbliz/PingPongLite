#pragma once

enum class BallEvent : char
{
	GOAL_LEFT,
	GOAL_RIGHT,
	WALL_HIT,
	PADDLE_HIT
};

class BallSubscriber
{
  public:
	virtual ~BallSubscriber() = default;
	virtual void onBallEvent(BallEvent event) = 0;
};
