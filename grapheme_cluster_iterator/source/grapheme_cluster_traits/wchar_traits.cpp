
#include "stdafx.h"
#include "../../include/grapheme_cluster_traits.h"

namespace {
	template<std::size_t>
	struct base_traits_helper;

	template<>
	struct base_traits_helper<2>
	{
		using type = yol::grapheme_cluster_traits::utf16_traits;
	};

	// wcharの処理をutf_traitsに移譲する
	using yol::grapheme_cluster_traits::wchar_traits;
	using base_traits = typename base_traits_helper<sizeof(wchar_traits::char_type)>::type;

	base_traits::string_view view_cast(wchar_traits::string_view text)
	{
		auto p1 = text.data();
		const base_traits::char_type* p2;

		static_assert(sizeof(&p1) == sizeof(&p2));
		static_assert(sizeof(*p1) == sizeof(*p2));
		memcpy(&p2, &p1, sizeof(&p2));
		return { p2, text.length() };
	}
}

namespace yol::grapheme_cluster_traits {

	std::size_t wchar_traits::calc_codepoint_size(string_view text)
	{
		return base_traits::calc_codepoint_size(view_cast(text));
	}

	auto wchar_traits::get_codepoint(string_view text) -> codepoint_type
	{
		return base_traits::get_codepoint(view_cast(text));
	}

	/// <summary>
	/// クラスタのサイズを計算する
	/// </summary>
	/// <param name="text">計算を開始する位置</param>
	/// <returns>クラスタのサイズ</returns>
	/// <remarks>http://unicode.org/reports/tr29/#Grapheme_Cluster_Boundary_Rules</remarks>
	std::size_t wchar_traits::calc_cluster_size(string_view text)
	{
		return base_traits::calc_cluster_size(view_cast(text));
	}
}
