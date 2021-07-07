#include "IResource.h"

IResource::IResource(void* resource, size_t size)
{
	_resource = resource;
	_size = size;
}

void* IResource::resource()
{
	return _resource;
}

size_t IResource::size()
{
	return _size;
}
