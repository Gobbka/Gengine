#pragma once
#include <functional>
#include <map>
#include <vector>

#include "Iterator/NodeEntry.h"
#include "../GEString.h"

class GEString;

namespace XML
{
	typedef long long Number;

	enum class ValueType
	{
		unknown,
		string,
		array,
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
		char* bytes;
		ValueType type;
	public:
		Number parse_number() const;
		GEString& string() const;
		std::vector<Node>& array() const;

		Node* append(Node node);
		void set_inner_text(GEString text);
		void clear();

		bool is_string() const;
		bool is_array() const;
		bool null() const;

		NodeValue();
		NodeValue(NodeValue&& other) noexcept;
	};

	class __declspec(dllexport) Node : public NodeValue
	{
		GEString _tag;
		Attributes _attributes;
		Node* _parent_node;
	public:

		GEString& tag();
		Attributes& attributes();

		Node() = delete;
		explicit Node(GEString tag,Node* parent_node);
		Node(Node&& other) noexcept;
		~Node() noexcept;

		Node& operator=(Node&& other) noexcept;

		NodeEntry find_by_tag(GEString child_tag);
		Node* parent_node();
	};

	struct __declspec(dllexport) Document
	{
		Node root_node;

		explicit Document(Node root_node);
	};
}
