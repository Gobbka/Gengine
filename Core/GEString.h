#pragma once
#include <ostream>

class __declspec(dllexport) GEString
{
	size_t _length;
	wchar_t* _string;
public:
	explicit GEString(wchar_t*& string);
	explicit GEString(const wchar_t* string);
	GEString(GEString& copy);
	GEString(GEString&& move) noexcept;
	GEString& operator=(GEString const& copy);
	GEString& operator=(GEString&& move) noexcept;
	~GEString();

	bool operator==(GEString& other) const;
	friend std::ostream& operator<<(std::ostream& os, const GEString& foo);
};
