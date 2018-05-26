#pragma once

#include <cstddef>

namespace yol::grapheme_cluster_traits {

	struct utf16_traits {
		using char_type = char16_t;
		static constexpr char_type null_char = u'\0';

		/// <summary>
		/// クラスタのサイズを計算する
		/// </summary>
		/// <param name="c">計算を開始する位置</param>
		/// <returns>クラスタのサイズ</returns>
		static std::size_t calc_cluster_size(const char_type* c)
		{

		}
	};
}
