#include "Keyboard.h"

bool* __virtal_keys = new bool[0XFE]{};

bool Keyboard::pressed(VirtualKey key)
{
	return __virtal_keys[(__int8)key];
}

void Keyboard::set(VirtualKey key, bool active)
{
	__virtal_keys[(__int8)key] = active;
}
