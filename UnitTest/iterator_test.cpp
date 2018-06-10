﻿#include "stdafx.h"
#include "CppUnitTest.h"
#include "basic_grapheme_cluster_string.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
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
			using basic_grapheme_cluster_string = yol::basic_grapheme_cluster_string<yol::grapheme_cluster_traits::utf16_traits>;
			Assert::IsTrue(has_iterator_traits<basic_grapheme_cluster_string::iterator>::value);
		}

		TEST_METHOD(TestAsciiDistance)
		{
			using basic_grapheme_cluster_string = yol::basic_grapheme_cluster_string<yol::grapheme_cluster_traits::utf16_traits>;
			basic_grapheme_cluster_string text(u"abcd");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(4, static_cast<int>(size));
		}

		TEST_METHOD(TestSurrogatePairDistance)
		{
			using basic_grapheme_cluster_string = yol::basic_grapheme_cluster_string<yol::grapheme_cluster_traits::utf16_traits>;
			basic_grapheme_cluster_string text(u"𧸐𡸴𣷹𣏓");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(4, static_cast<int>(size));
		}

		TEST_METHOD(TestSpacingMarkDistance)
		{
			using basic_grapheme_cluster_string = yol::basic_grapheme_cluster_string<yol::grapheme_cluster_traits::utf16_traits>;
			basic_grapheme_cluster_string text(u"நிกำ");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(2, static_cast<int>(size));
		}

		TEST_METHOD(TestReturnCodeDistance)
		{
			using basic_grapheme_cluster_string = yol::basic_grapheme_cluster_string<yol::grapheme_cluster_traits::utf16_traits>;
			basic_grapheme_cluster_string text(u"\n\n\r\r\n");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(4, static_cast<int>(size));
		}

		TEST_METHOD(TestExtendDistance)
		{
			using basic_grapheme_cluster_string = yol::basic_grapheme_cluster_string<yol::grapheme_cluster_traits::utf16_traits>;
			basic_grapheme_cluster_string text(u"ｶﾞｷﾞｸﾞｹﾞｺﾞ");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(5, static_cast<int>(size));
		}

		/*
		TEST_METHOD(TestMethod1)
		{
			using basic_grapheme_cluster_string = yol::basic_grapheme_cluster_string<yol::grapheme_cluster_traits::utf16_traits>;
			basic_grapheme_cluster_string hoge(u"abcdefg");

			for (auto& value : hoge) {
			}
		}*/

	};
}
