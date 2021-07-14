#pragma once

struct __declspec(dllexport) DriverInput
{
	char* ptr;
	size_t size;
};

struct __declspec(dllexport) DriverOutput : public DriverInput
{
	size_t width;
	size_t height;

	DriverOutput(char* ptr, size_t size, size_t width, size_t height) : DriverInput()
	{
		this->ptr = ptr;
		this->size = size;
		this->width = width;
		this->height = height;
	}
};

struct Color4Byte
{
	char r, g, b, a;
};
