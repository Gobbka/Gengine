#include "Technique.h"

#include "../../Render/Model/Model.h"

Render::Technique::Technique(size_t channels)
{
	_channels = channels;
}

void Render::Technique::submit(Model* model, size_t channel)
{
	if (this->_active && (channel & _channels) != 0)
	{
		for (auto step : _steps)
		{
			step.bind();
			//model->draw();
		}
	}
}

void Render::Technique::add_step(Step step)
{
	_steps.push_back(step);
}
