#include <iostream>
#include <unordered_map>
#include <chrono>

enum class MethodGenArray {Ordered,OrderedBack,Rand,StairRand,LAST};

MethodGenArray & operator ++ (MethodGenArray& e)
{
    if (e == MethodGenArray::LAST) {
        throw std::out_of_range("for E& operator ++ (E&)");
    }
    e = MethodGenArray(static_cast<std::underlying_type<MethodGenArray>::type>(e) + 1);
    return e;
}

int globalSn = 0;

//Function for filling array int in increase order
void genOrderedSeq(int* arr, const int len, int step = 5) {
	int tmp = 0;
	for (int i = 0; i <= len; i++) {
		arr[i] = tmp;
		tmp += step;
	}
};

//Function for filling array int in decrease order
void genOrderedBackSeq(int* arr, const int len, int step = 5) {
	int tmp = len*len;
	for (int i = 0; i <= len; i++) {
		arr[i] = tmp;
		tmp -= step;
	}
};

//Function for filling array random int
void genRandSeq(int* arr, const int len, int max = 1000) {
	srand(time(0));
	for (int i = 0; i < len; i++) {
		arr[i] = rand()%max;
	}
};

//Function for filling array random int in stair order
void genStairRandSeq(int* arr, const int len, int interval = 5, int mincoleb = 0, int maxcoleb = 50) {
	srand(time(0));
	int step = maxcoleb - mincoleb;
	for (int i = 0, j = 0; i < len; i++, j++) {
		if (j >= interval) {
			j = 0;
			mincoleb += step;
			maxcoleb += step;
		}
		arr[i] = mincoleb + rand() % (maxcoleb - mincoleb +1);
	}
};

//function swap elements in array
void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// function find the largest integer
int getMax(int* arr, int n){
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

//Function bubble sort with index last swap
void bubbleSortMod(int* arr, int len){
	int i = len-1, j;
	int lastSwapIndex = 0;
	while (i > 0) {
        lastSwapIndex = -1;
		for (j = 0; j < i; j++) {
			if (globalSn++,arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
                lastSwapIndex = j;
			}
		}
        i = lastSwapIndex;
	}
}

//Function for getting a digit at the place of digit discharge
int digitAt(int x, int d) {
    return (int)(x / pow(10, d - 1)) % 10;
}

//Main function MSD sort
void msdSort(int* arr, int lo, int hi, int d) {
    // recursion break condition
    if (hi <= lo) {
        return;
    }
    int count[10 + 2] = { 0 };
    // temp is created to easily swap strings in arr[]
    std::unordered_map<int, int> temp;
    // Store occurrences of most significant character
    // from each integer in count[]
    for (int i = lo; i <= hi; i++) {
        int c = digitAt(arr[i], d);
        count[c + 2]++;
    }
    // Change count[] so that count[] now contains actual
    // position of this digits in temp[]
    for (int r = 0; r < 10 + 1; r++)
        count[r + 1] += count[r];
    // Build the temp
    for (int i = lo; i <= hi; i++) {
        int c = digitAt(arr[i], d);
        temp[count[c + 1]++] = arr[i];
    }
    // Copy all integers of temp to arr[], so that arr[] now
    // contains partially sorted integers
    for (int i = lo; i <= hi; i++)
        arr[i] = temp[i - lo];
    // Recursively MSD_sort() on each partially sorted
    // integers set to sort them by their next digit
    if (d >= 1) {
        for (int r = 0; r < 10; r++)
            msdSort(arr, lo + count[r], lo + count[r + 1] - 1, d - 1);
    }
} 

// Main function to call MSD_sort
void radixSort(int* arr, int len)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr, len);

    // get the length of the largest integer
    int d = floor(log10(abs(m))) + 1;

    // function call
    msdSort(arr, 0, len - 1, d);
}

//Function merge two massive
void merge(int* array, int const left, int const mid, int const right){
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    // Create temp arrays
    int* leftArray = new int[subArrayOne],
        * rightArray = new int[subArrayTwo];

    // Copy data to temp arrays leftArray[] 
    // and rightArray[]
    for (int i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    // Initial index of first sub-array
    // Initial index of second sub-array
    int indexOfSubArrayOne = 0,
        indexOfSubArrayTwo = 0;

    // Initial index of merged array
    int indexOfMergedArray = left;

    // Merge the temp arrays back into 
    // array[left..right]
    while (indexOfSubArrayOne < subArrayOne &&
        indexOfSubArrayTwo < subArrayTwo)
    {
        if (globalSn++,leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo])
        {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else{
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne)
    {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo)
    {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

void mergeSort(int* array, int const begin, int const end){   
    // Returns recursively
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

//Function for start mergeSort
void mergeSort(int* array, int len) {
    int begin = 0;
    int end = len - 1;
    mergeSort(array, begin, end);
}

//Function for output array
void printArray(int* array, const int len) {
    for (int i = 1; i <= len; i++) {
        std::cout << array[i-1] << " ";
        if (i % 10 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

//Function distribution generation array
int* genArray(MethodGenArray choice,const int len) {
    int* array = new int[len];
    switch (choice) {
    case MethodGenArray::Ordered:
        genOrderedSeq(array,len);
        break;
    case MethodGenArray::OrderedBack:
        genOrderedBackSeq(array, len);
        break;
    case MethodGenArray::Rand:
        genRandSeq(array, len);
        break;
    case MethodGenArray::StairRand:
        genStairRandSeq(array, len);
        break;
    }
    return array;
}

//Function check correct sort
bool verifyArray(int* arr, int len) {
    for (int i = 0; i < len-1; i++) {
        if (arr[i] > arr[i + 1]) {
            std::cout << i << ":" << arr[i] << " " << i + 1 << ":" << arr[i + 1] << std::endl;
            return false;
        }
    }
    return true;
}

//Function estimate complexity (T(n) and S(n))
void estimateComplexitySort(void func(int*,int), const int len) {
    std::string method[4] = { "Ordered","OrderedBack","Random","Stair" };
    int i = 0;
    for (MethodGenArray methods = MethodGenArray::Ordered; methods != MethodGenArray::LAST; ++methods) {
        int* array = genArray(methods, len);
        globalSn = 0;

        auto start = std::chrono::high_resolution_clock::now();
        func(array, len);
        auto end = std::chrono::high_resolution_clock::now();
        if (verifyArray(array,len)) {
            std::chrono::duration<double, std::milli> time = end - start;
            std::cout << method[i] << " T(n) = " << time.count() << " S(n) = " << globalSn << std::endl;
            i++;
        }
        else {
            std::cout << "\nSORT NOT WORK!" << std::endl;
            system("pause");
            exit(0);
        }
    }
}

int compare(const void* val1, const void* val2) {
    globalSn++;
    return (*(int*)val1 - *(int*)val2);
}

void estimateComplexityQSort(int len) {
    std::string method[4] = { "Ordered","OrderedBack","Random","Stair" };
    int i = 0;
    for (MethodGenArray methods = MethodGenArray::Ordered; methods != MethodGenArray::LAST; ++methods) {
        int* array = genArray(methods, len);
        globalSn = 0;

        auto start = std::chrono::high_resolution_clock::now();
        qsort(array, len,sizeof(int),compare);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> time = end - start;
        std::cout << method[i] << " T(n) = " << time.count() << " S(n) = " << globalSn << std::endl;
        i++;
    }
}

void printArray(int* array, const int len) {
    for (int i = 1; i <= len; i++) {
        std::cout << array[i-1] << " ";
        if (i % 10 == 0) {
            std::cout << std::endl;
        }
    }
}

int main(void){
    for (int i = 500; i <= 5000; i+=500) {
        std::cout << "\nSIZE: " << i << " ----------------" << std::endl;
        std::cout << "Bubble modified sort:" << std::endl;
        estimateComplexitySort(bubbleSortMod, i);
        std::cout << "\nRadix MSD sort:" << std::endl;
        estimateComplexitySort(radixSort, i);
        std::cout << "\nMerge sort:" << std::endl;
        estimateComplexitySort(mergeSort, i);
        std::cout << "\nstd::qsort:" << std::endl;
        estimateComplexityQSort(i);
    }

    //estimateComplexitySort(mergeSort,5000000);
    return 0;
}