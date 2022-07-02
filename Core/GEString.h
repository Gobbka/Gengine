#pragma once
#include <ostream>

class __declspec(dllexport) GEString
{
	size_t _length;
	wchar_t* _string;
public:
	explicit GEString(wchar_t*& string);
	explicit GEString(const wchar_t* string);
	GEString(GEString const& copy);
	GEString(GEString&& move) noexcept;
	GEString& operator=(GEString const& copy);
	GEString& operator=(GEString&& move) noexcept;
	~GEString();

	bool operator==(GEString& other) const;
	bool operator==(const wchar_t* other) const;
	friend std::ostream& operator<<(std::ostream& os, const GEString& foo);

	bool endsWith(const wchar_t* search_string) const;
	bool startsWith(const wchar_t* search_string) const;

	static GEString copy(wchar_t* string);
	GEString slice(size_t start, size_t end) const;
	GEString trim() const;
	GEString operator+(GEString const& ref) const;
};
