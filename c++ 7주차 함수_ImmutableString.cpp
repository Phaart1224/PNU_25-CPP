#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

class ImmutableString {
private:
	char* const str;
	const size_t size;

public:
	/*
	* 생성자 오버로딩 -> 생성자를 만들때 들어온 인자로 구분, 만약 클래스 내에서 생성자 선언을 하지 않았거나,
	* 인자가 없는 생성자를 만들었다면 기본생성자 호출
	* *** 가장 중요 ***
	* 멤버 변수가 객체이거나 const이거나 레퍼런스인 경우는 무조건 member initialization을 이용해서 초기화 해야됨
	* 
	*/
	ImmutableString(const char _s[]) : size(strlen(_s)), str(new char[strlen(_s) + 1]) { // char배열이 들어올 때 생성자
		for (int i = 0; i < this->size + 1; i++) 
			str[i] = _s[i];
	};
	ImmutableString() : size(0), str(new char[1]) { this->str[0] = '\0'; }; // 인자로 아무것도 들어오지 않을때 생성자
	ImmutableString(const ImmutableString& obj) : size(strlen(obj.str)), str(new char[strlen(obj.str) + 1]) { // 인자가 객체로 들어왔으니 복사 생성자
		for (int i = 0; i < strlen(obj.str)+1 ; i++) 
			this->str[i] = obj.str[i];
	};

	bool isEqual(const ImmutableString& target) const {
		for (int i = 0; i < this->size + 1; i++)
			if (this->str[i] != target.str[i])
				return false;
		return true;
	}

	void print() const {
		cout << this->str << endl;
	}

	size_t getLength() const { // size_t는 unsigned int
		size_t len_Count = strlen(str);
		
		return len_Count;
	}

	~ImmutableString() { delete[] str; };
};

int main() {
	ImmutableString strs[] = {
		ImmutableString("C"), ImmutableString(),
		ImmutableString("Java"), ImmutableString("CSharp")
	};
	const int arraySize = sizeof(strs) / sizeof(ImmutableString);
	
	
	// [2]: Java
	const ImmutableString target("Java");
	for (size_t i = 0; i < arraySize; i++) {
		const ImmutableString str(strs[i]);
		if (str.isEqual(target)) {
			cout << "[" << i << "]: "; str.print(); break;
		}
	}
	// C
	//
	// Java
	// CSharp
	for (const ImmutableString& str : strs) {
		str.print();
	}
	vector<ImmutableString> strVector{ strs, strs + arraySize };
	size_t totalLength{};
	std::for_each(strVector.cbegin(), strVector.cend(),
		[&totalLength](const ImmutableString& str) {
			totalLength += str.getLength();
		}
	);
	cout << totalLength << endl; // 11
	
}
