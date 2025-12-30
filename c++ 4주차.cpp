#include <iostream>
#include <cctype>
#include <string>
#include <cstring>

using namespace std;

string getCommand(string command, int commandLength) { // 명령어를 소문자로 바꿔주는 함수
	for (int i = 0; i < commandLength; i++) {
		command[i] = tolower(command[i]);
	}
	return command;
}
void doCommand(const string command,  int* const scoreArr, int* count, const int maxSize) { // 명령어를 인자로 받아서 시행하는 함수
	if (command == "add") { // 명령어가 add 일경우 
		if (*count >= maxSize) {
			cout << "Too many scores" << endl;
			return;
		}
		int score;
		cout << "Enter score : ";
		cin >> score;
		if (score > 100 || score < 0) {
			cout << "Score Should be between 0 and 100" << endl;
			return;
		}
		scoreArr[*count] = score;
		(*count)++;
		cout << score << " added" << endl;
	}
	else if (command == "sum") { // 명령어가 sum일 경우
		int scoreSum = 0;
		for (int i = 0; i < *count; i++) {
			scoreSum = scoreSum + scoreArr[i];
		}
		cout << "Sum : " << scoreSum << endl;
	}
	else if (command == "average") { // 명령어가 average일 경우
		float scoreAverage = 0;
		if (*count == 0)
			cout << "1개 이상의 정수가 입력되어야 한다" << endl;
		else {
			for (int i = 0; i < *count; i++)
				scoreAverage = scoreAverage + scoreArr[i];
			scoreAverage = scoreAverage / (*count);
		}
		cout << "Average : " << scoreAverage << endl;
	}
	else if (command == "list") { // 명령어가 list일 경우
		if ((*count) == 0) return;
		for (int i = 0; i < *count; i++) {
			cout << scoreArr[i] << " ";
		}
		cout << endl;
	}
	else return;
}
int main() {
	cout << "Enter the score count : ";
	int maxSize;
	cin >> maxSize;
	if (cin.fail()) //정수가 들어오지 않았을 때 예외 처리
		return 0;
	int count = 0; // 숫자배열의 add 호출 명령어 카운트
	int* const scores = new int[maxSize]; // 동적 할당 후에는 nullptr을 받았는지 꼭 확인하는 예외처리를 해야됨

	while (true) {
		string command;
		cout << "Enter command : (add, sum, average, list, quit)" << " ";
		cin >> command;
		int length = (int)command.length();
		command = getCommand(command, length);
		if (command == "quit") {
			cout << "Bye";
			break;
		}
		doCommand(command, scores, &count, maxSize);
	}
	delete[] scores;
	return 0;
}