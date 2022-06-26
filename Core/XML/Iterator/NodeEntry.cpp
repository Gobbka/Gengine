#include "NodeEntry.h"
#include "../XMLCommon.h"

bool strings_equal(const char* ptr1, const char* ptr2)
{
	for (int i = 0;; i++)
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

XML::NodeEntry::NodeEntry(Node* node, GEString tag_filter)
	: _tag_filter(std::move(tag_filter))
	, _nodes(&node->array())
	, _current_iteration(0)
{
	next();
}

void XML::NodeEntry::reset()
{
	_current_iteration = 0;
	next();
}

bool XML::NodeEntry::next()
{
	for (; _current_iteration < _nodes->size(); _current_iteration++)
	{
		auto* node = &_nodes->operator[](_current_iteration);
		if(_tag_filter == node->tag())
		{
			return true;
		}
	}

	return false;
}

XML::Node* XML::NodeEntry::get() const
{
	if(_current_iteration < _nodes->size())
	{
		return &_nodes->operator[](_current_iteration);
	}
	return nullptr;
}