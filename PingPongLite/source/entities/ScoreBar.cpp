#include "ScoreBar.h"

ScoreBar::ScoreBar()
{
	leftScore = ScoreDecorator();
	rightScore = ScoreDecorator();

	leftScore.setPosition({280, 20});
	rightScore.setPosition({1280 - 280, 20});

	leftScore.color = SDL_Color(82, 124, 215);
	rightScore.color = SDL_Color(215, 121, 82);
}

void ScoreBar::update()
{
	float deltaTime = SDLHandler::get().getTick();
	roundDurationSeconds += deltaTime;

#pragma region TEST DEBUG strategy call request
	static const float cooldown = 15.f;
	static float timer = cooldown;

	timer -= deltaTime;
	if (timer < 0.f)
	{
		timer = cooldown;
		onStrategyChange();
	}
#pragma endregion
}

void ScoreBar::render()
{
	leftScore.render();
	rightScore.render();

	// Draw time START
	int minutes = roundDurationSeconds / 60;
	int seconds = (int)roundDurationSeconds % 60;
	std::string current_time = std::to_string(minutes) + (seconds > 9 ? " : " : " : 0") + std::to_string(seconds);

	SDL_Color color = SDL_Color(211, 211, 211);
	requestDrawText(FONT::CALIBRI, current_time.c_str(), &timePos, 32, color);
	// END
}

void ScoreBar::onBallEvent(BallEvent event)
{
	switch (event)
	{
	case BallEvent::GOAL_LEFT:
		rightScore.score++;
		break;
	case BallEvent::GOAL_RIGHT:
		leftScore.score++;
		break;
	}
}

void ScoreBar::onStrategyChange()
{
	std::swap(leftScore.color, rightScore.color);
	std::swap(leftScore.score, rightScore.score);
}

void ScoreBar::setScoreDecoratorListeners(std::shared_ptr<TextureSubscriber> texture,
										  std::shared_ptr<FontSubscriber> font)
{
	leftScore.addTextureListener(texture);
	leftScore.addFontListener(font);
	rightScore.addTextureListener(texture);
	rightScore.addFontListener(font);
}
