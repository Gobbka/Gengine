#pragma once
#include "Step.h"

namespace Render
{
	class MeshContainerComponent;

	class Technique
	{
	private:
		bool _active = true;
		size_t _channels;

		std::vector<Step> _steps;
	public:
		void submit(MeshContainerComponent* model,size_t channel);
		void add_step(Step step);
	public:
		virtual ~Technique() = default;
		Technique(size_t channels);
	};
}
