#include "GEString.h"

#include <cwchar>

GEString::GEString(wchar_t*& string)
	: _length(wcslen(string))
	, _string(string)
{
	string = nullptr;
}

GEString::GEString(const wchar_t* string)
	: _length(wcslen(string))
	, _string(new wchar_t[_length + 1])
{
	memcpy(_string, string, (_length + 1) * sizeof(wchar_t));
}

GEString::GEString(GEString& copy)
	: _length(copy._length)
	, _string(new wchar_t[_length])
{
	memcpy(_string, copy._string, (_length + 1) * sizeof(wchar_t));
}

GEString::GEString(GEString&& move) noexcept
	: _length(move._length)
	, _string(move._string)
{
	move._length = 0;
	move._string = nullptr;
}

GEString& GEString::operator=(GEString const& copy)
{
	if(_string != copy._string)
	{
		delete[] _string;
	}

	_length = copy._length;
	_string = new wchar_t[_length];
	memcpy(_string, copy._string, _length * sizeof(wchar_t));

	return *this;
}

GEString& GEString::operator=(GEString&& move) noexcept
{
	if (_string != move._string)
	{
		delete[] _string;
	}

	_length = move._length;
	_string = move._string;

	move._string = nullptr;
	move._length = 0;

	return *this;
}

bool GEString::operator==(GEString& other) const
{
	for (int i = 0;; i++)
	{
		const auto first_char = _string[i];
		const auto second_char = other._string[i];

		if (first_char == second_char && second_char == '\0')
			return true;

		if (first_char == '\0' || second_char == '\0')
			break;

		if (first_char != second_char)
			break;
	}

	return false;
}

GEString::~GEString()
{
	delete[] _string;
}

std::ostream& operator<<(std::ostream& os, const GEString& foo)
{
	os << foo._string;
	return os;
}
