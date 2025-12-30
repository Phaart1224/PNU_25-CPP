/*
#define _CRT_SECURE_NO_WARNINGS
# include <cstdlib>
# include <cstdio>



const int NUMBER_STUDENTS = 2;
const int NUMBER_QUIZZES = 3;
void readScores(const int score[NUMBER_STUDENTS][NUMBER_QUIZZES]) {
	for (int row = 0; row < NUMBER_STUDENTS; row++) {
		for (int column = 0; column < NUMBER_QUIZZES; column++)
			scanf("%d", &score[row][column]);
	}
}
void display(const int score[NUMBER_STUDENTS][NUMBER_QUIZZES]) {
	for (int row = 0; row < NUMBER_STUDENTS; row++) {
		for (int column = 0; column < NUMBER_QUIZZES; column++){
			printf("%5d", score[row][column]);
		}
		printf("\n");
	}
	printf("\n");
}
void display(const float* average, const int number) {
	for (int row = 0; row < number; row++)
		printf("%lf   ", average[row]);
	printf("\n");
}
void computeStudentAverage(const int score[NUMBER_STUDENTS][NUMBER_QUIZZES], float* average) {
	float sum = 0;
	for (int row = 0; row < NUMBER_STUDENTS; row++) {
		for (int column = 0; column < NUMBER_QUIZZES; column++) {
			sum += score[row][column];
		}
		average[row] = sum;
	}
}
void computeQuizAverage(const int score[NUMBER_STUDENTS][NUMBER_QUIZZES], float* average){
	float sum = 0;
	for (int column = 0; column < NUMBER_QUIZZES; column++) {
		for (int row = 0; row < NUMBER_STUDENTS; row++) {
			sum += score[row][column];
		}
		average[column] = sum;
	}
}

int main() {
	int scores[NUMBER_STUDENTS][NUMBER_QUIZZES];
	float studentAverage[NUMBER_STUDENTS];
	float quizAverage[NUMBER_QUIZZES];

	readScores(scores);

	printf("Student/Quiz Scores:\n");
	display(scores);

	computeStudentAverage(scores, studentAverage);
	printf("Student Average:\n");
	display(studentAverage, NUMBER_STUDENTS);

	computeQuizAverage(scores, quizAverage);
	printf("Quiz Average:\n");
	display(quizAverage, NUMBER_QUIZZES);
}
*/


# include <cstring>
# include <iostream>

using namespace std;

class Complex {
private:
	float real, imaginary;

public:
	Complex(const float real=0.0F, const float imaginary=0.0F) {
		this->real = real;
		this->imaginary = imaginary;
	}

	bool operator == (const Complex& c) const {
		return real == c.real && imaginary == c.imaginary;
	}

	friend ostream& operator << (ostream& os, const Complex& c);

};

ostream& operator << (ostream& os, const Complex& c) {
	cout << c.real << " + " << c.imaginary << "i";
}


class MyString {
private:
	char* str;

public:
	MyString(const char* const _str="") {
		str = new char[strlen(_str)+1];
		strcpy(str, _str);
	}
	MyString(const MyString& s) {
		str = new char[strlen(s.str)+1];
		strcpy(str, s.str);
	}
	~MyString() { delete [] str;}

	MyString operator = (const MyString& s) {
		delete [] str;
		str = new char[strlen(s.str)+1];
		strcpy(str, s.str);
	}
	bool operator == (const MyString& s) const {
		return strcmp(str, s.str) == 0;
	}
	friend ostream& operator << (ostream& os, const MyString& str);

};

ostream& operator << (ostream& os, const MyString& str) {
	cout << str.str;
}

template <class T>
class List {
	T* items{nullptr};
	int count{0};
	int size{0};

	void copyItems(const List& list) {
		this->items = new T[list.size];
		this->size = list.size;
		this->count = list.count;

		for ( int i=0; i < list.size; i ++ ) {
			items[i] = list.items[i];
		}
	}
public:
	List() = default;
	List(const int size) {
		items = new T[size];
		this->size = size;
	}
	~List() { delete [] items; }

	List(const T& list) {
		copyItems(list);
	}
	List& operator = (const List& list) {
		delete [] items;

		copyItems(list);

		return *this;
	}

	void add(const T& item) {
		items[count] = item;
		count++;
	}
	bool find(const T& item) const {
		for ( int i=0; i < count; i ++ ) {
			if ( items[i] == item ) return true;
		}
		return false;
	}
	T* getItems() const { return items; }
	int getCount() const { return count; }
};

template <class T>
ostream & operator << (ostream& os, const List<T>& list) {
	for ( int i=0; i < list.getCount(); i ++ )
		cout << list.getItems()[i] << endl;
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


