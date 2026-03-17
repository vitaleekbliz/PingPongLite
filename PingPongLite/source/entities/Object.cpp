#include "Object.h"

Object::Object()
{
	position = {0, 0};
}

void Object::setPosition(std::pair<float, float> pos)
{
	position = pos;
}

std::pair<float, float> Object::getPosition()
{
	return position;
}
