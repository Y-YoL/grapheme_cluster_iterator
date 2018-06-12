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

		TEST_METHOD(TestAsciiDistance)
		{
			basic_grapheme_cluster_string text(u"abcd");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(4, static_cast<int>(size));
		}

		TEST_METHOD(TestSurrogatePairDistance)
		{
			basic_grapheme_cluster_string text(u"𧸐𡸴𣷹𣏓");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(4, static_cast<int>(size));
		}

		TEST_METHOD(TestSpacingMarkDistance)
		{
			basic_grapheme_cluster_string text(u"நிกำ");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(2, static_cast<int>(size));
		}

		TEST_METHOD(TestReturnCodeDistanceGB3)
		{
			basic_grapheme_cluster_string text(u"\n\n\r\r\n");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(4, static_cast<int>(size));
		}

		TEST_METHOD(TestExtendDistance)
		{
			basic_grapheme_cluster_string text(u"ｶﾞｷﾞｸﾞｹﾞｺﾞ");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(5, static_cast<int>(size));
		}

		TEST_METHOD(TestReturnCodeDistanceGB4)
		{
			const char16_t buffer[] = { u'\n', u'\xff9e', u'\0' };
			basic_grapheme_cluster_string text(buffer);

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(2, static_cast<int>(size));
		}

		TEST_METHOD(TestHangulDistance)
		{
			const char16_t buffer[] = { u'ᄀ', u'ᅡ', u'ᆨ', u'\0' };
			basic_grapheme_cluster_string text(buffer);

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(1, static_cast<int>(size));
		}

		TEST_METHOD(TestPrependDistance)
		{
			basic_grapheme_cluster_string text(u"؀۱");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(1, static_cast<int>(size));
		}

#if false	// todo: 思ったより複雑そうなので後回し
		TEST_METHOD(TestEmojiDistance)
		{
			basic_grapheme_cluster_string text(u"🎅🎅🏿🎅🏻🎅🏽");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(4, static_cast<int>(size));
		}
#endif
	};
}
