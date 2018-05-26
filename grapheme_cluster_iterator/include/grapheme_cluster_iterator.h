#pragma once

#include <vector>
#include <string_view>
#include "grapheme_cluster_traits.h"

namespace yol {
	template<class Traits>
	class grapheme_cluster_iterator {
		using cluster_traits = Traits;
		using char_type = typename cluster_traits::char_type;

	public:
		grapheme_cluster_iterator() = default;
		grapheme_cluster_iterator(std::basic_string_view<char_type> text)
			: m_text(text.begin(), text.end())
		{
		}

	private:
		std::vector<char_type> m_text;
	};
}
