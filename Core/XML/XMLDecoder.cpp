#include "XMLDecoder.h"

struct NodeBorder
{
	char* node_start;
	char* node_end;
	char* value_start;
	char* value_end;
};

void copy_pure_xml(const char*src,char*dst)
{
	size_t j = 0;
	for(;*src;src++)
	{
		const auto symbol = *src;
		if(symbol < 0x20)
			continue;

		dst[j] = symbol;
		j++;
	}
	dst[j] = '\0';
}

NodeBorder extract_node(char*text)
{
	NodeBorder border{text,nullptr,nullptr,nullptr};

	for(;*text!='>';text++){}
	border.value_start = text+1;

	for (int opened_tags = 0; *text; text++)
	{
		const auto symbol = *text;
		if(symbol=='<')
		{
			opened_tags++;
			continue;
		}

		if(symbol == '/')
		{
			opened_tags -= 2;
		}

		if(opened_tags < 0)
		{
			break;
		}
	}

	border.value_end = text-1;
	for (; *text != '>'; text++){}
	border.node_end = text;

	return border;
}



XML::Node decode_node(NodeBorder border)
{
	//text++;
	//char* start_pos = text;
	//while(*text != ' ' && *text != '>')
	//{
	//	text++;
	//}
	//auto* tag = new char[text - start_pos+1];
	//memcpy(tag, start_pos, text - start_pos);
	//tag[text - start_pos] = 0;

	//int opened_tags=0;
	//for(size_t i =0;text[i];i++)
	//{
	//	auto symbol = text[i];
	//	if(symbol=='<')
	//	{
	//		opened_tags++;
	//		continue;
	//	}
	//	if(symbol=='/')
	//	{
	//		opened_tags-=2;
	//		if(opened_tags == -1)
	//		{
	//			
	//			int i = 228;
	//		}
	//	}
	//}

 //	return XML::Node(tag);
	throw std::exception("Invalid xml string");
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
			extract_node(&pure_xml[i + 1]);
			
			throw std::exception("Invalid xml string");
		}
	}

	throw std::exception("Invalid xml string");
}

