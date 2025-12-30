#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

char gainGrade(int score) {
	if (score <= 100 && score >= 90) {
		return 'A';
	}
	else if (score < 90 && score >= 80) {
		return 'B';
	}
	else if (score < 80 && score >= 70) {
		return 'C';
	}
	else if (score < 70 && score >= 60) {
		return 'D';
	}
	else {
		return 'F';
	}
}
int scoreSum(int scoreArr[], int cnt) {
	if (scoreArr == nullptr) return 0; // defensive programming 예외처리 꼭 해줘야됨
	if (cnt <= 0) return 0; // defensive programming 예외처리 꼭 해줘야됨
	
	int sum = 0;
	for (int i = 0; i < cnt; i++) {
		sum = sum + scoreArr[i];
	}
	return sum;
}
/* 조금 더 좋은 코드
char getGrade(const int score){
	const char grade[] = {'A','B','C','D'};
	const int gradeCount = sizeof(grades) / sizeof(grade[0]);
	const int lowScore[gradeCount] = {90,80,70,60};
	
	char grade = 'F';
	for(int i = 0; i < gradeCount; i++){
		if(score >= lowScore[i]){
			grade = grades[i];
			break;
		}
	}
	return grade;
}
*/
float scoreAverage(int scoreArr[], int cnt) {
	if (scoreArr == nullptr) return 0.0F; // defensive programming 예외처리 꼭 해줘야됨
	if (cnt <= 0) return 0.0F; // defensive programming 예외처리 꼭 해줘야됨

	float avg = 0;
	int sum = 0;
	for (int i = 0; i < cnt; i++) {
		sum = sum + scoreArr[i];
	}
	avg = (float)sum / (float)cnt;
	if (cnt != 0) // 예외처리
		return avg;
	else
		return 0;
}
int main(void) {
	string name; // 학생의 이름을 받는 변수
	int studentArr[100] = { 0 }; // 각 학생의 점수를 저장해줄 배열
	int cnt = 0; // 정상적인 학생의 수를 계산하는 변수 ** cnt말고 사전에 나온단어만 이용할것 ex) count **
	int score = 0; // 학생의 점수를 받는 변수

	while (score >= 0 || score <= 100) { // 학생 점수가 0 미만, 100 초과면 반복문 탈출
		cout << "Enter a name and score: ";
		cin >> name >> score;
		char grade = gainGrade(score); // 학생의 등급정보를 받아옴
		if (score < 0 || score > 100) {
			cout << "Bye " << name;
			break;
		}
		cout << "Hi " << name << "! " << "Your grade is " << grade << endl;
		studentArr[cnt] = score;
		cnt++;
	}
	cout << endl << endl << endl;
	cout << "Score Count: " << cnt << endl;
	int sum = scoreSum(studentArr, cnt); // 학생의 점수 합을 받아옴
	cout << "Total Score: " << sum << endl;
	float average = scoreAverage(studentArr, cnt); // 학생의 점수 평균을 받아옴
	cout << "Score Average: " << fixed << setprecision(2) << average;
	return 0;
}