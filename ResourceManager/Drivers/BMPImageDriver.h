#pragma once
#include "ImageDriver.h"

class __declspec(dllexport) BMPImageDriver
{
public:
	static DriverOutput to_data_byte4(DriverInput input);
};
