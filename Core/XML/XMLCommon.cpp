#include "XMLCommon.h"

size_t quick_pow10(size_t n)
{
	static size_t pow10[]
	{
		1,10,100,1000,10000,100000,1000000,10000000,100000000,
		1000000000,10000000000,100000000000,
	};

	return pow10[n];
}

bool strings_equal(const char*ptr1,char*ptr2)
{
	for(int i=0;;i++)
	{
		const auto first_char = ptr1[i];
		const auto second_char = ptr2[i];

		if (first_char == second_char == '\0')
			return true;

		if (first_char == '\0' || second_char == '\0')
			break;

		if (first_char != second_char)
			break;
	}

	return false;
}

XML::NodeEntry::NodeEntry(Node* node, const char* tag_filter)
	: _tag_filter(tag_filter)
	, _nodes(&node->value.array())
	, _current_iteration(0)
{
	next();
}

bool XML::NodeEntry::next()
{
	for(; _current_iteration < _nodes->size(); _current_iteration++)
	{
		const auto* node = &_nodes->operator[](_current_iteration);
		if(strings_equal(_tag_filter, node->tag))
		{
			return true;
		}
	}

	return false;
}

XML::Node* XML::NodeEntry::get() const
{
	return &_nodes->operator[](_current_iteration);
}

XML::Number XML::NodeValue::parse_number() const
{
	if (_type != ValueType::string)
		throw std::exception("Value type is not a string");

	const auto* text = (char*)_bytes;
	bool negative = false;
	Number value =0;
	const auto length = strlen(text);

	size_t iteration = 0;

	if(text[iteration] == '-')
	{
		negative = true;
		iteration++;
	}

	for(; iteration < length; iteration++)
	{
		const auto symbol = text[iteration];
#ifdef UNICODE
		if(symbol >= 0x30 && symbol <=0x39) // from 0 to 9 in unicode
		{
			value += (symbol - 0x30) * quick_pow10(length- iteration -1u);
		}
#else
		static_assert(false, "Unsuported");
#endif
	}

	if(negative)
		value = ~value + 1;

	return value;
}

const char* XML::NodeValue::string() const
{
	if(_type == ValueType::string)
		return (const char*)_bytes;
	throw std::exception("Value type is not a string");
}

void XML::NodeValue::append(Node node) const
{
	if (!is_array())
		throw std::exception("Value type is not a node array");

	array().push_back(std::move(node));
}

std::vector<XML::Node>& XML::NodeValue::array() const
{
	if(_type == ValueType::array)
		return *(std::vector<Node>*)_bytes;
	throw std::exception("Value type is not a node array");
}

bool XML::NodeValue::is_string() const
{
	return _type == ValueType::string;
}

bool XML::NodeValue::is_array() const
{
	return _type == ValueType::array;
}

XML::NodeValue::NodeValue(ValueType type, void* bytes)
	: _bytes(bytes)
	, _type(type)
{}

XML::Node::Node(const char* tag, size_t number)
	: value(ValueType::string,new size_t)
{
	const auto tag_len = strlen(tag);
	this->tag = new char[tag_len + 1];
	memcpy(this->tag, tag, tag_len + 1);
}

XML::Node::Node(char* tag, size_t number)
	: tag(tag)
	, value(ValueType::string, new size_t)
{}

XML::Node::Node(const char* tag, const char* value)
	: value(ValueType::string,nullptr)
{
	const auto tag_len = strlen(tag);
	this->tag = new char[tag_len + 1];
	memcpy(this->tag, tag, tag_len + 1);

	const auto value_len = strlen(value);
	this->value._bytes = new char[value_len+1];
	memcpy(this->value._bytes, value, value_len+1);
}

XML::Node::Node(const char* tag, char* value)
	: value(ValueType::string,value)
{
	const auto tag_len = strlen(tag);
	this->tag = new char[tag_len + 1];
	memcpy(this->tag, tag, tag_len + 1);
}

XML::Node::Node(char* tag, char* value)
	: tag(tag)
	, value(ValueType::string,value)
{}

XML::Node::Node(const char* tag)
	: tag(nullptr)
	, value(ValueType::array, new std::vector<Node>)
{
	const auto tag_len = strlen(tag);
	this->tag = new char[tag_len + 1];
	memcpy(this->tag, tag, tag_len + 1);
}

XML::Node::Node(char* tag)
	: tag(tag)
	, value(ValueType::array,new std::vector<Node>)
{}

XML::Node::Node(Node&& other) noexcept
	: tag(other.tag)
	, value(other.value)
{
	other.tag = nullptr;
	other.value._bytes = nullptr;
}

XML::Node& XML::Node::operator=(Node&& other) noexcept
{
	tag = other.tag;
	value = other.value;

	other.tag = nullptr;
	other.value._bytes = nullptr;

	return*this;
}

XML::Node::~Node()
{
	if(value.is_array())
	{
		const auto*vector = &value.array();
		delete vector;
	}

	delete[]tag;
}

XML::Node* XML::Node::find_by_tag_first(const char* child_tag)
{
	return NodeEntry( this, child_tag ).get();
}

XML::NodeEntry XML::Node::find_by_tag(const char* child_tag)
{
	return NodeEntry( this,child_tag );
}

XML::Document::Document(Node base_node)
	: base_node(std::move(base_node))
{

}
