#pragma once

class IResource
{
private:
	void*  _resource;
	size_t _size;
public:
	IResource(void* resource, size_t size);

	void* resource();
	size_t size();
};
