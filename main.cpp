#include <iostream>

int globalCount = 0;

int* genArray(const int len) {
	int* array = new int[len];
	for (int i = 1; i < len; i++) array[i] = i;
	return array;
}

int searchSequential(int* array, const int begin, const int end, const int searchingNumber) {
	for (int i = begin; i <= end; i++) {
		if (globalCount++, array[i] == searchingNumber) {
			return array[i];
		}
	}
	return 0;
}

int searchJumpLVL1(int* array, const int len, const int searchingNumber) {
	int jump = sqrt(len);
	int stepLeft = 0;
	int stepRight = jump;
	while (globalCount++, array[stepRight] < searchingNumber) {
		stepLeft = stepRight;
		stepRight += jump;
		if (stepRight > len) return 0;
	}
	return searchSequential(array, stepLeft, stepRight, searchingNumber);
}

int searchJumpLVL2(int* array, const int len, const int searchingNumber) {
	int jump = sqrt(len);
	int stepLeft = 0;
	int stepRight = jump;
	int fixStepRight;
	while (globalCount++, array[stepRight] < searchingNumber) {
		stepLeft = stepRight;
		stepRight += jump;
		if (stepRight > len) return 0;
	}
	fixStepRight = stepRight;
	while (globalCount++, array[stepLeft] > searchingNumber) {
		stepRight = stepLeft;
		stepLeft -= jump;
		if (stepLeft < 0) return 0;
	}
	return searchSequential(array, stepLeft, fixStepRight, searchingNumber);
}

int searchBinary(int* array, int begin, int end, const int searchingNumber) {
	int mid;
	while (begin <= end) {
		mid = begin + (end - begin) / 2;
		if (globalCount++, array[mid] == searchingNumber) return array[mid];
		else if (globalCount++, array[mid] > searchingNumber) end = mid - 1;
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
		index = left + (((right - left) / (array[right] - array[left])) * (searchingNumber - array[left]));
		if (globalCount++, array[index] == searchingNumber) return array[index];
		if (globalCount++, array[index] > searchingNumber) right = index - 1;
		else left = index + 1;
	}
	return 0;
}

int searchInterpolation(int* array, const int len, const int searchingNumber) {
	return searchInterpolation(array, 0, len - 1, searchingNumber);
}

void checkSearchFunction(int funcSearch(int*, const int, const int), const int step) {
	int maxLen = step * 10;
	for (int nowLen = step; nowLen <= maxLen; nowLen += step) {
		int j = 0;
		int searchingNumberExist = rand() % nowLen;
		int searchingNumberNotExist = -1;
		globalCount = 0;
		j = 0;
		int* array = genArray(nowLen);
		std::cout << "LEN ARRAY: " << nowLen << std::endl;
		while (j < 10) {
			if (funcSearch(array, nowLen, (searchingNumberExist*(j+1))) == searchingNumberExist * (j + 1)) j++;
			else {
				std::cout << "FAIL" << std::endl;
				return;
			}
		}
		std::cout << "Existing  - " << globalCount/j << std::endl;
		globalCount = 0;
		if (funcSearch(array, nowLen, searchingNumberNotExist)){
			std::cout << "FAIL" << std::endl;
			return;
		}
		std::cout << "NOT existing  - " << globalCount << std::endl;
	}
}

int searchJumpForResearch(int *array, const int len, const int searchingNumber, const int jump) {
	int stepLeft = 0;
	int stepRight = jump;
	while (globalCount++, array[stepRight] < searchingNumber) {
		stepLeft = stepRight;
		stepRight += jump;
		if (stepRight > len) return 0;
	}
	return searchSequential(array, stepLeft, stepRight, searchingNumber);
}

void researchJump(const int step) {
	int maxLen = step * 5;
	int stepJump;
	for (int nowLen = step; nowLen <= maxLen; nowLen += step) {
		int searchingNumber = rand() % nowLen;
		int* array = genArray(nowLen);
		globalCount = 0;
		stepJump = 1;
		std::cout << "LEN ARRAY:" << nowLen << std::endl;
		while (stepJump <= nowLen / 2) {
			if (searchJumpForResearch(array, nowLen, searchingNumber, stepJump) == searchingNumber) {
				std::cout << /*stepJump << ": "<<*//*"Step Jump:: "<< stepJump << " Comparisons: " <<*/ globalCount << std::endl;
				stepJump++;
			}
			else {
				std::cout << "FAIL" << std::endl;
				return;
			}
		}
	}
}

int main(void) {
	srand(time(NULL));
	int step = 100;
	/*std::cout << "=======BINARY=======" << std::endl;
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
	std::cout << "====================" << std::endl;*/
	researchJump(step);
	/*int* array = genArray(1000);
	std::cout << array[5] << std::endl;
	std::cout << searchBinary(array, 1000, 5) << std::endl;*/

	return 0;
}