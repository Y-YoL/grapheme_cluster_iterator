#include "stdafx.h"
#include "CppUnitTest.h"
#include "grapheme_cluster_string.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	using string = yol::sjis_grapheme_cluster_string;

	TEST_CLASS(SjisTraitsTest)
	{
	public:
		TEST_METHOD(TestAsciiDistance)
		{
			string text("abcd");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(4, static_cast<int>(size));
		}

		TEST_METHOD(TestMultiByteDistance)
		{
			string text("あいうえお");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(5, static_cast<int>(size));
		}

		TEST_METHOD(TestKanaDistance)
		{
			string text("ｱｲｳｴｵ");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(5, static_cast<int>(size));
		}

		TEST_METHOD(TestMultiByteIterator)
		{
			string text("あいうえお");

			auto it = text.begin();
			Assert::IsTrue((*it).view() == "あ");
		}

		TEST_METHOD(TestCodePoint)
		{
			char text[] = "A";

			auto cp = yol::grapheme_cluster_traits::sjis_traits::get_codepoint(text);

			Assert::AreEqual<unsigned>(cp, 0x41);
		}

		TEST_METHOD(TestMultiByteCodePoint)
		{
			char text[] = "あ";

			auto cp = yol::grapheme_cluster_traits::sjis_traits::get_codepoint(text);

			Assert::AreEqual<unsigned>(cp, 0x82a0);
		}
	};
}
