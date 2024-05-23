#include <iostream>
#include <vector>
#include <random>
#include <cmath>

#define M1 64
#define M2 67
#define K 200

struct Date {
	int month;
	int year;
	Date() {
		month = 0;
		year = 0;
	}
	Date(const int m, const int y) {
		month = m;
		year = y;
	}
	int _genKey() {
		return year*25 + month;
	}
	Date& operator = (const Date& a){
		month = a.month;
		year = a.year;
		return *this;
	}
	friend std::ostream& operator << (std::ostream &out, const Date* obj) {
		std::cout << obj->month << "." << obj->year;
		return out;
	}
};

class HashTableDate {
	friend void checkHashFunction(int, int);
protected:
	struct Node {
		int key;
		Date* date;
		Node(int k, Date* d) {
			key = k;
			date = d;
		}
	};
private:
	std::vector<Node>* array;
	int sizeHashTable;
	int quantityElements;
public:
	HashTableDate(const int size) {
		sizeHashTable = size;
		array = new std::vector<Node>[size];
		quantityElements = 0;
	}
	int add(struct Date* value) {
		int key = value->_genKey();
		array[_getIndex(key)].push_back(*(new Node(key, value)));
		quantityElements++;
		return key;
	}
	Date* operator [] (const int key) {
		int index = _getIndex(key);
		auto end =  array[index].end();
		for (auto iter = array[index].begin(); iter != end; iter++) {
			if (iter->key == key) return iter->date;
		}
		return nullptr;
	};
	void printAll() {
		for (int index = 0; index < sizeHashTable; index++) {
			if (array[index].empty()) continue;
			int lenVect = array[index].size();
			for (int i = 0; i < lenVect; i++) {
				std::cout << array[index][i].date << "<-value : key->" << array[index][i].key << std::endl;
			}
		}
	}
	int getSize() {
		return quantityElements;
	}
protected:
	int _getIndex(const int key) {
		double a;
		return (int)((double)sizeHashTable * modf((252.0 * 0.6180339887 * (double)key), &a));
	}
};
	
void checkHashFunction(int sizeTable, int quanitityKeys) {
	auto table = *new HashTableDate(sizeTable);
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<int> distrMonth(1, 12);
	std::uniform_int_distribution<int> distrYear(1972, 1992);
	for (int i = 0; i < quanitityKeys; i++)
		table.add(new Date(distrMonth(generator), distrYear(generator)));
	double summ = 0;
	for (int index = 0; index < sizeTable; index++) {
		auto size = table.array[index].size();
		std::cout << size << std::endl;
		summ += std::pow((size - ((double)quanitityKeys / sizeTable)), 2);
	}
	double xi2 = (double)sizeTable / (double)quanitityKeys * summ;
	std::cout << "xi2 = " << xi2 << std::endl;
}

int main(void) {
	checkHashFunction(M2,200);
}