#pragma once

namespace UI
{
	struct ElementDescription
	{
		// flags

		bool can_be_parent : 1;
		bool has_text : 1;

		// other

		const char* string_name;

		ElementDescription(bool can_be_parent, const char* string_name, bool has_text = false);
	};

}
