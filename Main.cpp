#include <iostream>
#include "Shannon_Fano.h"
#include <fstream>

using namespace std;

string fileName = "Text.txt";

int main()
{
	Map<char, int> map;
	char letter;
	int cntLetter = 0;
	string text = "";

	cout << "The text to be encoded and decoded: " << endl;

	ifstream file_input;
	file_input.open(fileName);

	while (!file_input.eof()) {
		letter = file_input.get();
		cout << letter;
		if (letter == '\n') break;
		text += letter;
		if (map.contains(letter)) {
			map.find(letter)->value++;
		}
		else {
			map.insert(letter, 1);
			cntLetter++;
		}
	}
	file_input.close();
	cout << endl;

	ShannonFano New(map, cntLetter, text);

	ShannonFano NewShannonFano(map, cntLetter, text);

	cout << "\nCounter table\n";
	NewShannonFano.printCounter();

	NewShannonFano.ShannonFanoEncode(0, cntLetter - 1);
	cout << "\nCode table\n";
	NewShannonFano.printCode();

	cout << "\nCompression ratio: " << (NewShannonFano.sizeOfOriginalText() / 1.0f) / (NewShannonFano.sizeOfEncodedText() / 1.0f) << "\n";

	cout << "\nEncoded text:\n";
	cout << NewShannonFano.encodedText() << endl;
	cout << "Size of encode text: " << NewShannonFano.sizeOfEncodedText();

	cout << "\n\nDecoded text:\n";
	cout << NewShannonFano.decodedText() << endl;
	cout << "Size of original text :" << NewShannonFano.sizeOfOriginalText() << endl;

	return 0;
}