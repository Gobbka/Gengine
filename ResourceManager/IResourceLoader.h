#pragma once
#include "IResource.h"

class IResourceLoader
{
public:
	void(*onLoad)(IResource* resource);
};
