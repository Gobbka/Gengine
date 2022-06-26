#pragma once
#include <functional>
#include <vector>
#include <Windows.h>

#include "Ecs/Ecs.h"

namespace UI
{

	struct __declspec(dllexport) AnimFunction
	{
		static float linear(float time)
		{
			return 1.f;
		}
	};
	
	struct __declspec(dllexport) AnimationComponent
	{
	public:
		typedef std::function<void(float value)> tSetFunction;

		// returns 0 <= value <= 1
		typedef float(*tAnimFunc)(float time);

	private:
		
		tSetFunction _set_function;
		tAnimFunc _anim_func;

		float _step;
		float _value;
		float _during;
		float _end_time;
	public:
		AnimationComponent(float from_value,float to_value, UINT during_ms, AnimationComponent::tSetFunction set_function, AnimationComponent::tAnimFunc anim_handle = AnimFunction::linear);

		bool play_step(float delta_time);
	};
	
	class __declspec(dllexport) HandleAnimationSystem : public ECS::EntitySystem
	{
		void tick(ECS::World* world, ECS_TICK_TYPE data) override;
	};
}
