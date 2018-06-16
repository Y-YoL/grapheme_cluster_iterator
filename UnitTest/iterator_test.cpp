#include "stdafx.h"
#include "CppUnitTest.h"
#include "basic_grapheme_cluster_string.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	using basic_grapheme_cluster_string = yol::basic_grapheme_cluster_string<yol::grapheme_cluster_traits::utf16_traits>;

	TEST_CLASS(IteratorTest)
	{
	public:
		template<class, class = void>
		struct has_iterator_traits
			: std::false_type {};

		template<class T>
		struct has_iterator_traits<T, std::void_t<typename std::iterator_traits<T>::iterator_category>>
			: std::true_type {};

		TEST_METHOD(TestIteratorTraits)
		{
			Assert::IsTrue(has_iterator_traits<basic_grapheme_cluster_string::iterator>::value);
		}

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

		TEST_METHOD(TestCompare)
		{
			basic_grapheme_cluster_string text(u"abcd");

			auto it = text.begin();
			Assert::IsTrue((*it) == u"a");
			Assert::IsTrue((*it) == u'a');
		}

		TEST_METHOD(TestInsert)
		{
			basic_grapheme_cluster_string text(u"abcd");

			auto it = text.begin();
			std::advance(it, 1);
			*it = u"あ";

			std::basic_string_view<char16_t> ret = text.c_str();
			Assert::AreEqual<unsigned>(ret.length(), 4);
			Assert::IsTrue(ret == u"aあcd");
		}

		TEST_METHOD(TestErase)
		{
			basic_grapheme_cluster_string text(u"abcd");

			auto it = text.begin();
			std::advance(it, 1);
			*it = u"";

			std::basic_string_view<char16_t> ret = text.c_str();
			Assert::AreEqual<unsigned>(ret.length(), 3);
			Assert::IsTrue(ret == u"acd");
		}
	};
}
