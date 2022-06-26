#include "Encoder.h"

void XML::Encoder::encode(Node& node)
{
	out << "<" << node.tag();
	node.attributes().each([&](const char* key, const char* value)
		{
			out << " " << key << "=\"" << value << "\"";
		});

	if(node.null())
	{
		out << "/>";
	}else
	{
		out << ">";

		if (node.isString())
		{
			out << node.string();
		}
		if (node.isArray())
		{
			auto* arr = &node.array();

			for (size_t i = 0; i < arr->size(); i++)
			{
				encode(arr->operator[](i));
			}
		}
		out << "</" << node.tag() << ">";
	}
}

XML::Encoder::Encoder(XML::Document& document)
{
	out << R"(<?xml version="1.0" encoding="UTF-8" ?>)";
	encode(document.root_node);
}
