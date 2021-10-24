#include "Passer.h"

void Render::Passer::add_pass(IPass*pass, PassStep step)
{
	switch (step)
	{
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
