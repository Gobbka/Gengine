#pragma once
#include <vector>

namespace XML
{
	typedef long long Number;

	struct Node;

	class __declspec(dllexport) NodeEntry
	{
		const char* _tag_filter;
		std::vector<Node>* _nodes;
		size_t _current_iteration;
	public:
		explicit NodeEntry(Node* node,const char* tag_filter);

		bool next();
		Node* get() const;
	};

	enum class ValueType
	{
		string,
		array
	};

	class __declspec(dllexport) NodeValue {
		friend Node;

		void*_bytes;
		ValueType _type;
	public:
		Number parse_number() const;
		const char* string() const;
		void append(Node node) const;
		std::vector<Node>& array() const;

		bool is_string() const;
		bool is_array() const;

		NodeValue(ValueType type,void*bytes);
	};

	struct __declspec(dllexport) Node : NodeValue
	{
		char* tag;

		Node() = delete;

		Node(const char* tag, size_t number);
		Node(char* tag, size_t number);
		Node(const char* tag, const char* value);
		Node(const char* tag, char* value);
		Node(char* tag, char* value);
		explicit Node(const char* tag);
		explicit Node(char* tag);
		Node(Node&& other) noexcept;
		~Node();

		Node& operator=(Node&& other) noexcept;

		Node* find_by_tag_first(const char* child_tag);
		NodeEntry find_by_tag(const char* child_tag);
	};

	struct __declspec(dllexport) Document
	{
		Node base_node;

		explicit Document(Node base_node);
	};
}
