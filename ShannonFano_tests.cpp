#include "pch.h"
#include "CppUnitTest.h"

#include "..\Lab2_Shannon_Fano\Shannon_Fano.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ShannonFanotests
{
	TEST_CLASS(ShannonFanotests)
	{
	public:
		TEST_METHOD(OriginalTextSizeTest) {
			Map<char, int> map;
			map.insert('a', 1);
			int letters = 1;
			string original = "a";
			ShannonFano coder(map, letters, original);
			Assert::IsTrue(coder.sizeOfOriginalText() == 8);
		}

		TEST_METHOD(EncodedTextSizeTest) {
			Map<char, int> map;
			map.insert('a', 1);
			map.insert('b', 1);
			int letters = 2;
			string original = "ab";
			ShannonFano Tester(map, letters, original);
			Tester.ShannonFanoEncode(0, 1);
			Assert::IsTrue(Tester.sizeOfEncodedText() == 2);
		}

		TEST_METHOD(EncodingTest) {
			Map<char, int> MyCustomMap;
			MyCustomMap.insert('a', 1);
			MyCustomMap.insert('b', 1);
			int letters = 2;
			string original = "ab";
			ShannonFano Tester(MyCustomMap, letters, original);
			Assert::IsTrue(Tester.sizeOfOriginalText() == 16);
			Tester.ShannonFanoEncode(0, 1);
			Assert::IsTrue(Tester.encodedText() == "10");
		}

		TEST_METHOD(RatioTest) {
			Map<char, int> map;
			map.insert(1, 1);
			map.insert(2, 1);
			int letters = 2;
			string original = "12";
			ShannonFano tester(map, letters, original);
			tester.ShannonFanoEncode(0, 1);
			Assert::IsTrue((tester.sizeOfOriginalText() / 1.0f) / (tester.sizeOfEncodedText() / 1.0f) == 8);
		}

		TEST_METHOD(DecoderTest) {
			Map<char, int> map;
			map.insert('a', 1);
			map.insert('b', 1);
			int letters = 2;
			string original = "ab";
			ShannonFano Tester(map, letters, original);
			Assert::IsTrue(Tester.sizeOfOriginalText() == 16);
			Tester.ShannonFanoEncode(0, 1);
			Assert::IsTrue(Tester.encodedText() == "10");
			Assert::IsTrue(Tester.decodedText() == "ab");
		}
	};
}
