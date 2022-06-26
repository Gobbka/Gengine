#include "XMLDecoder.h"

#include <iostream>
#include <regex>

wchar_t* extract_string(const wchar_t* start, const wchar_t* end)
{
	if (end >= start)
	{
		const auto length = end - start;
		auto* string = new wchar_t[length + 1];
		string[length] = '\0';
		memcpy(string, start, length * sizeof(wchar_t));
		return string;
	}
	return nullptr;
}

wchar_t* copy_string(wchar_t* string)
{
	const auto length = wcslen(string);
	auto* copy = new wchar_t[length + 1];
	copy[length] = '\0';
	memcpy(copy, string, length * sizeof(wchar_t));

	return copy;
}

wchar_t* skip_spaces(wchar_t* string)
{
	while((*string == ' ' || *string == '\t') && *string++){}
	return string;
}

wchar_t* getQuotEnd(wchar_t* start)
{
	while (auto symbol = *start++)
	{
		if (symbol == '\\')
		{
			start++;
			continue;
		}
		if (symbol == '"')
		{
			return start;
		}
	}
	return nullptr;
}

struct ParsedXmlPart
{
	wchar_t* name;
	enum class Role
	{
		OpenTag,
		CloseTag,
		SingleTag,
		Value
	} role;

	ParsedXmlPart(wchar_t* part)
		: name(getName(part))
		, role(getRole(part))
	{
		if(role == Role::Value)
		{
			name = copy_string(part);
		}
	}

	static wchar_t* getNameEnd(wchar_t* tag)
	{
		while (*tag++ && *tag != ' ' && *tag != '>')
		{
		}
		return tag;
	}

	static wchar_t* getName(wchar_t* part)
	{
		if(*part == '<')
		{
			part++;
		}

		if (*part == '/')
		{
			part++;
		}

		return extract_string(part, getNameEnd(part));
	}

	static Role getRole(wchar_t* part)
	{
		if (*part == '<')
		{
			if (*(part + 1) == '/')
			{
				return Role::CloseTag;
			}
			if (part[wcslen(part) - 2] == '/')
			{
				return Role::SingleTag;
			}
			
			return Role::OpenTag;
		}

		return Role::Value;
	}
};

void copy_pure_xml(const wchar_t*src,wchar_t*dst)
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

const wchar_t* getXmlHeaderEnd(const wchar_t* text)
{
	while(*text ++)
	{
		if (*text == '>')
			return text;
	}

	throw std::exception("Invalid xml string");
}

const wchar_t* getNextLt(const wchar_t* text)
{
	while(auto symbol = *text++)
	{
		if (symbol == '<')
			return text;
	}

	return nullptr;
}

const wchar_t* getNextRt(const wchar_t* text)
{
	while (auto symbol = *text++)
	{
		if (symbol == '>')
			return text;
	}

	return nullptr;
}

bool parseXmlParts(std::vector<wchar_t*>& parts, std::vector<ParsedXmlPart>& out)
{
	for(auto* part : parts)
	{
		out.emplace_back(ParsedXmlPart(part));
		delete[] part;
	}

	return true;
}

bool splitXmlBody(const wchar_t*xml,std::vector<wchar_t*>& out)
{
	const wchar_t* element_start = xml;

	while (true) {
		const wchar_t* element_end;

		if (*element_start == '<')
		{
			element_end = getNextRt(element_start);
		}
		else
		{
			element_end = getNextLt(element_start);
			if (element_end)
			{
				element_end -= 1;
			}
		}

		if (element_end == nullptr)
		{
			break;
		}

		out.push_back(extract_string(element_start, element_end));
		element_start = element_end;
	}

	return true;
}

XML::Document XML::decode_document(const wchar_t* str)
{
	const auto length = wcslen(str);
	auto* pure_xml = new wchar_t[length + 1];
	copy_pure_xml(str, pure_xml);

	std::vector<wchar_t*> parts;
	std::vector<ParsedXmlPart> parsed_parts;

	auto* xml_body = getXmlHeaderEnd(pure_xml) + 1;

	parts.push_back(extract_string(pure_xml, xml_body));

	if(splitXmlBody(xml_body, parts) && parseXmlParts(parts,parsed_parts))
	{
		Document document{ Node(GEString(parsed_parts[0].name),nullptr) };
		auto* current_node = &document.root_node;
		for(auto i = 1u;i < parsed_parts.size();i ++)
		{
			auto& part = parsed_parts[i];
			if(part.role == ParsedXmlPart::Role::OpenTag)
			{
				current_node = current_node->append(Node(GEString(part.name), current_node));
			}
			if(part.role == ParsedXmlPart::Role::CloseTag)
			{
				current_node = current_node->parentNode();
			}
			if(part.role == ParsedXmlPart::Role::SingleTag)
			{
				current_node->append(Node(GEString(part.name), current_node));
			}
			if(part.role == ParsedXmlPart::Role::Value)
			{
				current_node->setInnerText(GEString{ part.name });
			}
		}

		return document;
	}

	throw std::exception("Invalid xml string");
}

