#pragma once
#include <vector>
#include "../../GEString.h"

namespace XML
{
	class Node;

	class __declspec(dllexport) NodeEntry
	{
		GEString _tag_filter;
		std::vector<Node>* _nodes;
		size_t _current_iteration;
	public:
		explicit NodeEntry(Node* node,GEString& tag_filter);

		void reset();
		bool next();
		Node* get() const;
	};
}
