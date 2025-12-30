#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int rectangle_count = 0;

using namespace std;

struct Rectangle {
	int width;
	int height;
};

enum class CommandKind { ADD, SORT, PRINT, CLEAR, EXIT, INVALID };

bool compare(const Rectangle& a, const Rectangle& b) {
	return ((a.width * a.height) < (b.width * b.height));
}

string getCommand(string& command, const int commandLength) { // 명령어를 소문자로 바꿔주는 함수
	for (int i = 0; i < commandLength; i++) {
		command[i] = toupper(command[i]);
	}
	return command;
}

CommandKind getCommandKind(string& command) {
	command = getCommand(command, command.length());

	if (command == "ADD")
		return CommandKind::ADD;
	else if (command == "SORT")
		return CommandKind::SORT;
	else if (command == "PRINT")
		return CommandKind::PRINT;
	else if (command == "CLEAR") {
		rectangle_count = 0;
		return CommandKind::CLEAR;
	}
	else if (command == "EXIT")
		return CommandKind::EXIT;

	else return CommandKind::INVALID;
}

Rectangle getRectangle() {
	Rectangle r1;
	cin >> r1.width >> r1.height;
	rectangle_count++;
	return r1;
}

int getExtent(const int height, const int width) {
	return (width * height);
}

void print(const Rectangle& rectangle) {
	cout << rectangle.width << " " << rectangle.height << " " << getExtent(rectangle.height, rectangle.width) << endl;
}

void print(const vector<Rectangle>& rectangles) {
	cout << "Rectangle count: " << rectangle_count << endl;
	for (auto it = rectangles.begin(); it != rectangles.end(); it++)
		print(*it);
}

void sort(vector<Rectangle>& rectangles) {
	sort(rectangles.begin(), rectangles.end(), compare);
}

void main() {
	vector<Rectangle> rectangles{};

	while (true) {

		string commandString;
		cin >> commandString;
		const CommandKind command = getCommandKind(commandString);

		switch (command) {
		case CommandKind::ADD: {
			const Rectangle newRectangle = getRectangle();
			rectangles.push_back(newRectangle);
			break;
		}
		case CommandKind::PRINT:
			print(rectangles);
			// use const_iterator in print()
			// define and call print(const Rectangle&)
			break;
		case CommandKind::SORT: {
			sort(rectangles); // use iterators, define and call swap in sort()
			print(rectangles);
			break;
		}
		case CommandKind::CLEAR:  rectangles.clear(); break;
		case CommandKind::EXIT: break;
		default:  assert(false); break;
		}
		if (command == CommandKind::EXIT) break;
	}
	/*
	* 알아두면 좋은 벡터 함수
	* vector<int> v;
	* v.push_back(x)  .. 벡터 맨 뒤에 x요소를 추가
	* v.pop_back() .. 벡터 맨 뒤 요소를 제거
	* v.insert(pos,val) .. 벡터 pos 인덱스에 val값을 추가
	* v.erase(pos) .. pos 인덱스 요소를 제거 // auto it = v.erase(pos) 이런식으로 반환을 받는다면 삭제된 요소의 다음 요소를 가르키는 이터레이터를 반환
	* v.clear() .. 벡터의 모든 요소를 제거
	* v.begin() / end() 벡터의 앞, 뒤 반복자
	* v.rbegin(), v.rend() 벡터의 역방향 반복자 
	* v.cbegin(), v.cend() 벡터의 const 반복자
	* v.size() 벡터의 사이즈를 반환
	*/
}
