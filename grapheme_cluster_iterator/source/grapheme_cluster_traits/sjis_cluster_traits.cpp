
#include "stdafx.h"
#include "../../include/grapheme_cluster_string.h"

namespace {
	inline bool iskanji(unsigned char c)
	{
		return (c >= 0x81 && c <= 0x9f) || (c >= 0xe0 && c <= 0xfc);
	}
}


namespace yol::grapheme_cluster_traits {

	std::size_t sjis_traits::calc_codepoint_size(string_view text)
	{
		if (text.length() <= 1) {
			return text.length();
		}

		return iskanji(text[0]) ? 2 : 1;
	}

	auto sjis_traits::get_codepoint(string_view text) -> codepoint_type
	{
		if (text.length() == 0) {
			return 0;
		}

		codepoint_type c = static_cast<std::uint8_t>(text[0]);
		if (calc_cluster_size(text) == 2) {
			return (c << 8) | static_cast<std::uint8_t>(text[1]);
		} else {
			return c;
		}
	}

	std::size_t sjis_traits::calc_cluster_size(string_view text)
	{
		if (text.length() <= 1) {
			return text.length();
		}

		if (text[0] == '\r' && text[1] == '\n') {
			return 2;
		}

		return calc_codepoint_size(text);
	}
}
