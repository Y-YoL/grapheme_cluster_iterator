﻿#pragma once
#include <string_view>

namespace yol::detail {
	template<class Traits>
	class grapheme_cluster_type {
		using owner_type = basic_grapheme_cluster_string_base<Traits>;
		using cluster_traits = Traits;
		using char_type = typename cluster_traits::char_type;
		using difference_type = std::ptrdiff_t;

	public:
		grapheme_cluster_type(owner_type* owner, difference_type index)
			: m_owner(owner)
			, m_index(index)
		{
		}

		std::basic_string_view<char_type> operator=(std::basic_string_view<char_type> c)
		{
			auto& buffer = m_owner->get_buffer();
			auto size = view().length();
			buffer.erase(m_index, size);
			buffer.insert(m_index, c);

			return c;
		}

		std::basic_string_view<char_type> view() const
		{
			auto view = m_owner->get_view().substr(m_index);
			auto size = cluster_traits::calc_cluster_size(view);
			return view.substr(0, size);
		}

		bool operator==(char_type c) const
		{
			auto v = view();
			return v.length() == 1 && v[0] == c;
		}

#define GRAPHEME_CLUSTER_TYPE_OPERATOR_DEFINE(op)						\
		bool operator op (std::basic_string_view<char_type> c) const	\
		{																\
			return view() op c;											\
		}

		GRAPHEME_CLUSTER_TYPE_OPERATOR_DEFINE(== );
		GRAPHEME_CLUSTER_TYPE_OPERATOR_DEFINE(!= );
		GRAPHEME_CLUSTER_TYPE_OPERATOR_DEFINE(< );
		GRAPHEME_CLUSTER_TYPE_OPERATOR_DEFINE(> );
		GRAPHEME_CLUSTER_TYPE_OPERATOR_DEFINE(<= );
		GRAPHEME_CLUSTER_TYPE_OPERATOR_DEFINE(>= );
#undef GRAPHEME_CLUSTER_TYPE_OPERATOR_DEFINE

	private:
		owner_type* m_owner;
		difference_type m_index;
	};
}
