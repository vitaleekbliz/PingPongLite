#include "ScoreDecorator.h"

ScoreDecorator::ScoreDecorator()
{
	leftEffect = std::make_shared<EffectComponent>();
	rightEffect = std::make_shared<EffectComponent>();
}

void ScoreDecorator::update()
{
	upgradeEffectPosition();

	leftEffect->update();
	rightEffect->update();
}

void ScoreDecorator::render()
{
	std::string score_text = std::to_string(score);
	FontHandler::get().drawText(FONT::CALIBRI, score_text.c_str(), &position, 32, color);

	drawSideBar(true);
	drawSideBar(false);

	leftEffect->render();
	rightEffect->render();
}

void ScoreDecorator::upgradeEffectPosition()
{
	SDL_FPoint pos = getPosition();

	pos.x = position.x - effectOffsetX;
	pos.y = position.y + effectOffsetY;
	leftEffect->setPosition(pos);

	pos.x = position.x + effectOffsetX;
	pos.y = position.y + effectOffsetY;
	rightEffect->setPosition(pos);
}

void ScoreDecorator::add(int value)
{
	score += value;
	if (isPlayerScore)
	{
		AudioHandler::get().playAudio(SOUNDS::WIN);
	}
	else
	{
		AudioHandler::get().playAudio(SOUNDS::LOSE);
	}

	// if (score % 5 == 0)
	{
		leftEffect->start(isPlayerScore, (float)std::sqrt(score));
		rightEffect->start(isPlayerScore, (float)std::sqrt(score));
	}
}

void ScoreDecorator::upgradeColor()
{
	leftEffect->upgradeColor(isPlayerScore);
	rightEffect->upgradeColor(isPlayerScore);
}

void ScoreDecorator::drawSideBar(bool left)
{
	SDL_FRect globalDest = sideBarDestination;

	if (left)
		globalDest.x *= -1.f;
	globalDest.x += position.x;

	TextureHandler::get().drawTexture(TEXTURE::SCORE_BAR, globalDest, (left ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
}
