#include "Collectible.h"

Collectible::Collectible()
{
	setSize({32, 32});
}

COLLECTIBLE Collectible::getType() const
{
	return type;
}
