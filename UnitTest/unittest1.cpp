#include "stdafx.h"
#include "CppUnitTest.h"
#include "grapheme_cluster_iterator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			using grapheme_cluster_iterator = yol::grapheme_cluster_iterator<yol::grapheme_cluster_traits::utf16_traits>;
			grapheme_cluster_iterator hoge(u"abcdefg");
		}

	};
}
