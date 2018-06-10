#pragma once

#include <cstddef>
#include <string_view>

namespace yol::grapheme_cluster_traits {

	struct utf16_traits {
		using char_type = char16_t;
		static constexpr char_type null_char = u'\0';

		/// <summary>
		/// コードポイントのサイズを計算する
		/// </summary>
		/// <param name="c">コードポイントのサイズを計算する文字</param>
		/// <returns>コードポイントのサイズ</returns>
		static std::size_t calc_codepoint_size(std::basic_string_view<char_type> c);

		/// <summary>
		/// クラスタのサイズを計算する
		/// </summary>
		/// <param name="c">計算を開始する位置</param>
		/// <returns>クラスタのサイズ</returns>
		static std::size_t calc_cluster_size(std::basic_string_view<char_type> c)
		{
			return calc_codepoint_size(c);
		}
	};
}
