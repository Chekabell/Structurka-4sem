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
		point1++;
		point2++;
	}
	return true;
}

bool equalsSubStr(char* text, const int len, int point1, char* point2) {
	for (int i = 0; i < len; i++) {
		if (text[point1] != point2[i]) return false;
		point1++;
	}
	return true;
}

void checkSearchBySizeText(int functionSearch(const char*, const char*), const int step) {
	int maxLenText = step * 10;
	int lenSubStr = 100;
	char notExistSubStr[4]{ "abc" };
	for (int lenText = step; lenText <= maxLenText; lenText += step) {
		int iters = 0;
		char* text = genText(lenText);
		double averageTimeSuccsess = 0;
		double averageTimeFail = 0;
		while (iters <= 100) {
			int indexStartSubText = rand() % (lenText - lenSubStr -1);
			char* subText = subStr(text, indexStartSubText, indexStartSubText + lenSubStr);

			auto start = std::chrono::high_resolution_clock::now();
			int result = functionSearch(text, subText);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> time = end - start;
			if (equalsSubStr(text,lenSubStr, indexStartSubText,result)) iters++;
			else {
				std::cout << "------FAIL------" << std::endl;
				std::cout << indexStartSubText << " :: " << result << std::endl;
				std::cout << subText << " :: " << subStr(text, result, result + lenSubStr) << std::endl;
				return;
			}
			averageTimeSuccsess += std::chrono::duration<double,std::milli>(end - start).count();

			start = std::chrono::high_resolution_clock::now();
			result = functionSearch(text, notExistSubStr);
			end = std::chrono::high_resolution_clock::now();
			time = end - start;

			if (result < 0) iters++;
			else {
				std::cout << "------FAIL NOT EXIST------" << std::endl;
				return;
			}
			averageTimeFail += std::chrono::duration<double, std::milli>(end - start).count();
		}
		averageTimeSuccsess /= iters;
		averageTimeFail /= iters;
		std::cout << "Size text: " << lenText << " (succsess)T(n) = " << averageTimeSuccsess << " (fail)T(n) = " << averageTimeFail << std::endl;
	}
}

void checkSearchBySizeSubstr(int functionSearch(const char*, const char*), const int sizeText) {
	int maxSubStrSize = sizeText/2;
	int step = 10000;
	int i = 0;
	char notExistSubStr[4]{ "abc" };
	std::cout << "Size text: " << sizeText << std::endl;
	for (int lenSubStr = step, i = 0; i < 10 && lenSubStr <= maxSubStrSize; lenSubStr += step) {
		int iters = 0;
		char* text = genText(sizeText);
		double averageTimeSuccsess = 0;
		double averageTimeFail = 0;
		while (iters <= 100) {
			int indexStartSubText = rand() % (sizeText - lenSubStr - 1);
			char* subText = subStr(text, indexStartSubText, indexStartSubText + lenSubStr);

			auto start = std::chrono::high_resolution_clock::now();
			int result = functionSearch(text, subText);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> time = end - start;

			if (equalsSubStr(text, lenSubStr, indexStartSubText, result)) iters++;
			else {
				std::cout << "------FAIL------" << std::endl;
				std::cout << indexStartSubText << " :: " << result << std::endl;
				std::cout << subText << " :: " << subStr(text, result, result + lenSubStr) << std::endl;
				return;
			}
			averageTimeSuccsess += std::chrono::duration<double, std::milli>(end - start).count();

			start = std::chrono::high_resolution_clock::now();
			result = functionSearch(text, notExistSubStr);
			end = std::chrono::high_resolution_clock::now();
			time = end - start;

			if (result < 0) iters++;
			else {
				std::cout << "------FAIL------" << std::endl;
				std::cout << indexStartSubText << " :: " << result << std::endl;
				std::cout << subText << " :: " << result << std::endl;
				return;
			}
			averageTimeFail += std::chrono::duration<double, std::milli>(end - start).count();
		}
		averageTimeSuccsess /= iters;
		averageTimeFail /= iters;
		std::cout << "Size substr: " << lenSubStr << " (succsess)T(n) = " << averageTimeSuccsess << " (fail)T(n) = " << averageTimeFail << std::endl;
		i++;
	}
}

void checkSearchBySizeText(const int step) {
	int maxLenText = step * 10;
	int lenSubStr = 100;
	char notExistSubStr[4]{ "abc" };
	for (int lenText = step; lenText <= maxLenText; lenText += step) {
		int iters = 0;
		char* text = genText(lenText);
		double averageTimeSuccsess = 0;
		double averageTimeFail = 0;
		while (iters <= 100) {
			int indexStartSubText = rand() % (lenText - lenSubStr - 1);
			char* subText = subStr(text, indexStartSubText, indexStartSubText + lenSubStr);

			auto start = std::chrono::high_resolution_clock::now();
			char* result = strstr(text, subText);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> time = end - start;

			if (equalsSubStr(text, lenSubStr, indexStartSubText, result)) iters++;
			else {
				std::cout << "------FAIL------" << std::endl;
				std::cout << indexStartSubText << " :: " << result << std::endl;
				std::cout << subText << " :: " << result << std::endl;
				return;
			}
			averageTimeSuccsess += std::chrono::duration<double, std::milli>(end - start).count();

			start = std::chrono::high_resolution_clock::now();
			result = strstr(text, notExistSubStr);
			end = std::chrono::high_resolution_clock::now();
			time = end - start;
			if (!result) iters++;
			else {
				std::cout << "------FAIL------" << std::endl;
				std::cout << indexStartSubText << " :: " << result << std::endl;
				std::cout << subText << " :: " << result << std::endl;
				return;
			}
			averageTimeFail += std::chrono::duration<double, std::milli>(end - start).count();
		}
		averageTimeFail /= iters;
		averageTimeSuccsess /= iters;
		std::cout << "Size text: " << lenText << " (succsess)T(n) = " << averageTimeSuccsess << " (fail)T(n) = " << averageTimeFail << std::endl;
	}
}

void checkSearchBySizeSubstr(const int sizeText) {
	int maxSubStrSize = sizeText / 2;
	int step = 10000;
	int i = 0;
	char notExistSubStr[4]{ "abc" };
	std::cout << "Size text: " << sizeText << std::endl;
	for (int lenSubStr = step, i = 0; i < 10 && lenSubStr <= maxSubStrSize; lenSubStr += step) {
		int iters = 0;
		char* text = genText(sizeText);
		double averageTimeSuccsess = 0;
		double averageTimeFail = 0;
		while (iters <= 100) {
			int indexStartSubText = rand() % (sizeText - lenSubStr - 1);
			char* subText = subStr(text, indexStartSubText, indexStartSubText + lenSubStr);

			auto start = std::chrono::high_resolution_clock::now();
			char* result = strstr(text, subText);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> time = end - start;

			if (equalsSubStr(text, lenSubStr, indexStartSubText, result)) iters++;
			else {
				std::cout << "------FAIL------" << std::endl;
				std::cout << indexStartSubText << " :: " << result << std::endl;
				std::cout << subText << " :: " << result << std::endl;
				return;
			}
			averageTimeSuccsess += std::chrono::duration<double, std::milli>(end - start).count();

			start = std::chrono::high_resolution_clock::now();
			result = strstr(text, notExistSubStr);
			end = std::chrono::high_resolution_clock::now();
			time = end - start;
			if (!result) iters++;
			else {
				std::cout << "------FAIL------" << std::endl;
				std::cout << indexStartSubText << " :: " << result << std::endl;
				std::cout << subText << " :: " << result << std::endl;
				return;
			}
			averageTimeFail += std::chrono::duration<double, std::milli>(end - start).count();
		}
		averageTimeSuccsess /= iters;
		averageTimeFail /= iters;
		std::cout << "Size substr: " << lenSubStr << " (succsess)T(n) = " << averageTimeSuccsess << " (fail)T(n) = "<< averageTimeFail << std::endl;
		i++;
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
	const int step = 1000000;
	std::cout << "KMP search by size text:" << std::endl;
	checkSearchBySizeText(kmpSearch, step);
	std::cout << "KMP search by size substr:" << std::endl;
	checkSearchBySizeSubstr(kmpSearch, step);
	std::cout << "Strstr search by size text:" << std::endl;
	checkSearchBySizeText(step);
	std::cout << "Strstr search by size substr:" << std::endl;
	checkSearchBySizeSubstr(step);
	return 0;
}