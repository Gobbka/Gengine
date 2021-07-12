#include "BMPImageDriver.h"
#include <cassert>

#define READ_INT32(ptr,offset) *(int*)((char*)ptr + offset)
#define READ_INT16(ptr,offset) *(unsigned short*)((char*)ptr + offset)

BMPImageDriver::DriverOutput::DriverOutput(char* ptr, size_t size, size_t width, size_t height)
	: DriverInput()
{
	this->ptr = ptr;
	this->size = size;
	this->width = width;
	this->height = height;
}

BMPImageDriver::DriverOutput BMPImageDriver::to_data_byte4(DriverInput input)
{
	const auto file_size = (size_t)READ_INT32(input.ptr, 0x2);
	const auto image_size = (size_t)READ_INT32(input.ptr, 0x22);
	const auto offset = READ_INT32(input.ptr,0xA);

	const auto width = READ_INT32(input.ptr, 0X12);
	const auto height = READ_INT32(input.ptr, 0X16);

	const auto bits_per_pixel = READ_INT16(input.ptr, 0x1c);

	auto* input_ptr = input.ptr + offset;

	const auto total_pixels = (size_t)width * height;

	struct Color4Byte
	{
		char r, g, b, a;
	};

	auto* img_output_ptr = new Color4Byte[total_pixels];
	
	for(size_t i = 0; i < total_pixels;i++)
	{
		img_output_ptr[i] = Color4Byte{
			input_ptr[i * 3],
			input_ptr[i * 3+1],
			input_ptr[i * 3+2],
			(char)0xFF
		};
	}
	
	return DriverOutput((char*)img_output_ptr, total_pixels * 4,width,height);
}
