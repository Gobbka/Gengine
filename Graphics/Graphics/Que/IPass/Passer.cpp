#include "Passer.h"

void Render::Passer::add_pass(IPass*pass)
{
	_body_passes.push_back(pass);
}

std::vector<Render::IPass*>& Render::Passer::get_passes()
{
	return _body_passes;
}
