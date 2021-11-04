#include "XMLEncoder.h"
#include <iostream>

void XML::XMLEncoder::encode(Node& node)
{
	out << "<" << node.tag();
	node.attributes().each([&](const char* key, const char* value)
		{
			out << " " << key << "=\"" << value << "\"";
		});
	out << ">";

	if(node.is_string())
	{
		out << node.string();
	}
	if(node.is_array())
	{
		auto* arr = &node.array();

		for(size_t i =0;i < arr->size();i++)
		{
			encode(arr->operator[](i));
		}
	}
	out << "</" << node.tag() << ">";
}

XML::XMLEncoder::XMLEncoder(XML::Document& document)
{
	out << R"(<?xml version="1.0" encoding="UTF-8" ?>)""\n";
	encode(document.base_node);
}

void XML::XMLEncoder::print() const
{
	std::cout << out.str().c_str();
}
