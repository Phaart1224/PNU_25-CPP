#include <iostream>

using namespace std;

class Matrix {
private:
	int** values;
	int row, column;

	void allocateMatrix(const int row, const int column) { // 2차원 배열을 할당하는 부분을 함수로 묶음
		this->row = row;
		this->column = column;
		values = new int* [row];
		for (int i = 0; i < row; i++) values[i] = new int[column];
	}

	void copyMatrix(const Matrix& object) { // 다른 오브젝트에서 값을 복사해오는 부분을 함수로 묶음
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				values[i][j] = object.values[i][j];
			}
		}
	}

	void deleteMatrix() { // values 배열을 메모리해제 하는 부분을 함수로 묶음
		if (values != nullptr) {
			for (int i = 0; i < this->row; i++)
				delete[] values[i];
			delete[] values;
		}
	}

public:
	Matrix(const int row, const int column) {
		allocateMatrix(row, column);
	}

	Matrix(const Matrix& object) {
		allocateMatrix(object.row, object.column);
		copyMatrix(object);
	}

	const Matrix& operator = (const Matrix& object) {
		if (&object != this) {
			deleteMatrix();
			allocateMatrix(object.row, object.column);
			copyMatrix(object);
		}
		return *this;
	}

	const Matrix operator + (const Matrix& object) const {
		Matrix temp(object.row, object.column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				temp.values[i][j] = values[i][j] + object.values[i][j];
			}
		}
		return temp;
	}

	const Matrix operator * (const int times) const {
		Matrix temp(this->row, this->column);
		for (int i = 0; i < temp.row; i++) {
			for (int j = 0; j < temp.column; j++) {
				temp.values[i][j] = values[i][j] * times;
			}
		}
		return temp;
	}

	friend istream& operator >> (istream& is, Matrix& object);
	friend ostream& operator << (ostream& os, const Matrix& object);

	~Matrix() { deleteMatrix(); }
};

istream& operator >> (istream& is, Matrix& object) {
	for (int i = 0; i < object.row; i++) {
		for (int j = 0; j < object.column; j++) {
			is >> object.values[i][j];
		}
	}
	return is;
}

ostream& operator << (ostream& os, const Matrix& object) {
	for (int i = 0; i < object.row; i++) {
		for (int j = 0; j < object.column; j++) {
			os << object.values[i][j] << " ";
		}
		cout << endl;
	}
	return os;
}

int main() {
	Matrix m1(2, 2), m2(2, 2);
	cin >> m1;
	cin >> m2;

	Matrix m3(m1 + m2);
	Matrix m4(2, 2);

	m4 = m3 * 10;

	cout << endl << m3;
	cout << endl << m4;
}