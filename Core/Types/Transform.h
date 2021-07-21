#pragma once
#include "Types.h"

namespace Core
{
	class __declspec(dllexport) Transform
	{
		Position3 _pos;
	public:
		Transform(Position3 pos);

		void adjust_position(Position3 pos);
		void set_position(Position3 pos);

		Position3 get_position();
	};
};
