#include <iostream>

int* genArray(const int len) {
	int* array = new int[len];
	for (int i = 0; i < len; i++) array[i] = i;
	return array;
}

int searchSequential(int* array, const int len, const int searchingNumber, const int begin = 0) {
	if (array && len > 0) {
		for (int i = begin; i < len; i++) {
			if (array[i] == searchingNumber) {
				return array[i];
			}
		}
	}
	return 0;
}

int searchJumpLVL1(int* array, const int len, const int searchingNumber) {
	int i = sqrt(len);
	while (array[i] < searchingNumber)
		i += sqrt(len);
	return searchSequential(array, i, searchingNumber);
}

int searchJumpLVL2(int* array, const int len, const int searchingNumber) {
	int i = sqrt(len);
	while (array[i] < searchingNumber)
		i += sqrt(len);
	while (array[i] > searchingNumber)
		i -= sqrt(len);
	return searchSequential(array, len, searchingNumber, i);
}

int searchBinary(int* array,const int begin, const int end, const int searchingNumber) {
	int mid = end + begin / 2;
	if (array[mid] < searchingNumber)
		return searchBinary(array, mid+1, end, searchingNumber);
	else if (array[mid] > searchingNumber)
		return searchBinary(array, begin, mid-1,searchingNumber);
	return array[mid];
}

int searchBinary(int* array, const int len, const int searchingNumber) {
	return searchBinary(array, 0, len-1, searchingNumber);
}

int searchInterpolation(int* array, const int left, const int right, const int searchingNumber) {
	int index = (searchingNumber - array[left]) * (left - right) / (array[left] - array[right]) + left;
	if (array[index] < searchingNumber)
		return searchBinary(array, index+1, right, searchingNumber);
	else if (array[index] > searchingNumber)
		return searchBinary(array, left, index-1, searchingNumber);
	return array[index];
}

int searchInterpolation(int* array, const int len, const int searchingNumber) {
	return searchInterpolation(array, 0, len - 1, searchingNumber);
}

void checkSearchFunction(int funcSearch(int*,const int,const int)) {
	const int len = 1000;
	int searchingNumber = 254;
	int* array = genArray(len);
	if (funcSearch(array, len, searchingNumber) == searchingNumber) {
		std::cout << "Search is work!" << std::endl;
	}
	else std::cout << "FAILED" << std::endl;
}

int main(void) {
	checkSearchFunction(searchBinary);
	checkSearchFunction(searchJumpLVL1);
	checkSearchFunction(searchJumpLVL2);
	checkSearchFunction(searchInterpolation);
	return 0;
}