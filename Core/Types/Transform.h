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

	class __declspec(dllexport) Quaternion3 {
		Vector3 _rotation;
	public:
		Quaternion3(Vector3 rotation);

		Vector3 get_rotation();
	};
};
