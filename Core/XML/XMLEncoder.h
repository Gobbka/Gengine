#pragma once
#include "XMLCommon.h"
#include <ostream>
#include <sstream>

namespace XML
{
	class __declspec(dllexport) XMLEncoder
	{
		std::ostringstream out;
		void encode(Node node);
	public:
		explicit XMLEncoder(XML::Document& document);
		const char* text();
		void print() const;
	};
}

