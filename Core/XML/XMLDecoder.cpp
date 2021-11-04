#include "XMLDecoder.h"

void copy_pure_xml(const char*src,char*dst)
{
	for(size_t j=0;*src;src++)
	{
		const auto symbol = *src;
		if(symbol < 0x20)
			continue;

		dst[j] = symbol;
		j++;
	}
}

XML::Node decode_node(char*text)
{
	text++;
	char* start_pos = text;
	while(*text != ' ' && *text != '>')
	{
		text++;
	}
	auto* tag = new char[text - start_pos+1];
	memcpy(tag, start_pos, text - start_pos);
	tag[text - start_pos] = 0;

 	return XML::Node(tag);
}

XML::Document XML::decode_document(const char* str)
{
	const auto length = strlen(str);
	auto* pure_xml = new char[length + 1];
	copy_pure_xml(str, pure_xml);

	for (size_t i = 0; pure_xml[i]; i++)
	{
		if (pure_xml[i] == '>')
		{
			delete[]pure_xml;
			return Document(decode_node(&((char*)pure_xml)[i+1]));
		}
	}

	throw std::exception("Invalid xml string");
}

