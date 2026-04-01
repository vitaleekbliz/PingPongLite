#include "Collectible.h"

Collectible::Collectible()
{
	setSize({48, 48});
}

COLLECTIBLE Collectible::getType() const
{
	return type;
}
