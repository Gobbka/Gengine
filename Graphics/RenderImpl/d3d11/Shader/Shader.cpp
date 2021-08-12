#include "Shader.h"
#include <cassert>
#include <d3dcompiler.h>

void Render::Shader::read_file(const wchar_t* file_name)
{
	assert(SUCCEEDED(D3DReadFileToBlob(file_name, &_blob)));
	this->construct(_blob);
}

void Render::Shader::release_blob() const
{
	_blob->Release();
}
