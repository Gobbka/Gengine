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

bool strings_equal(const char*ptr1,const char*ptr2)
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
	, _nodes(&node->array())
	, _current_iteration(0)
{
	next();
}

bool XML::NodeEntry::next()
{
	for(; _current_iteration < _nodes->size(); _current_iteration++)
	{
		const auto* node = &_nodes->operator[](_current_iteration);
		if(strings_equal(_tag_filter, node->tag()))
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

XML::Attributes::Attributes(Attributes&& other) noexcept
{
	_attributes = std::move(other._attributes);
}

void XML::Attributes::add(char* key, char* value)
{
	_attributes[key] = value;
}

void XML::Attributes::add(const char* key, const char* value)
{
	const auto key_len = strlen(key);
	const auto value_len = strlen(value);

	auto* new_key = new char[key_len+1];
	auto* new_value = new char[value_len+1];

	memcpy(new_key, key, key_len + 1);
	memcpy(new_value, value, value_len + 1);

	_attributes[new_key] = new_value;
}

char* XML::Attributes::get(const char* key)
{
	return _attributes[(char*)key];
}

void XML::Attributes::each(std::function<void(const char* key, const char* value)> callback)
{
	for(const auto pair : _attributes)
	{
		callback(pair.first, pair.second);
	}
}


XML::Number XML::NodeValue::parse_number() const
{
	if (type != ValueType::string)
		throw std::exception("Value type is not a string");

	const auto* text = (char*)bytes;
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
	if(type == ValueType::string)
		return (const char*)bytes;
	throw std::exception("Value type is not a string");
}

void XML::NodeValue::append(Node&& node) const
{
	if (!is_array())
		throw std::exception("Value type is not a node array");

	array().push_back(std::move(node));
}

std::vector<XML::Node>& XML::NodeValue::array() const
{
	if(type == ValueType::array)
		return *(std::vector<Node>*)bytes;
	throw std::exception("Value type is not a node array");
}

bool XML::NodeValue::is_string() const
{
	return type == ValueType::string;
}

bool XML::NodeValue::is_array() const
{
	return type == ValueType::array;
}

bool XML::NodeValue::null() const
{
	return bytes == nullptr;
}

XML::NodeValue::NodeValue(ValueType type, void* bytes)
	: bytes(bytes)
	, type(type)
{}

XML::NodeValue::NodeValue(NodeValue&& other) noexcept
	: bytes(other.bytes)
	, type(other.type)
{
	other.bytes = nullptr;
}

XML::Tag::Tag(char* name)
	: value(name)
{}

XML::Tag::Tag(const char* name)
	: value(nullptr)
{
	const auto src_len = strlen(name);
	value = new char[src_len + 1];
	memcpy(value, name, src_len + 1);
}

XML::IValue::IValue(char* value)
	: value(value)
{}

XML::ArrayValue::ArrayValue()
	: IValue((char*)new std::vector<Node>)
{}

XML::NullValue::NullValue()
	: IValue(nullptr)
{}

XML::StringValue::StringValue(char* value)
	: IValue(value)
{}

XML::StringValue::StringValue(const char* value)
	: IValue(nullptr)
{
	const auto src_len = strlen(value);
	this->value = new char[src_len + 1];
	memcpy(this->value, value, src_len + 1);
}

XML::NumberValue::NumberValue(Number num)
	: IValue(nullptr)
{}

const char* XML::Node::tag() const
{
	return _tag;
}

XML::Attributes& XML::Node::attributes()
{
	return _attributes;
}

XML::Node::Node(Tag tag, IValue value)
	: NodeValue(ValueType::string,value.value)
	, _tag(tag.value)
{}

XML::Node::Node(Tag tag, ArrayValue value)
	: NodeValue(ValueType::array,value.value)
	, _tag(tag.value)
{}

XML::Node::Node(Node&& other) noexcept
	: NodeValue(std::move(other))
	, _tag(other._tag)
	, _attributes(std::move(other._attributes))
{
	other._tag = nullptr;
	other.bytes = nullptr;
}

XML::Node& XML::Node::operator=(Node&& other) noexcept
{
	_tag = other._tag;
	bytes = other.bytes;
	type = other.type;

	other._tag = nullptr;
	other.bytes = nullptr;

	return*this;
}

XML::Node::~Node() noexcept
{
	if(is_array())
	{
		const auto*vector = &array();
		delete vector;
	}

	delete[]_tag;
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
