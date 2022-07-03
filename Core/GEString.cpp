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

GEString::GEString(GEString const& copy)
	: _length(copy._length)
	, _string(new wchar_t[_length + 1])
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

bool GEString::operator==(const wchar_t* other) const
{
	for (int i = 0;; i++)
	{
		const auto first_char = _string[i];
		const auto second_char = other[i];

		if (first_char == second_char && second_char == '\0')
			return true;

		if (first_char == '\0' || second_char == '\0')
			break;

		if (first_char != second_char)
			break;
	}

	return false;
}

bool GEString::endsWith(const wchar_t* search_string) const
{
	const auto length = wcslen(search_string);
	for(auto i = length - 1, j = _length - 1;i-->0 && j --> 0;)
	{
		if (_string[j] != search_string[i])
			return false;
	}
	return true;
}

bool GEString::startsWith(const wchar_t* search_string) const
{
	for(size_t i = 0; i < _length && search_string[i]; i++)
	{
		if(search_string[i] != _string[0])
		{
			return false;
		}
	}

	return true;
}

GEString GEString::copy(wchar_t* string)
{
	const auto length = wcslen(string);
	auto* new_string = new wchar_t[length + 1];
	memcpy(new_string, string, (length + 1) * sizeof(wchar_t));

	return GEString(new_string);
}

GEString GEString::slice(size_t start, size_t end) const
{
	if (start == 0 && end == _length)
	{
		return GEString{ *this };
	}

	const auto length = end - start + 1;
	auto* slice = new wchar_t[length + 1];
	slice[length] = '\0';
	memcpy(slice, _string + start, length * sizeof(wchar_t));

	return GEString{ slice };
}

GEString GEString::trim() const
{
	size_t start_index = 0;
	size_t end_index = _length;

	for(size_t i = 0; i < _length; i++)
	{
		if(_string[i] != ' ')
		{
			start_index = i;
			break;
		}
	}
	for (size_t i = _length; i --> 0 ;)
	{
		if (_string[i] != ' ')
		{
			end_index = i;
			break;
		}
	}

	return slice(start_index, end_index);
}

GEString GEString::operator+(GEString const& ref) const
{
	const auto length = this->_length + ref._length;
	auto new_string = new wchar_t[length + 1];
	new_string[length] = '\0';
	memcpy(new_string, _string, _length * sizeof(wchar_t));
	memcpy(new_string + _length, ref._string, ref._length * sizeof(wchar_t));
	return GEString{ new_string };
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

const wchar_t* GEString::data()
{
	return _string;
}

