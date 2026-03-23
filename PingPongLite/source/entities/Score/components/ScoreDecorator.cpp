#include "ScoreDecorator.h"

ScoreDecorator::ScoreDecorator()
{
	SDL_FPoint pos = SDL_FPoint();

	pos.x = position.x - effectOffset;
	leftEffect.setPosition(pos);

	pos.x = position.x + effectOffset;
	rightEffect.setPosition(pos);
}

void ScoreDecorator::update()
{
	leftEffect.update();
	rightEffect.update();
}

void ScoreDecorator::render()
{
	std::string score_text = std::to_string(score);
	FontHandler::get().drawText(FONT::CALIBRI, score_text.c_str(), &position, 32, color);

	drawSideBar(true);
	drawSideBar(false);

	leftEffect.render();
	rightEffect.render();
}

void ScoreDecorator::increment()
{
	score++;
	if (tag == "player")
	{
		AudioHandler::get().playAudio(SOUNDS::WIN);
	}
	else if (tag == "computer")
	{
		AudioHandler::get().playAudio(SOUNDS::LOSE);
	}

	// if (score % 5 == 0)
	{
		leftEffect.start(tag == "player", effectDuration);
		rightEffect.start(tag == "player", effectDuration);
	}
}

void ScoreDecorator::drawSideBar(bool left)
{
	SDL_FRect globalDest = sideBarDestination;

	if (left)
		globalDest.x *= -1.f;
	globalDest.x += position.x;

	TextureHandler::get().drawTexture(TEXTURE::SCORE_BAR, globalDest, (left ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
}
