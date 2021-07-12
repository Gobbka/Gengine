#pragma once

class __declspec(dllexport) BMPImageDriver
{
public:
	struct DriverInput
	{
		char* ptr;
		size_t size;
	};

	struct DriverOutput : public DriverInput
	{
		size_t width;
		size_t height;

		DriverOutput(char* ptr, size_t size, size_t width, size_t height);
	};
	
	static DriverOutput to_data_byte4(DriverInput input);
};
