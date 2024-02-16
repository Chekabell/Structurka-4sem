#include <iostream>

//Функция для заполнения массива вещественными значениями в порядке возрастания
void Ordered(double* arr, int len) {
	double tmp = 0;
	for (int i = 0; i <= len; i++){
		arr[i] = tmp;
		tmp += 0.01;
	}
};

//Функция для заполнения массива целочисленными значениями в порядке возрастания
void Ordered(int* arr, int len) {
	int tmp = 0;
	for (int i = 0; i <= len; i++) {
		arr[i] = tmp;
		tmp++;
	}
};

//Функция для заполнения массива вещественными значениями в порядке убывания
void OrderedBack(double* arr, int len) {
	double tmp = len * 0.01;
	for (int i = 0; i <= len; i++) {
		arr[i] = tmp;
		tmp -= 0.01;
	}
};

//Функция для заполнения массива целочисленными значениями в порядке убывания
void OrderedBack(int* arr, int len) {
	int tmp = len;
	for (int i = 0; i <= len; i++) {
		arr[i] = tmp;
		tmp--;
	}
};

//Функция для заполнения массива случайными целочисленными значениями
void RandSeq(int* arr, int len, int max) {
	srand(time(0));
	for (int i = 0; i < len; i++){
		arr[i] = rand() % (max - 1);
	}
}

//Функция для заполнения массива случайными вещественными значениями
void RandSeq(double* arr, int len, double max) {
	srand(time(0));
	for (int i = 0; i < len; i++) {
		arr[i] = (double)rand() / RAND_MAX * max;
	}
}

//Функция для заполнения массива целочисленными значениями в виде пилообразного распределения
void SawRand(int* arr, int len, int interval, int min = 0, int max = 5) {
	int tmp = min;
	for (int i = 1; i <= len; i++) { 
		arr[i-1] = tmp;
		tmp += (max - min)/interval;
		if (tmp >= max || i%interval == 1) {
			tmp = min;
		}
	}
}

//Функция для заполнения массива вещественными значениями в виде пилообразного распределения
void SawRand(double* arr, int len, double max = 5) {
	srand(time(0));
	double min = 0.5, tmpmax = 1.2;
	for (int i = 0; i < len; i++) {
		arr[i] = min + (double)rand() / RAND_MAX * (tmpmax - min);
		min++;
		tmpmax++;
		if (max <= min) min = 0.5, tmpmax = 1.2;
	}
}

//Функция для заполнения массива значениями в виде синусоидального распределения
void SinRand(double* arr, int len, double range = 1) {
	srand(time(0));
	for (int i = 0; i < len; i++) arr[i] = sin(i) * range;
}

void SinRand(int* arr, int len, int range = 2) {
	srand(time(0));
	for (int i = 0; i < len; i++) arr[i] = sin(i) * (range+1);
}

//Функция для заполнения массива целочисленными значениями в виде пилообразного распределения
void StairRand(int* arr, int len, int step = 1) {
	srand(time(0));
	int min = 0, max = 5;
	for (int j = 0, i = 0; i < len; i++, j++) {
		if (j >= step) {
			j = 0;
			min += 5;
			max += 5;
		}
		arr[i] = min + rand() % (max - min + 1);
	}
}

//Функция для заполнения массива вещественными значениями в виде ступенчатого распределения
void StairRand(double* arr, int len, int step) {
	srand(time(0));
	double min = 0, max = 5;
	for (int j = 0, i = 0; i < len; i++, j++) {
		if (j >= step) {
			j = 0;
			min += 5;
			max += 5;
		}
		arr[i] = min + (double)rand() / RAND_MAX * (max - min);
	}
}

//Функция для заполнения массива целочисленными значениями в виде ступенчатого распределения
void QuaziRand(int* arr, int len, int min, int max) {
	srand(time(0));
	for (int i = 0; i < len; i++){
		arr[i] = min + rand() % (max - min + 1);
		min++;
		max++;
	}
}

//Функция для заполнения массива вещественными значениями в виде ступенчатого распределения
void QuaziRand(double* arr, int len, double min, double max) {
	srand(time(0));
	for (int i = 0; i < len; i++) {
		arr[i] = min + (double)rand() / RAND_MAX * (max - min);
		min++;
		max++;
	}
}

int main(void) {
	const int len = 20;
	int massive[len];
	SawRand(massive, len, 6);
	for (int i = 0; i < len; i++) {
		std::cout << massive[i] << std::endl;
	}
}
