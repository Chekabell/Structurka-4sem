#include <iostream>
#include <Windows.h>

enum class Func { Ordered, OrderedBack, RandSeq, SawRand, SinRand, StairRand, QuaziRand, Last };

struct time {
	int intTime;
	int doubleTime;
};
	
struct time a;

//Функция для заполнения массива вещественными или целочисленными значениями в порядке возрастания
template <typename T> void Ordered(T* arr, const int len, T step = 5) {
	T tmp = 0;
	for (int i = 0; i <= len; i++) {
		arr[i] = tmp;
		tmp += step;
	}
};

	//Функция для заполнения массива вещественными или целочисленными значениями в порядке убывания
template <typename T> void OrderedBack(T* arr, const int len, T step = 5) {
	T tmp = len;
	for (int i = 0; i <= len; i++) {
		arr[i] = tmp;
		tmp -= step;
	}
};

//Функция для заполнения массива случайными вещественными или целочисленными значениями
template <typename T> void RandSeq(T* arr, const int len, T max = 50) {
	srand(time(0));
	for (int i = 0; i < len; i++) {
		arr[i] = (double)rand() / RAND_MAX * max;
	}
};

//Функция для заполнения массива целочисленными значениями в виде пилообразного распределения
template <typename T> void SawRand(T* arr, const int len, int interval = 5, T min = 0, T max = 50) {
	T tmp = min;
	for (int i = 2; i <= len + 1; i++) {
		arr[i - 2] = tmp;
		tmp += (max - min) / interval;
		if (tmp >= max || i % interval == 1) {
			tmp = min;
		}
	}
};

//Функция для заполнения массива значениями в виде синусоидального распределения
template <typename T> void SinRand(T* arr, const int len, T range = 50) {
	for (int i = 0; i < len; i++) arr[i] = sin(i) * range;
};

//Функция для заполнения массива целочисленными значениями в виде ступенчатого распределения
template <typename T> void StairRand(T* arr, const int len, T interval = 5, T mincoleb = 0, T maxcoleb = 50) {
	srand(time(0));
	T step = maxcoleb - mincoleb;
	for (int i = 0, j = 0; i < len; i++, j++) {
		if (j >= interval) {
			j = 0;
			mincoleb += step;
			maxcoleb += step;
		}
		arr[i] = mincoleb + (double)rand() / RAND_MAX * (maxcoleb - mincoleb);
	}
};

//Функция для заполнения массива целочисленными значениями в виде квазирандомного распределения
template <typename T> void QuaziRand(T* arr, const int len, T min = 0, T max = 50, T step = 5) {
	srand(time(0));
	for (int i = 0; i < len; i++) {
		arr[i] = min + (double)rand() / RAND_MAX * (max - min);
		min += step;
		max += step;
	}
};

//Функция распределения для вызова функция по заполнению массивов данными
void Decor(enum Func key, int* masInt, double* masDouble, const int len){
	SYSTEMTIME st;
	int tmpTimeInt = 0, tmpTimeDouble = 0;
	GetLocalTime(&st);
	tmpTimeInt = (st.wSecond * 1000) + st.wMilliseconds;
	switch (key) {
		case Func::Ordered:
			Ordered<int>(masInt,len);
			GetLocalTime(&st);
			tmpTimeDouble = (st.wSecond * 1000) + st.wMilliseconds;
			Ordered<double>(masDouble, len);
			break;
		case Func::OrderedBack:
			OrderedBack<int>(masInt, len);
			GetLocalTime(&st);
			tmpTimeDouble = (st.wSecond * 1000) + st.wMilliseconds;
			Ordered<double>(masDouble, len);
			break;
		case Func::RandSeq:
			RandSeq<int>(masInt, len);
			GetLocalTime(&st);
			tmpTimeDouble = (st.wSecond * 1000) + st.wMilliseconds;
			RandSeq<double>(masDouble, len);
			break;
		case Func::SawRand:
			SawRand<int>(masInt, len);
			GetLocalTime(&st);
			tmpTimeDouble = (st.wSecond * 1000) + st.wMilliseconds;
			SawRand<double>(masDouble, len);
			break;
		case Func::SinRand:
			SinRand<int>(masInt, len);
			GetLocalTime(&st);
			tmpTimeDouble = (st.wSecond * 1000) + st.wMilliseconds;
			SinRand<double>(masDouble, len);
			break;
		case Func::StairRand:
			StairRand<int>(masInt, len);
			GetLocalTime(&st);
			tmpTimeDouble = (st.wSecond * 1000) + st.wMilliseconds;
			StairRand<double>(masDouble, len);
			break;
		case Func::QuaziRand:
			QuaziRand<int>(masInt, len);
			GetLocalTime(&st);
			tmpTimeDouble = (st.wSecond * 1000) + st.wMilliseconds;
			QuaziRand<double>(masDouble, len);
			break;
	}
	GetLocalTime(&st);
	a.intTime = std::abs(tmpTimeDouble - tmpTimeInt);
	a.doubleTime = std::abs((st.wSecond * 1000) + st.wMilliseconds - tmpTimeDouble);
}


int main(void) {
	const int len = 100;
	auto* massiveDouble = new double[len];
	auto* massiveInt = new int[len];
	Decor(Func::Ordered,massiveInt,massiveDouble,len);
	std::cout << "Ordered Int = " << a.intTime << "\nOrdered Double = " << a.doubleTime << std::endl;
	Decor(Func::OrderedBack, massiveInt, massiveDouble, len);
	std::cout << "OrderedBack Int = " << a.intTime << "\nOrderedBack Double = " << a.doubleTime << std::endl;
	Decor(Func::RandSeq, massiveInt, massiveDouble, len);
	std::cout << "RandSeq Int = " << a.intTime << "\nRandSeq Double = " << a.doubleTime << std::endl;
	Decor(Func::SawRand, massiveInt, massiveDouble, len);
	std::cout << "SawRand Int = " << a.intTime << "\nSawRand Double = " << a.doubleTime << std::endl;
	Decor(Func::SinRand, massiveInt, massiveDouble, len);
	std::cout << "SinRand Int = " << a.intTime << "\nSinRand Double = " << a.doubleTime << std::endl;
	Decor(Func::StairRand, massiveInt, massiveDouble, len);
	std::cout << "StairRand Int = " << a.intTime << "\nStairRand Double = " << a.doubleTime << std::endl;
	Decor(Func::QuaziRand, massiveInt, massiveDouble, len);
	std::cout << "QuaziRand Int = " << a.intTime << "\nQuaziRand Double = " << a.doubleTime << std::endl;

	/*QuaziRand<double>(massiveDouble, len);
	for (int i = 0; i < len; i++) {
		std::cout << massiveDouble[i] << (i%9!=0 || i==0 ? " ":"\n");
	}*/
	return 0;
}
