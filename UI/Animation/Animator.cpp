#include "Animator.h"

#include <utility>


UI::AnimationComponent::AnimationComponent(float from_value, float to_value, UINT during, AnimationComponent::tSetFunction set_function, AnimationComponent::tAnimFunc anim_handle)
{
	_end_time = during;
	_during = 0;
	_value = from_value;
	_step = (to_value - from_value) / (float)during;

	_set_function = std::move(set_function);
	_anim_func = anim_handle;
}

bool UI::AnimationComponent::play_step(float delta_time)
{
	if(_during < _end_time)
	{
		_value += _step * _anim_func(_during) * delta_time;
		
		_set_function(_value);
		
		_during += delta_time;
		return true;
	}
	
	return false;
}

void UI::HandleAnimationSystem::tick(ECS::World* world, ECS::DefaultTickData tick_data)
{
	world->each<AnimationComponent>([&](ECS::Entity* ent, ECS::ComponentHandle<AnimationComponent> hComp)
		{
			if(!hComp->play_step(tick_data))
			{
				ent->remove<AnimationComponent>();
			}
		});
}
