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

		TEST_METHOD(TestKanaDistance2)
		{
#pragma warning(push)
#pragma warning(disable:4838 4309)
			char buff[] = { 0xb6, 0xde, 0xb7, 0xde, 0xb8, 0xde, 0xb9, 0xde, 0xba, 0xde, 0x00 }; // sjis: "ｶﾞｷﾞｸﾞｹﾞｺﾞ"
#pragma warning(pop)

			string text(buff);

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(5, static_cast<int>(size));
		}

		TEST_METHOD(TestReturnCodeDistance)
		{
			string text("\n\n\r\r\n");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(4, static_cast<int>(size));
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
#pragma warning(push)
#pragma warning(disable:4838 4309)
			char text[] = { 0x82, 0xa0, 0x00 }; // Sift-jis:"あ"
#pragma warning(pop)

			auto cp = yol::grapheme_cluster_traits::sjis_traits::get_codepoint(text);

			Assert::AreEqual<unsigned>(cp, 0x82a0);
		}
	};
}
