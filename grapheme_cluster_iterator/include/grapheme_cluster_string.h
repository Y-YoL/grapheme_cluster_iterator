#pragma once

#include "basic_grapheme_cluster_string.h"
#include "grapheme_cluster_traits.h"

namespace yol {
	using utf16_grapheme_cluster_string = basic_grapheme_cluster_string<grapheme_cluster_traits::utf16_traits>;
	using sjis_grapheme_cluster_string = basic_grapheme_cluster_string<grapheme_cluster_traits::sjis_traits>;
}
