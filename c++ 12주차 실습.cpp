#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

class Complex {
	float real, imaginary;
public:
	Complex() = default;
	Complex(const float _real, const float _imaginary) : real(_real), imaginary(_imaginary) {}
	Complex(const Complex& complex) {
		real = complex.real;
		imaginary = complex.imaginary;
	}
	Complex& operator = (const Complex&) = default;

	bool operator == (const Complex& complex) const {
		return (real == complex.real && imaginary == complex.imaginary);
	}

	friend ostream& operator << (ostream& os, const Complex& complex);
};
ostream& operator << (ostream& os, const Complex& complex) {
	os << complex.real << " + " << complex.imaginary << "i";
	return os;
}

class MyString {
	char* str;
	void deleteString() {
		delete[] str;
	}

	void copyString(const char* string) {
		str = new char[strlen(string) + 1];
		strcpy(str, string);
	}

public:
	MyString() {
		str = new char[1];
		copyString("");
	}
	MyString(const char* string) {
		copyString(string);
	}
	MyString(const MyString& mystring) {
		copyString(mystring.str);
	}

	MyString& operator = (const MyString& mystring) {
		if (this == &mystring)
			return *this;

		deleteString();
		copyString(mystring.str);

		return *this;
	}

	bool operator == (const MyString& mystring) const {
		return strcmp(mystring.str, str) == 0;
	}

	friend ostream& operator << (ostream& os, const MyString& mystring);

	~MyString() { deleteString(); }
};

ostream& operator << (ostream& os, const MyString& mystring) {
	os << mystring.str;
	return os;
}

template <typename T>
class List {
	T* items{ nullptr };
	int count{ 0 }; // the number of items stored in the list
	int size{ 0 }; // capacity

	void deleteList() {
		if (items == nullptr) return;

		delete[] items;
	}
	void copyList(const List& list) {
		count = list.count;
		size = list.size;
		items = new T[list.size];

		for (int i = 0; i < list.count; i++) {
			items[i] = list.items[i];
		}
	}

public:
	List(const int _size) : count(0), size(_size) {
		items = new T[_size];
	}
	List(const List& list) {
		copyList(list);
	}

	List& operator = (const List& list) {
		if (&list == this)
			return *this;

		deleteList();
		copyList(list);

		return *this;
	}
	void add(const T& item) {
		items[count] = item;
		count++;
	}
	bool find(const T& item) {
		for (int i = 0; i < count; i++) {
			if (items[i] == item)
				return true;
		}
		return false;
	}
	int getCount() const {
		return this->count;
	}
	T operator [] (int i) {
		return items[i];
	}
	const T operator [] (int i) const {
		return items[i];
	}
	~List() { deleteList(); }
};
template <typename T>
ostream& operator << (ostream& os, const List<T>& list) {
	for (int i = 0; i < list.getCount(); i++)
		os << list[i] << endl;
	return os;
}

int main() {
	List<Complex> cList(100);

	cList.add(Complex(0, 0));
	cList.add(Complex(1, 1));
	cout << cList << endl;

	cout << std::boolalpha;
	cout << cList.find(Complex(1, 1)) << endl;	// true
	cout << cList.find(Complex(1, 0)) << endl;	// false

	List<MyString> sList(200);
	sList.add("Banana");
	sList.add("Apple");
	cout << sList << endl;
	cout << sList.find("Banana") << endl;	// true
	cout << sList.find("Melon") << endl;	// false

	List<MyString> s2List{ sList };
	s2List.add("Strawberry");
	cout << s2List << endl;

	List<MyString> s3List(10);
	s3List = s2List;
	s3List.add("Grape");
	cout << s3List << endl;

	//s3List.sort();
	cout << s3List << endl;
}