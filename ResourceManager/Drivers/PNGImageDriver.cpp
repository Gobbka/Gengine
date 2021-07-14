#include "PNGImageDriver.h"

#include <cassert>

#define READ_INT32(ptr,offset) *(int*)((char*)ptr + offset)
#define READ_INT16(ptr,offset) *(unsigned short*)((char*)ptr + offset)
#define READ_INT8(ptr,offset) *(unsigned char*)((char*)ptr + offset)

#define TO_LITTLE_ENDIAN(x) ((x>>24) |((x >> 8) & 0x0000ff00) |((x << 8) & 0x00ff0000) | (x << 24))

#define FILE_SIGNATURE_SIZE 0x8

enum class COLOR_PALETTE
{
	GrayScale = 0,
	TrueColor = 2,
	Indexed_color = 3,
	Grayscale_alpha = 4,
	TrueColor_alpha = 6,
};

void PNGImageDriver::parse_chunks(DriverInput input, std::map<unsigned, PNGChunk>* map)
{
	unsigned offset = FILE_SIGNATURE_SIZE;
	
	while(true)
	{
		PNGChunk chunk;
		
		chunk.size = TO_LITTLE_ENDIAN( *(unsigned*)(input.ptr + offset));
		chunk.data_ptr = (input.ptr + offset + 4 + 4);

		unsigned chunk_name = *(unsigned*)(input.ptr + offset + 4);
		(*map)[chunk_name] = chunk;

		offset += 4 + 4 + chunk.size + 4;

		// 49 45 4E 44 what means IEND in ascii
		if(chunk_name == 0x444e4549)
			break;
	}
}

DriverOutput PNGImageDriver::to_data_byte4(DriverInput input)
{
	
	const auto ihdr_size = READ_INT32(input.ptr, FILE_SIGNATURE_SIZE);

	std::map<unsigned, PNGChunk> map;
	parse_chunks(input, &map);
	
	auto hdr_chunk = map[0x52444849];
	const auto image_width = TO_LITTLE_ENDIAN(READ_INT32(hdr_chunk.data_ptr, 0x0));
	const auto image_height = TO_LITTLE_ENDIAN(READ_INT32(hdr_chunk.data_ptr, 0x4));
	const auto bit_depth = READ_INT8(hdr_chunk.data_ptr, 0x8);
	const auto color_palette = (COLOR_PALETTE)READ_INT8(hdr_chunk.data_ptr, 0x9);
	const auto compression_method = READ_INT8(hdr_chunk.data_ptr, 0xA);
	const auto filter_method = READ_INT8(hdr_chunk.data_ptr, 0xB);
	const auto interlaced_method = READ_INT8(hdr_chunk.data_ptr, 0xB);

	assert(compression_method == 0);
	assert(filter_method == 0);
	assert(interlaced_method == 0);

	
	auto idat_chunk = map[0x54414449];

	auto* image_data = new Color4Byte[10 * 10];

	
	for(int i = 0,read_offset=0;i < idat_chunk.size;i++,read_offset+=3)
	{
		image_data[i] = Color4Byte{
			idat_chunk.data_ptr[read_offset],
			idat_chunk.data_ptr[read_offset + 1],
			idat_chunk.data_ptr[read_offset + 2],
			(char)0xFF
		};
	}
	
	return DriverOutput((char*)image_data, 10 * 10 * 4,image_width,image_height);
}
