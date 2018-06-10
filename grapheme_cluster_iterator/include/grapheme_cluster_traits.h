#pragma once

#include <cstddef>
#include <string_view>

namespace yol::grapheme_cluster_traits {

	struct utf16_traits {
		/// <summary>
		/// 文字の型
		/// </summary>
		using char_type = char16_t;

		/// <summary>
		/// コードポイントの型
		/// </summary>
		using codepoint_type = std::uint32_t;

		using string_view = std::basic_string_view<char_type>;

		static constexpr char_type null_char = u'\0';

		/// <summary>
		/// コードポイントのサイズを計算する
		/// </summary>
		/// <param name="text">コードポイントのサイズを計算する文字</param>
		/// <returns>コードポイントのサイズ</returns>
		static std::size_t calc_codepoint_size(string_view text);

		/// <summary>
		/// コードポイントを取得する
		/// </summary>
		/// <param name="text">コードポイントを取得する文字</param>
		/// <returns>コードポイント</returns>
		static codepoint_type get_codepoint(string_view text);

		/// <summary>
		/// クラスタのサイズを計算する
		/// </summary>
		/// <param name="text">計算を開始する位置</param>
		/// <returns>クラスタのサイズ</returns>
		static std::size_t calc_cluster_size(string_view text)
		{
			return calc_codepoint_size(text);
		}
	};
}
