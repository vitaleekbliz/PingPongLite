#include "TimeDecorator.h"

void TimeDecorator::update()
{
	seconds += SDLHandler::get().getTick();
	if (seconds > 60.f)
	{
		seconds -= 60.f;
		minutes++;
	}
}

void TimeDecorator::render()
{
	std::string current_time =
		std::to_string(minutes) + (seconds > 10.f ? " : " : " : 0") + std::to_string((int)seconds);

	FontHandler::get().drawText(FONT::CALIBRI, current_time.c_str(), &position, 32, color);
}
