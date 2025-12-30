#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

// 학생 구조체 정의
struct StudentInfo {
	string name;
	vector<int> scores;
	int sum;
	float average;
};

// 재사용성이 있게 함수 이름을 특정 행동만 하는것이 아닌 합을 가져온다 라는 뜻으로 설정.
// 값을 복사하여 넘겨주면 오버헤드가 너무 많이 발생하므로 레퍼런스로 넘겨줌.
// 값을 읽기만 하니 const 붙여주기
int getSum(const vector<int>& values) {
	int sum = 0;
	for (const int i : values)
		sum += i;
	return sum;

	// 더 좋은 방법
	// sum = std::accumulate(values.begin(), values.end(), 0);
	// return sum;
	// accumulate(시작 인덱스, 마지막 인덱스, 더한 값을 저장해줄 변수의 초기값)
	// #include <numeric>에 저장되어있음.
}


// getSum함수와 동일하게 설정.
// 값을 읽기만하니 const 붙여주기
float getAverage(const vector<int>& values) {
	float sum = 0;
	float average = 0;
	for (const float i : values)
		sum = sum + i;
	average = sum / values.size();
	return average;
}


// struct벡터에서 인덱스를 하나 불러와서 출력해주는 함수
// 여기도 오버헤드가 적도록 값의 원본을 호출
// 값을 읽기만 하니 인자에 const붙여주기
void printStudentstruct(const StudentInfo& st) {
	cout << st.name;
	for (const int v : st.scores)
		cout << "\t" << v;
	cout << "\t" << st.sum << "\t" << st.average << endl;
}


// struct 벡터에서 값을 하나씩 넘겨주는 함수.
// 마찬가지로 오버헤드가 적도록 값의 원본을 호출.
// 값을 읽기만 하니 인자에 const 붙여주기
void printStudentvector(const vector<StudentInfo>& st) {
	int index = 1;
	for (const StudentInfo v : st) {
		cout << index << "  ";
		printStudentstruct(v);
		index++;
	}
}

// 오버헤드가 적도록 값의 원본을 불러옴.
// struct의 값을 변경해야됨. 그러므로 struct는 const 붙이지 말고 값의 변경이 필요없는 score벡터의 크기만 읽는 vLength는 const붙이기
void makeStudentVector(struct StudentInfo& st, const int& vLength) {
	st.scores.resize(vLength);
	cin >> st.name;
	for (auto it = st.scores.begin(); it != st.scores.end(); ++it)
		cin >> *it;

	// range-based for loop ver.
	/*
	vector<int>& scores = st.scores;
	for (int& score : scores) {
		cin >> score;
	}
	*/

	st.sum = getSum(st.scores);
	st.average = getAverage(st.scores);
}



int main() {

	int studentNum, subjectNum;
	cout << "Enter student number and subject number : ";
	cin >> studentNum >> subjectNum;
	vector<StudentInfo> studentVector(studentNum);
	for (auto it = studentVector.begin(); it != studentVector.end(); ++it)
		makeStudentVector(*it, subjectNum);
	printStudentvector(studentVector);
}
