#include "Passer.h"

void Render::Passer::clear(PassStep step)
{
	switch (step)
	{
	case PassStep::begin:
		_begin_passes.clear();
	break;
	case PassStep::draw:
		_draw_passes.clear();
	break;
	case PassStep::probe:
		_probe_passes.clear();
	break;
	case PassStep::overlay:
		_overlay_passes.clear();
	break;
	}
}

void Render::Passer::execute(Scene* scene)
{
	for (IPass* pass : _begin_passes)
	{
		pass->execute(scene);
	}
	for (IPass* pass : _probe_passes)
	{
		pass->execute(scene);
	}
	for (IPass* pass : _draw_passes)
	{
		pass->execute(scene);
	}
	for (IPass* pass : _overlay_passes)
	{
		pass->execute(scene);
	}
}

void Render::Passer::add_pass(IPass*pass, PassStep step)
{
	switch (step)
	{
	case PassStep::begin:
		_begin_passes.push_back(pass);
		break;
	case PassStep::draw:
		_draw_passes.push_back(pass);
	break;
	case PassStep::probe:
		_probe_passes.push_back(pass);
	break;
	case PassStep::overlay:
		_overlay_passes.push_back(pass);
	break;
	}	
}
