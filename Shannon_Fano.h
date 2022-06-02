#pragma once
#include "Map.h"
#include <iostream>

using namespace std;

class ShannonFano {
private:
	char* chars; 
	int* cnt; 
	int size; 
	string* code;
	string sourceText;

	void BubbleSort() {
		for (int i = 0; i < size; i++) {
			bool flag = true;
			for (int j = 0; j < size - (i + 1); j++) {

				if (cnt[j] < cnt[j + 1]) {
					int bufCnt = cnt[j];
					char buf = chars[j];

					//swap
					cnt[j] = cnt[j + 1];
					chars[j] = chars[j + 1];
					cnt[j + 1] = bufCnt;
					chars[j + 1] = buf;

					flag = false;
				}
			}

			if (flag) break;

		}
	}

	int minValue(int first, int second) {
		if (first > second) {
			return second;
		}
		if (second > first) {
			return first;
		}
	}


	bool contains(string substring) {
		for (int i = 0; i < size; i++) {
			if (code[i] == substring)
				return true;
		}
		return false;
	}

	int getIndex(char letter) {
		for (int i = 0; i < size; i++) {
			if (chars[i] == letter) {
				return i;
			}
		}
	}

	int getIndex(string substring) {
		for (int i = 0; i < size; i++) {
			if (code[i] == substring) {
				return i;
			}
		}
	}

public:
	ShannonFano(Map<char, int>& map, const int realCnt, string text) {

		chars = new char[realCnt];
		cnt = new int[realCnt];
		code = new string[realCnt];
		size = realCnt;
		sourceText = text;

		List<char> key = map.getKeys();
		List<int> value = map.getValues();

		for (int i = 0; i < size; i++)
		{
			chars[i] = key.getHead();
			cnt[i] = value.getHead();
			code[i] = "";
			key.setNext();
			value.setNext();
		}

		BubbleSort();

	}

	~ShannonFano() {
		delete[] chars;
		delete[] cnt;
		delete[] code;
	}

	//encode algorithm
	void ShannonFanoEncode(int begin, int end) {

		if (begin == end)
			return;
		int left = begin, right = end;
		int leftSumCounter = 0, rightSumCounter = 0;

		while (left <= right) {
			if (leftSumCounter <= rightSumCounter) {
				leftSumCounter += cnt[left];
				left++;
			}
			else {
				rightSumCounter += cnt[right];
				right--;
			}
		}

		for (int i = begin; i < left; i++) {
			code[i] += "0";
		}

		for (int i = left; i <= end; i++) {
			code[i] += "1";
		}

		ShannonFanoEncode(begin, left - 1);
		ShannonFanoEncode(left, end);
	}

	void printCounter() {
		for (int i = 0; i < size; i++)
		{
			cout << chars[i] << " : " << cnt[i] << '\n';
		}
	}

	void printCode() {
		for (int i = 0; i < size; i++)
		{
			cout << chars[i] << " : " << code[i] << '\n';
		}
	}

	string encodedText() {
		string encodedText = "";
		for (int i = 0; i < sourceText.size(); i++) {
			encodedText += code[getIndex(sourceText.at(i))];
		}
		return encodedText;
	}

	string decodedText() {
		string decodedText = "";
		string textToDecode = encodedText();
		int maxLength = 0;
		for (int i = 0; i < size; i++) {
			if (code[i].size() > maxLength) {
				maxLength = code[i].size();
			}
		}
		while (textToDecode.size() > 0) {
			for (int i = 0; i <= minValue(maxLength, textToDecode.size()); i++) {
				string substring = textToDecode.substr(0, i);
				if (contains(substring)) {
					decodedText += chars[getIndex(substring)];
					textToDecode.erase(0, i);
					break;
				}
			}
		}
		return decodedText;
	}

	int sizeOfOriginalText() {
		int sum = 0;
		for (int i = 0; i < size; i++)
		{
			sum += 8 * cnt[i];
		}
		return sum;
	}

	int sizeOfEncodedText() {
		int sum = 0;
		for (int i = 0; i < size; i++)
		{
			sum += code[i].size() * cnt[i];
		}
		return sum;
	}
};
