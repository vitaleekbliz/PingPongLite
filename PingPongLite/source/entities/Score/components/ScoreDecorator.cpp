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

	pos.x = position.x - effectOffset;
	pos.y = position.y - effectOffset / 5;
	leftEffect->setPosition(pos);

	pos.x = position.x + effectOffset;
	pos.y = position.y - effectOffset / 5;
	rightEffect->setPosition(pos);
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
		leftEffect->start(tag == "player", (float)std::sqrt(score));
		rightEffect->start(tag == "player", (float)std::sqrt(score));
	}
}

void ScoreDecorator::upgradeColor()
{
	leftEffect->upgradeColor(tag == "player");
	rightEffect->upgradeColor(tag == "player");
}

void ScoreDecorator::drawSideBar(bool left)
{
	SDL_FRect globalDest = sideBarDestination;

	if (left)
		globalDest.x *= -1.f;
	globalDest.x += position.x;

	TextureHandler::get().drawTexture(TEXTURE::SCORE_BAR, globalDest, (left ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
}
