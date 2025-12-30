#include <iostream>
#include <string>
#include <limits>
using namespace std;

string getType(string typeString) {
	int i = 0;
	while (typeString[i] != '\0') {
		if (typeString[i] >= 'A' && typeString[i] <= 'Z')
			typeString[i] = typeString[i] + ('a' - 'A');
		i++;
	}
	return typeString;
} // tolower(), toupper()
int main() {
	int typeCountArray[5] = { 0 }; // 지역변수는 반드시 생성하는 즉시 초기화할것. 디버깅모드가 아닌 릴리즈모드에서 오류가 생길수있음
	while (true) {
		string type;
		cin >> type;
		type = getType(type);
		if (type == "quit")
			break;
		else if (type == "long") {
			cout << numeric_limits<long>::min() << '\t' << numeric_limits<long>::max() << endl;
			typeCountArray[2]++;
		}
		else if (type == "int") {
			cout << numeric_limits<int>::min() << '\t' << numeric_limits<int>::max() << endl;
			typeCountArray[1]++;
		}	
		else if (type == "float") {
			cout << numeric_limits<float>::min() << '\t' << numeric_limits<float>::max() << endl;
			typeCountArray[3]++;
		}
		else if (type == "char") {
			cout << static_cast<int>(numeric_limits<char>::min()) << '\t' << static_cast<int>(numeric_limits<char>::max()) << endl;
			typeCountArray[0]++;
		}
		else if (type == "double") {
			cout << numeric_limits<double>::min() << '\t' << numeric_limits<double>::max() << endl;
			typeCountArray[4]++;
		}
		else {
			continue;
		}
	}
	cout << "=== A list of # of types ===" << endl;
	cout << "char :" << typeCountArray[0] << endl;
	cout << "int :" << typeCountArray[1] << endl;
	cout << "long :" << typeCountArray[2] << endl;
	cout << "float :" << typeCountArray[3] << endl;
	cout << "double :" << typeCountArray[4] << endl;
}
// numeric_limits<Type>::max(), min() .. 타입의 최대, 최소값 반환
// 명시적으로 형 변환을 하려면 static_cast<Type>을 통해서 x타입으로 변환 가능