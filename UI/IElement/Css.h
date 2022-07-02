#pragma once
#include "Types/Types.h"

struct Css
{
	enum class Visible
	{
		visible,
		hidden,
	};

	enum class Display
	{
		block,
		none,
	};

	enum class Cursor 
	{
		arrow,
		pointer,
	};

	Visible overflow = Visible::visible;
	Display display = Display::block;
	Cursor cursor = Cursor::arrow;

	Vector4 margin = {0,0,0,0};
	float alpha = 1.f;
};
