#pragma once

#include "grapheme_cluster_traits.h"
#include "detail/basic_grapheme_cluster_string_base.h"
#include "detail/grapheme_cluster_iterator.h"

namespace yol {
	template<class Traits>
	class basic_grapheme_cluster_string : detail::basic_grapheme_cluster_string_base<Traits> {
		using base_type = detail::basic_grapheme_cluster_string_base<Traits>;
		using cluster_traits = Traits;
		using char_type = typename cluster_traits::char_type;

	public:
		using iterator = detail::grapheme_cluster_iterator<cluster_traits>;

	public:
		basic_grapheme_cluster_string() = default;
		basic_grapheme_cluster_string(std::basic_string_view<char_type> text)
			: base_type(text)
		{
		}

		iterator begin() { return iterator(this); }
		iterator end() { return iterator(this); }

		const char_type* c_str() const { return m_text.data(); }
	};
}
