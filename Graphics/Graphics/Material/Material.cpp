#include "Material.h"

Render::Material::Material(void* pSysMem, Surface resolution)
	: _resolution(resolution)
{
	_pSysMem = pSysMem;
}
