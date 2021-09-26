#pragma once
#include <cassert>
#include <cstdint>

namespace FS
{
	class FSFile;
}

class __declspec(dllexport) BinaryReader
{
public:
    explicit BinaryReader(_In_z_ wchar_t const* fileName) noexcept(false);
    BinaryReader(_In_reads_bytes_(dataSize) uint8_t const* dataBlob, size_t dataSize) noexcept;

    BinaryReader(BinaryReader const&) = delete;

    // Reads a single value.
    template<typename T> T const& Read()
    {
        return *ReadArray<T>(1);
    }

    // Reads an array of values.
    template<typename T> T const* ReadArray(size_t elementCount)
    {
        uint8_t const* newPos = mPos + sizeof(T) * elementCount;

        assert(newPos > mPos);
        assert(newPos <= mEnd);

        auto result = reinterpret_cast<T const*>(mPos);

        mPos = newPos;

        return result;
    }

    auto available()
    {
        return mEnd - mPos;
    }

    auto valid()
    {
        return mOwnedData != nullptr;
    }

    // Lower level helper reads directly from the filesystem into memory.
    static bool ReadEntireFile(_In_z_ wchar_t const* fileName, _Inout_ uint8_t** data, size_t* dataSize);

    ~BinaryReader();
private:
    // The data currently being read.
    uint8_t const* mPos;
    uint8_t const* mEnd;

    uint8_t* mOwnedData;
};
