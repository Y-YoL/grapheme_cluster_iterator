
#include "stdafx.h"
#include "../../include/grapheme_cluster_traits.h"
#if defined(USE_LOCAL_ICU)
#include <unicode/uchar.h>
#else
#include <icu.h>
#endif
#include <optional>

namespace {
	using yol::grapheme_cluster_traits::utf16_traits;

	UGraphemeClusterBreak GetGraphemeClusterBreak(utf16_traits::codepoint_type c)
	{
		return static_cast<UGraphemeClusterBreak>(u_getIntPropertyValue(c, UProperty::UCHAR_GRAPHEME_CLUSTER_BREAK));
	}

	bool CheckHangulSequence(UGraphemeClusterBreak prev, UGraphemeClusterBreak gcb)
	{
		switch (prev) {
			// GB6
		case UGraphemeClusterBreak::U_GCB_L:
			switch (gcb) {
			case UGraphemeClusterBreak::U_GCB_L:
			case UGraphemeClusterBreak::U_GCB_V:
			case UGraphemeClusterBreak::U_GCB_LV:
			case UGraphemeClusterBreak::U_GCB_LVT:
				return true;
			}

			break;
			// GB7
		case UGraphemeClusterBreak::U_GCB_LV:
		case UGraphemeClusterBreak::U_GCB_V:
			switch (gcb) {
			case UGraphemeClusterBreak::U_GCB_V:
			case UGraphemeClusterBreak::U_GCB_T:
				return true;
			}

			break;
			// GB8
		case UGraphemeClusterBreak::U_GCB_LVT:
		case UGraphemeClusterBreak::U_GCB_T:
			switch (gcb) {
			case UGraphemeClusterBreak::U_GCB_T:
				return true;
			}

			break;
		}

		return false;
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
		// GB2
		if (text.length() <= 1) {
			return text.length();
		}

		auto prev = GetGraphemeClusterBreak(get_codepoint(text));
		auto size = calc_codepoint_size(text);
		text = text.substr(size);

		// GB4
		switch (prev) {
		case UGraphemeClusterBreak::U_GCB_CONTROL:
		case UGraphemeClusterBreak::U_GCB_LF:
			return size;
		case UGraphemeClusterBreak::U_GCB_CR:
			{
				auto c = get_codepoint(text);
				auto gcb = GetGraphemeClusterBreak(c);
				if (gcb == UGraphemeClusterBreak::U_GCB_LF) {
					// GB3
					return size + U16_LENGTH(c);
				}

				return size;
			}
		}

		while (!text.empty()) {
			auto c = get_codepoint(text);
			auto gcb = GetGraphemeClusterBreak(c);

			switch (gcb) {
				// GB999
			case UGraphemeClusterBreak::U_GCB_OTHER:
				return size;

				// GB6, 7, 8
			case UGraphemeClusterBreak::U_GCB_L:
			case UGraphemeClusterBreak::U_GCB_V:
			case UGraphemeClusterBreak::U_GCB_LV:
			case UGraphemeClusterBreak::U_GCB_LVT:
			case UGraphemeClusterBreak::U_GCB_T:
				if (!CheckHangulSequence(prev, gcb)) {
					return size;
				}

				break;

				// GB9
			case UGraphemeClusterBreak::U_GCB_EXTEND:
			case UGraphemeClusterBreak::U_GCB_ZWJ:
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
