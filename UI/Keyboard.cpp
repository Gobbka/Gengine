#include "Keyboard.h"

bool virtual_keys[0XFE]{};

bool Keyboard::pressed(VirtualKey key)
{
	return virtual_keys[(__int8)key];
}

void Keyboard::set(VirtualKey key, bool active)
{
	virtual_keys[(__int8)key] = active;
}
