
#include "stdafx.h"
#include "../../include/grapheme_cluster_string.h"

namespace {
	inline bool iskanji(unsigned char c)
	{
		return (c >= 0x81 && c <= 0x9f) || (c >= 0xe0 && c <= 0xfc);
	}

	inline bool isHalfKana(unsigned char c)
	{
		return (c >= 0xa1) && (c <= 0xdd);
	}

	/// <summary>
	/// 濁音がつけられる半角カナのチェック
	/// </summary>
	/// <param name="c">チェックする文字</param>
	/// <returns>濁音がつけられる文字であればtrue</returns>
	inline bool isHalfKana2(unsigned char c)
	{
		return
			(c >= 0xb6 && c <= 0xc4) ||	// ｶ - ﾄ
			(c >= 0xca && c <= 0xce) || // ﾊ - ﾎ
			(c == 0xb3);				// ｳ
	}

	/// <summary>
	/// 半濁音がつけられる半角カナのチェック
	/// </summary>
	/// <param name="c">チェックする文字</param>
	/// <returns>半濁音がつけられる文字であればtrue</returns>
	inline bool isHalfKana3(unsigned char c)
	{
		return (c >= 0xca && c <= 0xce); // ﾊ - ﾎ
	}

	/// <summary>
	/// 項目の一致チェック
	/// </summary>
	/// <remarks>意図しない型変換が起きないよう、明示的に比較する際の型を指定できるようにする</remarks>
	template<class T>
	inline bool equal(T x, T y)
	{
		return x == y;
	}
}


namespace yol::grapheme_cluster_traits {

	std::size_t sjis_traits::calc_codepoint_size(string_view text)
	{
		if (text.length() <= 1) {
			return text.length();
		}

		return iskanji(text[0]) ? 2 : 1;
	}

	auto sjis_traits::get_codepoint(string_view text) -> codepoint_type
	{
		if (text.length() == 0) {
			return 0;
		}

		codepoint_type c = static_cast<std::uint8_t>(text[0]);
		if (calc_cluster_size(text) == 2) {
			return (c << 8) | static_cast<std::uint8_t>(text[1]);
		} else {
			return c;
		}
	}

	std::size_t sjis_traits::calc_cluster_size(string_view text)
	{
		if (text.length() <= 1) {
			return text.length();
		}

		// crlf
		if (text[0] == '\r' && text[1] == '\n') {
			return 2;
		}

		// 半角カナ
		if (isHalfKana(text[0])) {
			if (isHalfKana2(text[0]) && equal<std::uint8_t>(text[1], 0xde)) {
				return 2;
			}

			if (isHalfKana3(text[0]) && equal<std::uint8_t>(text[1], 0xdf)) {
				return 2;
			}
		}

		return calc_codepoint_size(text);
	}
}
