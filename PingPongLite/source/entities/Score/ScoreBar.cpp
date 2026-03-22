#include "ScoreBar.h"

ScoreBar::ScoreBar()
{
	leftScore = ScoreDecorator();
	rightScore = ScoreDecorator();

	leftScore.setPosition({280, 20});
	rightScore.setPosition({1280 - 280, 20});

	leftScore.color = SDL_Color(82, 124, 215);
	rightScore.color = SDL_Color(215, 121, 82);

	leftScore.tag = "computer";
	rightScore.tag = "player";

	time.setPosition({1280 / 2, 20});
}

void ScoreBar::update()
{
	time.update();
}

void ScoreBar::render()
{
	leftScore.render();
	rightScore.render();

	time.render();
}

void ScoreBar::onBallEvent(BallEvent event)
{
	switch (event)
	{
	case BallEvent::GOAL_LEFT:
		rightScore.increment();
		break;
	case BallEvent::GOAL_RIGHT:
		leftScore.increment();
		break;
	}
}

void ScoreBar::onStrategyChange()
{
	std::swap(leftScore.color, rightScore.color);
	std::swap(leftScore.score, rightScore.score);
	std::swap(leftScore.tag, rightScore.tag);
}
