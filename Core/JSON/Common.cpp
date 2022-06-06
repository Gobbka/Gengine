#include "Common.h"

#include <cstring>

JSON::Node::Node(size_t value)
	: _value((char*)value)
	, _type(NodeType::number)
{
}

JSON::Node::Node(bool value)
	: _value((char*)value)
	, _type(NodeType::boolean)
{
}

JSON::Node::Node(char*& value)
	: _value(nullptr)
	, _type(NodeType::string)
{
	
}

size_t JSON::Node::number() const
{
	if(_type == NodeType::number)
	{
		return (size_t)_value;
	}
	return 0;
}
