#include "stdafx.h"
#include "CppUnitTest.h"
#include "grapheme_cluster_string.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	using string = yol::sjis_grapheme_cluster_string;

	TEST_CLASS(SjisTraitsTest)
	{
#pragma warning(push)
#pragma warning(disable:4309)
		/// <summary>
		/// sjis: "ｶﾞｷﾞｸﾞｹﾞｺﾞ"
		/// </summary>
		static constexpr char kanaText[] = {
			static_cast<char>(0xb6),
			static_cast<char>(0xde),
			static_cast<char>(0xb7),
			static_cast<char>(0xde),
			static_cast<char>(0xb8),
			static_cast<char>(0xde),
			static_cast<char>(0xb9),
			static_cast<char>(0xde),
			static_cast<char>(0xba),
			static_cast<char>(0xde),
			0x00
		};
#pragma warning(pop)

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
			string text(kanaText);

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

		TEST_METHOD(TestKanaIterator)
		{
			string text(kanaText);

#pragma warning(push)
#pragma warning(disable:4838 4309)
			char test[] = { 0xb6, 0xde, 0x00 };
#pragma warning(pop)

			auto it = text.begin();
			Assert::IsTrue((*it).view() == test);
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

		TEST_METHOD(TestKanaCodePoint)
		{
			auto cp = yol::grapheme_cluster_traits::sjis_traits::get_codepoint(kanaText);

			Assert::AreEqual<unsigned>(cp, 0xb6);
		}
	};
}
