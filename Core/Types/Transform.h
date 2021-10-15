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
		DirectX::XMMATRIX create_world_matrix() const;

		DirectX::XMVECTOR _forward_vector;
		DirectX::XMVECTOR _up_vector;
		DirectX::XMVECTOR _right_vector;
	public:
		DirectX::XMMATRIX get_world_matrix() const;
		
		Transform(Position3 pos);

		void adjust_position(Position3 pos);
		void set_position(Position3 pos);

		void adjust_rotation(Vector3 rotation);
		void set_rotation(Vector3 rotation);

		Position3 get_position_lh() const;
		Position3 get_position() const;
		Vector3 get_rotation() const;

		static inline DirectX::XMVECTOR up();
		static inline DirectX::XMVECTOR right();
		static inline DirectX::XMVECTOR forward();
	};

	class __declspec(dllexport) Quaternion3 {
		Vector3 _rotation;
	public:
		Quaternion3(Vector3 rotation);

		void adjust_rotation(Vector3 rot);

		Vector3 get_rotation() const;
	};
};
