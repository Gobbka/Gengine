#pragma once
#include <cassert>
#include <cstdint>

namespace FS
{
	class File;
}

class __declspec(dllexport) BinaryReader
{
public:
    explicit BinaryReader(_In_z_ wchar_t const* fileName) noexcept(false);
    BinaryReader(_In_reads_bytes_(dataSize) uint8_t const* dataBlob, size_t dataSize) noexcept;

    BinaryReader(BinaryReader const&) = delete;
    BinaryReader(BinaryReader && other) noexcept(true);
    BinaryReader& operator=(BinaryReader&& other) noexcept;

    // Reads a single value.
    template<typename T> T const& Read()
    {
        return *readArray<T>(1);
    }

    // Reads an array of values.
    template<typename T> T const* readArray(size_t elementCount)
    {
        uint8_t const* newPos = _pos + sizeof(T) * elementCount;

        assert(newPos > _pos);
        assert(newPos <= _end);

        auto result = reinterpret_cast<T const*>(_pos);

        _pos = newPos;

        return result;
    }

    auto available() const
    {
        return _end - _pos;
    }

    auto valid() const
    {
        return _data != nullptr;
    }

    char* toString() const;

    // Lower level helper reads directly from the filesystem into memory.
    static bool readEntireFile(_In_z_ wchar_t const* fileName, _Inout_ uint8_t** data, size_t* dataSize);

    ~BinaryReader();
private:
    // The data currently being read.
    uint8_t const* _pos;
    uint8_t const* _end;

    uint8_t* _data;
};
