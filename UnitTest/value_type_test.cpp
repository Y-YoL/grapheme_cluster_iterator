#include "stdafx.h"
#include "CppUnitTest.h"
#include "basic_grapheme_cluster_string.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	using basic_grapheme_cluster_string = yol::basic_grapheme_cluster_string<yol::grapheme_cluster_traits::utf16_traits>;

	TEST_CLASS(ValueTypeTest)
	{
	public:

		TEST_METHOD(TestAscii)
		{
			basic_grapheme_cluster_string text(u"abcd");

			auto it = text.begin();
			Assert::IsTrue((*it).view() == u"a");
		}

		TEST_METHOD(TestExtend)
		{
			basic_grapheme_cluster_string text(u"ｶﾞｷﾞｸﾞｹﾞｺﾞ");

			auto it = text.begin();
			Assert::IsTrue((*it).view() == u"ｶﾞ");
		}
	};
}
