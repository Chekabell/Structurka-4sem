#include <iostream>
#include <unordered_map>
#include <math.h>

//Функция для заполнения массива вещественными или целочисленными значениями в порядке возрастания
void ordered(int* arr, const int len, int step = 5) {
	int tmp = 0;
	for (int i = 0; i <= len; i++) {
		arr[i] = tmp;
		tmp += step;
	}
};

//Функция для заполнения массива вещественными или целочисленными значениями в порядке убывания
void orderedBack(int* arr, const int len, int step = 5) {
	int tmp = len;
	for (int i = 0; i <= len; i++) {
		arr[i] = tmp;
		tmp -= step;
	}
};

//Функция для заполнения массива случайными вещественными или целочисленными значениями
void randSeq(int* arr, const int len, int max = 10) {
	srand(time(0));
	for (int i = 0; i < len; i++) {
		arr[i] = rand()%max;
	}
};

//Функция для заполнения массива целочисленными значениями в виде ступенчатого распределения
void stairRand(int* arr, const int len, int interval = 5, int mincoleb = 0, int maxcoleb = 50) {
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

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubbleSortMod(int* arr, int n){
	int i, j;
	int index;
	for (i = 0; i < n - 1; i++) {
		index = 0;
		for (j = index; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
				index = j + 1;
			}
		}
	}
}


void merge(int array[], int const left, int const mid, int const right){
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
        if (leftArray[indexOfSubArrayOne] <=
            rightArray[indexOfSubArrayTwo])
        {
            array[indexOfMergedArray] =
                leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else
        {
            array[indexOfMergedArray] =
                rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne)
    {
        array[indexOfMergedArray] =
            leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo)
    {
        array[indexOfMergedArray] =
            rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(int array[], int const begin, int const end){   
    // Returns recursively
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

void printArray(int* array, const int len) {
    for (int i = 1; i <= len; i++) {
        std::cout << array[i-1] << " ";
        if (i % 10 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

void sortInsertion(int* arr, int len)
{
    int i, j;
    int V;
    for (i = 1; i < len; i++)
    {
        V = arr[i];
        for (j = i; j > 0 && arr[j - 1] > V; j--)
            arr[j] = arr[j - 1];
        arr[j] = V;
    }
}

int digit_at(int x, int d)
{
    return (int)(x / pow(10, d - 1)) % 10;
}

// The main function to sort array using
// MSD Radix Sort recursively
void MSD_sort(int* arr, int lo, int hi, int d)
{
    if (d <= 2) {
        sortInsertion(arr, hi+1);
        return;
    }
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
        int c = digit_at(arr[i], d);
        count[c + 2]++;
    }

    // Change count[] so that count[] now contains actual
    // position of this digits in temp[]
    for (int r = 0; r < 10 + 1; r++)
        count[r + 1] += count[r];

    // Build the temp
    for (int i = lo; i <= hi; i++) {
        int c = digit_at(arr[i], d);
        temp[count[c + 1]++] = arr[i];
    }

    // Copy all integers of temp to arr[], so that arr[] now
    // contains partially sorted integers
    for (int i = lo; i <= hi; i++)
        arr[i] = temp[i - lo];

    // Recursively MSD_sort() on each partially sorted
    // integers set to sort them by their next digit
    for (int r = 0; r < 10; r++)
        MSD_sort(arr, lo + count[r], lo + count[r + 1] - 1,
            d - 1);
}

// function find the largest integer
int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// Main function to call MSD_sort
void radixsort(int* arr, int len)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr, len);

    // get the length of the largest integer
    int d = floor(log10(abs(m))) + 1;

    // function call
    MSD_sort(arr, 0, len - 1, d);
}

bool verifyArray(int* arr, int len) {
    for (int i = 0; i < len-1; i++) {
        if (arr[i] > arr[i + 1]) {
            std::cout << arr[i] << " " << arr[i + 1] << std::endl;
            return false;
        }
    }
    return true;
}


int main(void)
{
    const int len = 500000;
    int *arr = new int[len];
    for (int i = 1; i <= 10; i++) {
        randSeq(arr, len);
        radixsort(arr, len);
        verifyArray(arr, len);
        std::cout << i << ": check" << std::endl;
    }

    return 0;
}