#pragma once

#include <vector>
#include <string_view>

namespace yol::detail {
	template<class Traits>
	class basic_grapheme_cluster_string_base {
		using cluster_traits = Traits;
		using char_type = typename cluster_traits::char_type;

	protected:
		basic_grapheme_cluster_string_base() = default;
		basic_grapheme_cluster_string_base(std::basic_string_view<char_type> text)
			: m_text(text.begin(), text.end())
		{
			m_text.push_back(cluster_traits::null_char);
		}

	protected:
		std::vector<char_type> m_text;
	};
}
