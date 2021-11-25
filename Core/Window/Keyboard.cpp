#include "Keyboard.h"

bool Keyboard::pressed(VirtualKey key) const
{
	return virtual_keys[(__int8)key];
}

void Keyboard::set(VirtualKey key, bool active)
{
	virtual_keys[(__int8)key] = active;
}
