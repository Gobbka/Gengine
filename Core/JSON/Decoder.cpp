#include "Decoder.h"

#include <vector>

struct DecoderNode
{
	struct
	{
		JSON::NodeType type = JSON::NodeType::unknown;
		size_t value;
	} key;
	size_t value;
};

struct NodeDescription
{
	JSON::NodeType type;
	std::vector<DecoderNode> values;
};

JSON::NodeType get_value_type(const wchar_t* ptr)
{
	if (*ptr == '[')
		return JSON::NodeType::array;
	if (*ptr == '{')
		return JSON::NodeType::map;
	if (*ptr == '"')
		return JSON::NodeType::string;
	if (*ptr >= '0' && *ptr <= '9')
		return JSON::NodeType::number;
	return JSON::NodeType::unknown;
}

JSON::NodeType get_node_type(wchar_t open_bracket)
{
	switch (open_bracket)
	{
	case '{': return JSON::NodeType::map;
	case '[': return JSON::NodeType::array;
	default: return JSON::NodeType::unknown;
	}
}

wchar_t get_close_bracket(wchar_t open_bracket)
{
	switch (open_bracket)
	{
		case '{': return '}';
		case '[': return ']';
		default: return 0;
	}
}

unsigned parse(const wchar_t* text,unsigned&current_depth,std::vector<NodeDescription>&nodes)
{
	for(unsigned i = 0; text[i]; i++)
	{
		wchar_t symbol = text[i];

		nodes[current_depth].type = get_value_type(text);

		if(nodes[current_depth].type == JSON::NodeType::number)
		{
			unsigned value = 0,k = 1;
			do
			{
				value += (text[i] - 48) * k;
				i++;
				k *= 10;
			} while (text[i] != ',');
		}

		if (nodes[current_depth].type == JSON::NodeType::array)
			parse(++text, current_depth, nodes);
		if (nodes[current_depth].type == JSON::NodeType::map)
			parse(++text, current_depth, nodes);
	}
	return 0;
}

JSON::Node JSON::decode(const wchar_t* text)
{
	std::vector<NodeDescription> nodes(255);

	unsigned current_depth = 0;
	parse(text, current_depth, nodes);


	return Node(false);
}
