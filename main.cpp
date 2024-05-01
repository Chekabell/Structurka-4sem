#include <iostream>
#include <chrono>

int globalCount = 0;
const char* globalAlphabet{ "QWERTYUIOPASDFGHJKLZXCVBNM"};


char* genText(const int len) {
	size_t lenAlphabet = strlen(globalAlphabet);
	char* text = new char[len];
	for (int i = 0; i < len; i++) {
		text[i] = globalAlphabet[rand() % lenAlphabet];
	}
	return text;
}

int* prefixGen(const char* text) {
	size_t len = strlen(text);
	int* pi = new int[len]{0};
	for (int i = 1; i < len; i++) {
		int j = pi[i - 1];
		for (; j > 0 && text[j] != text[i];)
			j = pi[j - 1];
		if (text[i] == text[j])
			j += 1;
		pi[i] = j;
	}
	return pi;
}

int kmpSearch(const char* text, const char* subText) {
	int j = 0;
	size_t lenText = strlen(text);
	size_t lenSubText = strlen(subText);
	int* pi = prefixGen(subText);
	for (int i = 0; i < lenText; i++) {
		for (; j > 0 && text[i] != subText[j];)
			j = pi[j - 1];
		if (text[i] == subText[j])
			j++;
		if (j >= lenSubText)
			return i - j + 1;
	}
	return -1;
}

char* subStr(const char * text, int pointStart, const int pointEnd) {
	int len = pointEnd - pointStart + 1;
	char* subText = new char[len];
	subText[len] = '\0';
	for (int i = 0; i < len; i++) {
		subText[i] = text[pointStart];
		pointStart++;
	}
	return subText;
}

bool equalsSubStr(char* text, const int len, int point1, int point2) {
	if (point1 == point2) return true;
	for (int i = 0; i < len; i++) {
		if (text[point1] != text[point2]) return false;
	}
	return true;
}

void checkSearchBySizeText(int functionSearch(const char*, const char*), int step) {
	int maxLenText = step * 10;
	int lenSubStr = 10;
	for (int lenText = step; lenText <= maxLenText; lenText += step) {
		int iters = 0;
		char* text = genText(lenText);
		double averageTime;
		while (iters <= 100) {
			int pointStartSubText = rand() % (lenText - lenSubStr -1);
			char* subText = subStr(text, pointStartSubText, pointStartSubText + lenSubStr);

			auto start = std::chrono::high_resolution_clock::now();
			int result = functionSearch(text, subText);
			auto end = std::chrono::high_resolution_clock::now();

			if (equalsSubStr(text,lenSubStr,pointStartSubText,result)) iters++;
			else {
				std::cout << "------FAIL------" << std::endl;
				std::cout << pointStartSubText << " :: " << result << std::endl;
				std::cout << subText << " :: " << subStr(text, result, result + lenSubStr);
				return;
			}
			averageTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		}
		averageTime /= iters;
		std::cout << "Size text: " << lenText << " T(n) = " << averageTime << std::endl;
	}
}



std::ostream& operator << (std::ostream& os, const char* text) {
	for (int i = 0; text[i] != '\0'; i++) {
		std::cout << text[i];
	}
	return os;
}

int main(void) {
	srand((unsigned int)time(NULL));
	const int step = 10000;
	checkSearchBySizeText(kmpSearch, step);
	return 0;
}