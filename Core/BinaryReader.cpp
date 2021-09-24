﻿#include "BinaryReader.h"
#include <fstream>
#include <winerror.h>


BinaryReader::BinaryReader(_In_z_ wchar_t const* fileName) noexcept(false)
{
	mOwnedData = nullptr;

	size_t dataSize=0;
	const auto result = ReadEntireFile(fileName, &mOwnedData, &dataSize);

	assert(result);

	mPos = mOwnedData;
	mEnd = mOwnedData + dataSize;
}

BinaryReader::BinaryReader(_In_reads_bytes_(dataSize) uint8_t const* dataBlob, size_t dataSize) noexcept
	: mPos(dataBlob),
	mEnd(dataBlob + dataSize),
	mOwnedData(nullptr)
{}

bool BinaryReader::ReadEntireFile(_In_z_ wchar_t const* fileName, _Inout_ uint8_t** data, size_t* dataSize)
{
	std::ifstream ifs(fileName,std::ios::binary | std::ios::ate);

	if (!ifs.is_open())
		return false;

	*dataSize = ifs.tellg();
	*data = new uint8_t[*dataSize];
	ifs.seekg(std::ios::beg);
	ifs.read((char*)*data, *dataSize);

	return true;
}

BinaryReader::~BinaryReader()
{
	delete[] mOwnedData;
}
