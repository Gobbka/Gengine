#include "XMLDecoder.h"

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

void extract_node(char*text)
{
	char* end=nullptr;
	int tags_opened = 0;
	for(size_t i = 0;text[i];i++)
	{
		auto symbol = text[i];
		if(symbol == '<')
		{
			tags_opened++;
			continue;
		}
		if(symbol == '/')
		{
			if(i % 2 == 0)
				tags_opened-=2;
			else
				tags_opened--;

			if(tags_opened <= 0)
			{
				end = text + i;
				break;
			}
		}
	}

	end++;
}


XML::Document XML::decode_document(const char* str)
{
	const auto length = strlen(str);
	auto* pure_xml = new char[length + 1];
	copy_pure_xml(str, pure_xml);

	char* xml_header = pure_xml;
	char* xml_body = nullptr;

	for (size_t i = 0; pure_xml[i]; i++)
	{
		if (pure_xml[i] == '>')
		{
			xml_body = pure_xml + i + 1;
			break;
		}
	}

	extract_node(xml_body);

	throw std::exception("Invalid xml string");
}

