#include "stdafx.h"
#include "CppUnitTest.h"
#include "grapheme_cluster_string.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	using string = yol::wchar_grapheme_cluster_string;

	TEST_CLASS(WcharTraitsTest)
	{
	public:
		TEST_METHOD(TestAsciiDistance)
		{
			string text(L"abcd");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(4, static_cast<int>(size));
		}

		TEST_METHOD(TestSurrogatePairDistance)
		{
			string text(L"𧸐𡸴𣷹𣏓");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(4, static_cast<int>(size));
		}

		TEST_METHOD(TestMultiByteDistance)
		{
			string text(L"あいうえお");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(5, static_cast<int>(size));
		}

		TEST_METHOD(TestKanaDistance)
		{
			string text(L"ｱｲｳｴｵ");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(5, static_cast<int>(size));
		}

		TEST_METHOD(TestReturnCodeDistance)
		{
			string text(L"\n\n\r\r\n");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(4, static_cast<int>(size));
		}

		TEST_METHOD(TestMultiByteIterator)
		{
			string text(L"あいうえお");

			auto it = text.begin();
			Assert::IsTrue((*it).view() == L"あ");
		}

		TEST_METHOD(TestExtendDistance)
		{
			string text(L"ｶﾞｷﾞｸﾞｹﾞｺﾞ");

			auto size = std::distance(text.begin(), text.end());
			Assert::AreEqual(5, static_cast<int>(size));
		}

		TEST_METHOD(TestCodePoint)
		{
			wchar_t text[] = L"A";

			auto cp = string::cluster_traits::get_codepoint(text);

			Assert::AreEqual<unsigned>(cp, 0x41);
		}
	};
}
