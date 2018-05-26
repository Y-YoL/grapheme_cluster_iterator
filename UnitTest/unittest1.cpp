#include "stdafx.h"
#include "CppUnitTest.h"
#include "basic_grapheme_cluster_string.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			using basic_grapheme_cluster_string = yol::basic_grapheme_cluster_string<yol::grapheme_cluster_traits::utf16_traits>;
			basic_grapheme_cluster_string hoge(u"abcdefg");

			for (auto& value : hoge) {
			}
		}

	};
}
