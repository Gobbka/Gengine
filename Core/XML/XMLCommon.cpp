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

XML::Attributes::Attributes(Attributes&& other) noexcept
	: _attributes(std::move(other._attributes))
{
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

GEString& XML::NodeValue::string() const
{
	if(type == ValueType::string)
		return *(GEString*)bytes;
	throw std::exception("Value type is not a string");
}

XML::Node* XML::NodeValue::append(Node node)
{
	if(bytes == nullptr)
	{
		bytes = (char*)new std::vector<Node>;
		type = ValueType::array;
	}

	if (!is_array())
		throw std::exception("Value type is not a node array");

	array().push_back(std::move(node));
	return &array()[array().size() - 1];
}

void XML::NodeValue::set_inner_text(GEString text)
{
	if(bytes != nullptr)
	{
		this->clear();
	}

	bytes = (char*)new GEString(std::move(text));
	type = ValueType::string;
}

void XML::NodeValue::clear()
{
	switch (type)
	{
	case ValueType::unknown:
		delete[] bytes;
		break;
	case ValueType::string:
		delete (GEString*)bytes;
		break;
	case ValueType::array:
		delete (std::vector<Node>*)bytes;
		break;
	}

	bytes = nullptr;
	type = ValueType::unknown;
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

XML::NodeValue::NodeValue()
	: bytes(nullptr)
	, type(ValueType::unknown)
{
}

XML::NodeValue::NodeValue(NodeValue&& other) noexcept
	: bytes(other.bytes)
	, type(other.type)
{
	other.bytes = nullptr;
	other.type = ValueType::unknown;
}

GEString& XML::Node::tag()
{
	return _tag;
}

XML::Attributes& XML::Node::attributes()
{
	return _attributes;
}

XML::Node::Node(GEString tag,Node* parent_node)
	: NodeValue()
	, _tag(std::move(tag))
	, _parent_node(parent_node)
{
}

XML::Node::Node(Node&& other) noexcept
	: NodeValue(std::move(other))
	, _tag(std::move(other._tag))
	, _attributes(std::move(other._attributes))
	, _parent_node(other._parent_node)
{
	other.bytes = nullptr;
	other._parent_node = nullptr;
}

XML::Node& XML::Node::operator=(Node&& other) noexcept
{
	_tag = std::move(other._tag);
	bytes = other.bytes;
	type = other.type;
	_parent_node = other._parent_node;

	other._parent_node = nullptr;
	other.clear();

	return*this;
}

XML::Node::~Node() noexcept
{
	clear();
}

XML::NodeEntry XML::Node::find_by_tag(GEString child_tag)
{
	return NodeEntry( this,std::move(child_tag) );
}

XML::Node* XML::Node::parent_node()
{
	return _parent_node;
}

XML::Document::Document(Node root_node)
	: root_node(std::move(root_node))
{

}
