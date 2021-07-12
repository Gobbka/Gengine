#include "BMPImageDriver.h"
#include <cassert>
#include <fstream>

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


	const auto total_pixels = (size_t)width * height;

	struct Color4Byte
	{
		char r, g, b, a;
	};

	auto* img_output_ptr = new Color4Byte[total_pixels];

	auto* input_ptr = input.ptr;

	auto write_offset = offset;

	const auto layer_offset = 0x3;
	
	for(int i = 0,k=height*width-1;i < height;i++)
	{
		for(int j = 0;j<width;j++)
		{	
			img_output_ptr[k] = Color4Byte{
				input_ptr[write_offset+2],
				input_ptr[write_offset+1],
				input_ptr[write_offset],
				(char)0xFF
			};
			write_offset += 3;
			k--;
		}
		write_offset += layer_offset;
	}

	
	
	return DriverOutput((char*)img_output_ptr, total_pixels * 4,width,height);
}
