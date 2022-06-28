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

	Visible overflow = Visible::visible;
	Display display = Display::block;

	Vector4 margin = {0,0,0,0};
	float alpha = 1.f;
};
