#pragma once
#include "Common.h"

namespace JSON
{
	Node __declspec(dllexport) decode(const wchar_t* text,unsigned max_depth = 255);
}
