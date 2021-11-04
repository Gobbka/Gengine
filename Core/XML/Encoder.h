#pragma once
#include "XMLCommon.h"
#include <ostream>
#include <sstream>

namespace XML
{
	class __declspec(dllexport) Encoder
	{
		std::ostringstream out;
		void encode(Node& node);
	public:
		explicit Encoder(XML::Document& document);
		auto text() const { return out.str(); }
		void print() const;
	};
}

