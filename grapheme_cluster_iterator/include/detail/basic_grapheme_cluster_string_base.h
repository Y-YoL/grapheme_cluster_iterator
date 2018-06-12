#pragma once

#include <vector>
#include <string_view>

namespace yol::detail {
	template<class Traits>
	class basic_grapheme_cluster_string_base {
		using cluster_traits = Traits;
		using char_type = typename cluster_traits::char_type;
		using buffer_type = std::basic_string<char_type>;

	protected:
		basic_grapheme_cluster_string_base() = default;
		basic_grapheme_cluster_string_base(std::basic_string_view<char_type> text)
			: m_text(text.begin(), text.end())
		{
			m_text.push_back(cluster_traits::null_char);
		}

	public:
		buffer_type& get_buffer() { return m_text; }
		const buffer_type& get_buffer() const { return m_text; }

		std::basic_string_view<char_type> get_view() const { return m_text; }

	protected:
		buffer_type m_text;
	};
}
