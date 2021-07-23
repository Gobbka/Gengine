#pragma once
#include "Types.h"

namespace Core
{
	class __declspec(dllexport) Transform
	{
		Position3 _pos;
		Vector3  _rotation;
		
		DirectX::XMMATRIX _world_matrix;
	private:
		void update_world_matrix();
	public:
		DirectX::XMMATRIX get_world_matrix() const;
		
		Transform(Position3 pos);

		void adjust_position(Position3 pos);
		void set_position(Position3 pos);

		void adjust_rotation(Vector3 rotation);
		void set_rotation(Vector3 rotation);

		Position3 get_position();
	};

	class __declspec(dllexport) Quaternion3 {
		Vector3 _rotation;
	public:
		Quaternion3(Vector3 rotation);

		void adjust_rotation(Vector3 rot);

		Vector3 get_rotation();
	};
};
