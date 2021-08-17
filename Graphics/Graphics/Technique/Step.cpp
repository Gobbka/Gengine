#include "Step.h"

void Render::Step::add_bindable(BindFunction bind)
{
	_binds.push_back(bind);
}

void Render::Step::bind()
{
	for(auto bind : _binds)
	{
		bind();
	}
}
