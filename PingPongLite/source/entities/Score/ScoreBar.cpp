#include "ScoreBar.h"

ScoreBar::ScoreBar()
{
	computerScore = std::make_shared<ScoreDecorator>();
	playerScore = std::make_shared<ScoreDecorator>();

	computerScore->setPosition({280, 20});
	playerScore->setPosition({1280 - 280, 20});

	computerScore->color = SDL_Color(82, 124, 215);
	playerScore->color = SDL_Color(215, 121, 82);

	computerScore->isPlayerScore = false;
	playerScore->isPlayerScore = true;

	time.setPosition({1280 / 2, 20});
}

void ScoreBar::update()
{
	computerScore->update();
	playerScore->update();

	time.update();
}

void ScoreBar::render()
{
	computerScore->render();
	playerScore->render();

	time.render();
}

void ScoreBar::onBoundaryEvent(BOUNDARY event)
{
	switch (event)
	{
	case BOUNDARY::LEFT:
		(scoreSwapped ? computerScore : playerScore)->add(1);
		break;
	case BOUNDARY::RIGHT:
		(scoreSwapped ? playerScore : computerScore)->add(1);
		break;
	}
}

void ScoreBar::onStrategyChange()
{
	SDL_FPoint temp = playerScore->getPosition();
	playerScore->setPosition(computerScore->getPosition());
	computerScore->setPosition(temp);

	scoreSwapped = !scoreSwapped;
}

void ScoreBar::onAddScore(int value, bool computer)
{
	(computer ? computerScore : playerScore)->add(value);
}
