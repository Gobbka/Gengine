#pragma once
#include <functional>
#include <map>
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

	class __declspec(dllexport) Attributes {
		std::map<char*, char*> _attributes;
	public:
		Attributes() = default;
		Attributes(Attributes&& other) noexcept;

		void add(char* key, char* value);
		void add(const char* key,const char* value);
		char* get(const char* key);

		void each(std::function<void(const char*key, const char*value)> callback);
	};

	class __declspec(dllexport) NodeValue {
	protected:
		void*bytes;
		ValueType type;
	public:
		Number parse_number() const;
		const char* string() const;
		void append(Node&& node) const;
		std::vector<Node>& array() const;

		bool is_string() const;
		bool is_array() const;
		bool null() const;

		NodeValue(ValueType type,void*bytes);
		NodeValue(NodeValue&& other) noexcept;
	};

	struct __declspec(dllexport) Tag
	{
		char* value;

		Tag(char* name);
		Tag(const char* name);
	};

	struct __declspec(dllexport) IValue
	{
		char* value;

		IValue(char* value);
	};

	struct __declspec(dllexport) ArrayValue : IValue
	{
		ArrayValue();
	};
	struct __declspec(dllexport) NullValue : IValue
	{
		NullValue();
	};
	struct __declspec(dllexport) StringValue : IValue
	{
		StringValue(char* value);
		StringValue(const char* value);
	};
	struct __declspec(dllexport) NumberValue : IValue
	{
		NumberValue(Number num);
	};

	class __declspec(dllexport) Node : public NodeValue
	{
		char* _tag;
		Attributes _attributes;
	public:

		const char* tag() const;
		Attributes& attributes();

		Node() = delete;
		Node(Tag tag, IValue value);
		Node(Tag tag, ArrayValue value);
		Node(Node&& other) noexcept;
		~Node() noexcept;

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
