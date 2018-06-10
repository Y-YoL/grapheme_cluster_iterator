
#include "stdafx.h"
#include "../../include/grapheme_cluster_traits.h"

namespace yol::grapheme_cluster_traits {

	std::size_t utf16_traits::calc_codepoint_size(std::basic_string_view<char_type> c)
	{
		return 1;
	}
}
