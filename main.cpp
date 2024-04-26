#include <iostream>

int globalCount = 0;

int* genArray(const int len) {
	int* array = new int[len];
	int number = 1;
	for (int i = 0; i < len; i++) {
		array[i] = number;
		number += 2;
	}
	return array;
}

int searchJumpLVL1(int* array, const int len, const int searchingNumber) {
	const int jump = sqrt(len);
	int stepLeft = 0;
	int stepRight = jump;
	while (globalCount++, array[std::min(stepRight, len) - 1] < searchingNumber) {
		stepLeft = stepRight;
		stepRight += jump;
		if (stepLeft >= len) return 0;
	}
	while (globalCount++, array[stepLeft] < searchingNumber) {
		stepLeft++;
		if (stepLeft >= std::min(stepRight, len)) return 0;
	}

	if (globalCount++, array[stepLeft] == searchingNumber) return array[stepLeft];
	return 0;
}

int searchJumpLVL2(int* array, const int len, const int searchingNumber) {
	const int jump = sqrt(len);
	const int jump2 = sqrt(jump);
	int stepLeft = 0;
	int stepRight = jump;

	while (globalCount++, array[std::min(stepRight, len) - 1] < searchingNumber) {
		stepLeft = stepRight;
		stepRight += jump;
		if (stepLeft >= len) return 0;
	}

	int len2 = stepRight;
	stepRight = stepLeft + jump2;

	while (globalCount++, array[std::min(stepRight, len2) - 1] < searchingNumber) {
		stepLeft = stepRight;
		stepRight += jump2;
		if (stepLeft >= len) return 0;
	}
	while (globalCount++, array[stepLeft] < searchingNumber) {
		stepLeft++;
		if (stepLeft >= std::min(stepRight, len2)) return 0;
	}

	if (globalCount++, array[stepLeft] == searchingNumber) return array[stepLeft];
	return 0;
}

int searchBinary(int* array, int begin, int end, const int searchingNumber) {
	int mid;
	while (begin <= end) {
		mid = begin + (end - begin) / 2;
		if (globalCount++, array[mid] == searchingNumber) return array[mid];
		if (globalCount++, array[mid] > searchingNumber) end = mid - 1;
		else begin = mid + 1;
	}
	return 0;
}

int searchBinary(int* array, const int len, const int searchingNumber) {
	return searchBinary(array, 0, len-1, searchingNumber);
}

int searchInterpolation(int* array, int left, int right, const int searchingNumber) {
	int index;
	while (left <= right && (globalCount++, searchingNumber >= array[left]) && (globalCount++, searchingNumber <= array[right])) {
		index = left + (((double)(right - left) / (array[right] - array[left])) * (searchingNumber - array[left]));
		if (globalCount++, array[index] == searchingNumber) return array[index];
		if (globalCount++, array[index] > searchingNumber) right = index - 1;
		else left = index + 1;
	}
	return 0;
}

int searchInterpolation(int* array, const int len, const int searchingNumber) {
	return searchInterpolation(array, 0, len - 1, searchingNumber);
}

int genUnevenNumber(int len) {
	int number = rand() % (len-2);
	if (number % 2 == 0) number++;
	return number;
}

int genEvenNumber(int len) {
	int number = rand() % (len-2);
	if (number % 2 != 0) number++;
	return number;
}

void checkSearchFunction(int funcSearch(int*, const int, const int), const int step) {
	int maxLen = step * 10;
	for (int nowLen = step; nowLen <= maxLen; nowLen += step) {
		int searchingNumberExist;
		int* array = genArray(nowLen);
		int j = 0;
		globalCount = 0;
		std::cout << "LEN ARRAY: " << nowLen << std::endl;
		while (j < 1000) {
			searchingNumberExist = genUnevenNumber(nowLen);
			if (funcSearch(array, nowLen, searchingNumberExist) == searchingNumberExist) j++;
			else {
				std::cout << "FAIL" << std::endl;
				return;
			}
		}
		std::cout << "Existing - " << globalCount/j << std::endl;
		globalCount = 0;
		j = 0;
		while (j < 1000) {
			if (funcSearch(array, nowLen, genEvenNumber(nowLen))) {
				std::cout << "FAIL" << std::endl;
				return;
			}
			else j++;
		}
		std::cout << "NOT existing - " << globalCount/j << std::endl;
	}
}

int searchJumpForResearch(int *array, const int len, const int searchingNumber, const int jump) {
	int stepLeft = 0;
	int stepRight = jump;

	while (globalCount++, array[std::min(stepRight,len)-1] < searchingNumber) {
		stepLeft = stepRight;
		stepRight += jump;
		if (stepLeft >= len) return 0;
	}

	while (globalCount++, array[stepLeft] < searchingNumber) {
		stepLeft++;
		if (stepLeft >= std::min(stepRight,len)) return 0;
	}
	
	if (globalCount++, array[stepLeft] == searchingNumber) return array[stepLeft];
	return 0;
}

void researchJump(const int step) {
	int maxLen = step * 5;
	int stepJump;
	for (int nowLen = step; nowLen <= maxLen; nowLen += step) {
		int* array = genArray(nowLen);
		stepJump = 1;
		std::cout << "LEN ARRAY:" << nowLen << "sqrt = "<< sqrt(nowLen) << std::endl;
		while (stepJump <= nowLen / 2) {
			int it;
			globalCount = 0;
			for (it = 1; it <= 100; it++) {
				int searchingNumber = genUnevenNumber(nowLen);
				if (searchJumpForResearch(array, nowLen, searchingNumber, stepJump) != searchingNumber) {
					std::cout << "WTF " << searchingNumber << " WTF" << std::endl;
					std::cout << "FAIL" << std::endl;
					return;
				}
			}
			std::cout << globalCount / it << std::endl;
			stepJump++;
		}
	}
}

int main(void) {
	srand(time(NULL));
	int step = 10000000;
	std::cout << "=======BINARY=======" << std::endl;
	checkSearchFunction(searchBinary,step);
	std::cout << "====================" << std::endl;
	std::cout << "====INTERPOLATION====" << std::endl;
	checkSearchFunction(searchInterpolation, step);
	std::cout << "=====================" << std::endl;
	std::cout << "======JUMPLVL1======" << std::endl;
	checkSearchFunction(searchJumpLVL1, step);
	std::cout << "====================" << std::endl;
	std::cout << "======JUMPLVL2======" << std::endl;
	checkSearchFunction(searchJumpLVL2, step);
	std::cout << "====================" << std::endl;

	/*for (int i = 0; i <= 100; i++) {
		std::cout << genEvenNumber(step) << std::endl;
	}*/
	/*researchJump(step);*/

	/*int* array = genArray(1000);
	std::cout << array[5] << std::endl;
	std::cout << searchBinary(array, 1000, 5) << std::endl;*/

	return 0;
}