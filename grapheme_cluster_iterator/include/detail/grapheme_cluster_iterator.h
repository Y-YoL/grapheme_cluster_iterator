#pragma once

#include "basic_grapheme_cluster_string_base.h"

namespace yol::detail {
	template<class Traits>
	class grapheme_cluster_iterator {
	public:
		grapheme_cluster_iterator() = default;
		grapheme_cluster_iterator(basic_grapheme_cluster_string_base<Traits>*)
		{
			throw 0;
		}


		bool operator!=(const grapheme_cluster_iterator& rhs)
		{
			throw 0;
		}

		grapheme_cluster_iterator& operator++()
		{
			throw 0;
		}

		int& operator*()
		{
			throw 0;
		}
	};
}
