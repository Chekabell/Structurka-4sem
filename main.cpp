#include <iostream>
#include <vector>

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
	int genKey() {
		return month * year;
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
private:
	Date* array;
	int sizeHashTable;
public:
	HashTableDate(const int size) {
		sizeHashTable = size;
		array = new Date[size];
	}
	int hashDate(const int key) {
		return (int)(0.616161 * (float)key);
	}
	int getIndex(const int key) {
		return hashDate(key) % sizeHashTable;
	}
	void add(int key, const struct Date* value){
		array[getIndex(key)] = *value;
	}
	Date* operator [] (const int key) {
		int index = getIndex(key);
		return &array[index];
	};
};

int main(void) {
	HashTableDate table = *new HashTableDate(M1);
	Date* obj = new Date(5, 1975);
	int key = obj->genKey();
	table.add(key,obj);
	std::cout << table[key] << std::endl;
	return 0;
}