#pragma once
#include <functional>
#include <vector>
#include <Windows.h>

namespace UI
{

	struct __declspec(dllexport) AnimFunction
	{
		static float linear(int time)
		{
			return 1.f;
		}
	};
	
	
	struct __declspec(dllexport) Animation
	{
	public:
		typedef std::function<void(float value)> tSetFunction;

		// returns 0 <= value <= 1
		typedef float(*tAnimFunc)(int time);

	private:
		
		tSetFunction _set_function;
		tAnimFunc _anim_func;

		float _step;
		float _value;
		int _during;
		int _end_time;
	public:
		Animation(float from_value,float to_value, UINT during_ms, Animation::tSetFunction set_function, Animation::tAnimFunc anim_handle = AnimFunction::linear);

		bool play_step(int delta_time);
	};

	
	
	class __declspec(dllexport) Animator
	{
		std::vector<Animation*> _animations;
		bool _playing = false;
		HANDLE _thread;

		static void handle_animations(Animator*animator);
	public:
		Animator();
		~Animator() = default;
		
		void add_animation(Animation*animation);
		void remove_anim(UINT index);

		void start();
		void end();

	};
}
