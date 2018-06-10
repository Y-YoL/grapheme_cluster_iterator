#pragma once

#include "basic_grapheme_cluster_string_base.h"

namespace yol::detail {
	template<class Traits>
	class grapheme_cluster_iterator {
		using owner_type = basic_grapheme_cluster_string_base<Traits>;
		using cluster_traits = Traits;

	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = int;
		using difference_type = std::ptrdiff_t;
		using pointer = int*;
		using reference = int&;

	public:
		grapheme_cluster_iterator()
			: m_owner(nullptr)
			, m_index(0)
		{}

		grapheme_cluster_iterator(owner_type* owner)
			: m_owner(owner)
			, m_index(0)
		{}

		bool operator==(const grapheme_cluster_iterator& rhs) const
		{
			if (!m_owner && !rhs.m_owner) {
				// 両方とも 'end'
				return true;
			} else if (m_owner && rhs.m_owner) {
				return (m_owner == rhs.m_owner) && (m_index == rhs.m_index);
			} else if (m_owner) {
				return m_owner->get_buffer().size() == (m_index + 1);
			} else {
				return rhs.m_owner->get_buffer().size() == (rhs.m_index + 1);

			}
		}

		bool operator!=(const grapheme_cluster_iterator& rhs) const
		{
			return !(*this == rhs);
		}

		grapheme_cluster_iterator& operator++()
		{
			if (m_owner) {
				std::basic_string_view<typename cluster_traits::char_type> view = m_owner->get_buffer();
				m_index += cluster_traits::calc_cluster_size(view.substr(m_index));
			}

			return *this;
		}

		reference operator*()
		{
			throw 0;
		}

	private:
		owner_type* m_owner;
		difference_type m_index;
	};
}
