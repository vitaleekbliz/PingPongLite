#include "ScoreBar.h"

ScoreBar::ScoreBar()
{
	leftScore = std::make_shared<ScoreDecorator>();
	rightScore = std::make_shared<ScoreDecorator>();

	leftScore->setPosition({280, 20});
	rightScore->setPosition({1280 - 280, 20});

	leftScore->color = SDL_Color(82, 124, 215);
	rightScore->color = SDL_Color(215, 121, 82);

	leftScore->tag = "computer";
	rightScore->tag = "player";

	time.setPosition({1280 / 2, 20});
}

void ScoreBar::update()
{
	leftScore->update();
	rightScore->update();

	time.update();
}

void ScoreBar::render()
{
	leftScore->render();
	rightScore->render();

	time.render();
}

void ScoreBar::onBoundaryEvent(BOUNDARY event)
{
	switch (event)
	{
	case BOUNDARY::LEFT:
		rightScore->increment();
		break;
	case BOUNDARY::RIGHT:
		leftScore->increment();
		break;
	}
}

void ScoreBar::onStrategyChange()
{
	SDL_FPoint temp = rightScore->getPosition();
	rightScore->setPosition(leftScore->getPosition());
	leftScore->setPosition(temp);

	std::swap(rightScore, leftScore);
}
