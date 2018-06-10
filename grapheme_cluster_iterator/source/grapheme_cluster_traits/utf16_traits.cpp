
#include "stdafx.h"
#include "../../include/grapheme_cluster_traits.h"
#include <icu.h>
#include <optional>

namespace {
	using yol::grapheme_cluster_traits::utf16_traits;

	UGraphemeClusterBreak GetGraphemeClusterBreak(utf16_traits::codepoint_type c)
	{
		return static_cast<UGraphemeClusterBreak>(u_getIntPropertyValue(c, UProperty::UCHAR_GRAPHEME_CLUSTER_BREAK));
	}
}

namespace yol::grapheme_cluster_traits {

	std::size_t utf16_traits::calc_codepoint_size(string_view text)
	{
		if (text.length() == 0) {
			return 0;
		}

		auto c = get_codepoint(text);
		return U16_LENGTH(c);
	}

	auto utf16_traits::get_codepoint(string_view text) -> codepoint_type
	{
		if (text.length() == 0) {
			return 0;
		}

		char32_t c = {};
		U16_GET(text, 0, 0, text.length(), c);
		return c;
	}

	/// <summary>
	/// クラスタのサイズを計算する
	/// </summary>
	/// <param name="text">計算を開始する位置</param>
	/// <returns>クラスタのサイズ</returns>
	/// <remarks>http://unicode.org/reports/tr29/#Grapheme_Cluster_Boundary_Rules</remarks>
	std::size_t utf16_traits::calc_cluster_size(string_view text)
	{
		if (text.length() <= 1) {
			return text.length();
		}

		auto prev = GetGraphemeClusterBreak(get_codepoint(text));
		auto size = calc_codepoint_size(text);;
		text = text.substr(size);

		while (!text.empty()) {
			auto c = get_codepoint(text);
			auto gcb = GetGraphemeClusterBreak(c);

			switch (gcb) {
				// GB999
			case UGraphemeClusterBreak::U_GCB_OTHER:
				return size;

				// GB3
			case UGraphemeClusterBreak::U_GCB_LF:
				if (prev != UGraphemeClusterBreak::U_GCB_CR) {
					return size;
				}

				break;

				// GB9a
			case UGraphemeClusterBreak::U_GCB_SPACING_MARK:
				break;

			default:
				return size;
			}

			prev = gcb;
			size += U16_LENGTH(c);
			text = text.substr(U16_LENGTH(c));
		}

		return size;
	}
}
