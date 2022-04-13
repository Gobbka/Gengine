#include "BinaryReader.h"

#include <fstream>
#include <winerror.h>
#include "FS/FSFile.h"

BinaryReader::BinaryReader(_In_z_ wchar_t const* fileName) noexcept(false)
	: mPos(nullptr)
	, mEnd(nullptr)
	, mOwnedData(nullptr)
{
	auto dataSize = 0ull;
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

BinaryReader::BinaryReader(BinaryReader&& other) noexcept(true)
	: mPos(other.mPos)
	, mEnd(other.mEnd)
	, mOwnedData(other.mOwnedData)
{
	other.mOwnedData = nullptr;
	other.mPos = nullptr;
	other.mEnd = nullptr;
}

BinaryReader& BinaryReader::operator=(BinaryReader&& other) noexcept
{
	if (mOwnedData != other.mOwnedData)
		delete[] mOwnedData;
	mOwnedData = other.mOwnedData;
	mEnd = other.mEnd;
	mPos = other.mPos;

	other.mOwnedData = nullptr;
	other.mEnd = nullptr;
	other.mPos = nullptr;

	return*this;
}

char* BinaryReader::to_string()
{
	char* new_ = new char[available()+1];
	new_[available()] = '\0';
	memcpy(new_, mOwnedData, mEnd - mOwnedData);
	return new_;
}

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
