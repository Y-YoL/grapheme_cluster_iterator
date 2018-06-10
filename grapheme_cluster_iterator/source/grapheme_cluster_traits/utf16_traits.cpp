
#include "stdafx.h"
#include "../../include/grapheme_cluster_traits.h"
#include <icu.h>

namespace yol::grapheme_cluster_traits {

	std::size_t utf16_traits::calc_codepoint_size(string_view text)
	{
		if (text.length() == 0) {
			return 0;
		}

		auto cp = get_codepoint(text);
		return U16_LENGTH(cp);
	}

	auto utf16_traits::get_codepoint(string_view text) -> codepoint_type
	{
		if (text.length() == 0) {
			return 0;
		}

		char32_t c = {};
		U16_GET(text, 0, 0, text.length(), c);
		return c;
	}
}
