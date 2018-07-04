#pragma once

#include "grapheme_cluster_traits.h"
#include "detail/basic_grapheme_cluster_string_base.h"
#include "detail/grapheme_cluster_iterator.h"

namespace yol {
	template<class Traits>
	class basic_grapheme_cluster_string : detail::basic_grapheme_cluster_string_base<Traits> {
		using base_type = detail::basic_grapheme_cluster_string_base<Traits>;

	public:
		using cluster_traits = Traits;
		using iterator = detail::grapheme_cluster_iterator<cluster_traits>;

	private:
		using char_type = typename cluster_traits::char_type;

	public:
		/// <summary>
		/// 空の文字列を扱うgrapheme_cluster_stringを構築
		/// </summary>
		basic_grapheme_cluster_string() = default;

		/// <summary>
		/// textの内容を基にgrapheme_cluster_stringを構築
		/// </summary>
		/// <param name="text">基にする文字列</param>
		basic_grapheme_cluster_string(std::basic_string_view<char_type> text)
			: base_type(text)
		{
		}

		/// <summary>
		/// 先頭要素を指すイテレータを取得する
		/// </summary>
		/// <returns>先頭要素へのイテレータ</returns>
		iterator begin() { return iterator(this); }

		/// <summary>
		/// 末尾の次を指すイテレータを取得する
		/// </summary>
		/// <returns>末尾の次を指すイテレータ</returns>
		iterator end() { return iterator(nullptr); }

		/// <summary>
		/// null終端された文字列の先頭ポインタを取得
		/// </summary>
		/// <returns>null終端文字列</returns>
		const char_type* c_str() const { return m_text.data(); }
	};
}
