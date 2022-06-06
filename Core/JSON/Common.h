#pragma once

namespace JSON
{
	enum class NodeType
	{
		unknown,
		number,
		string,
		boolean,
		map,
		array
	};

	class __declspec(dllexport) Node
	{
		static_assert(sizeof(char*) == sizeof(size_t), "Pointer and size_t have not the same size");
		static_assert(sizeof(char*) > sizeof(bool), "Boolean size more than pointer size");

		char* _value;
		NodeType _type;
	public:
		explicit Node(size_t value);
		explicit Node(bool value);
		explicit Node(char* & value);
		explicit Node(char* && value);

		size_t number() const;
		const wchar_t* string();
		bool boolean();
	};
}
