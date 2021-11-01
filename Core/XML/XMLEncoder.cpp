#include "XMLEncoder.h"
#include <iostream>

void XML::XMLEncoder::encode(Node node)
{
	//for(const auto child : node.children)
	//{
	//	out << "<" << child.tag << ">";
	//	encode(node);
	//	out << "</" << child.tag << ">";
	//}
}

XML::XMLEncoder::XMLEncoder(XML::Document& document)
{
	out << R"(<?xml version="1.0" encoding="UTF-8" ?>)";
	encode(document.base_node);
}

void XML::XMLEncoder::print() const
{
	std::cout << out.str().c_str();
}
