#include <iostream>
#include <functional>
#include <exception>

using namespace std;

template <typename T>
class StackException : public runtime_error {
	const T value;
public:
	StackException(const string& msg, const T& value = T{})
		: runtime_error(msg), value(value) {}
	T getValue() const { return value; }
};

template <typename T>
class Stack {
	int size;
	int top;
	T* items;

	pair<function<bool(const T&)>, string> itemValidCondition;

	void deleteStack() {
		delete[] items;
	}

	void copyStack(const Stack& stack) {
		size = stack.size;
		top = stack.top;
		items = new T[size];

		for (int i = 0; i < top; i++) {
			items[i] = stack.items[i];
		}
	}
	// move 연산을 할 때 필요
	void moveFrom(Stack& other) {
		size = other.size;
		top = other.top;
		items = other.items;

		other.size = 0;
		other.top = 0;
		other.items = nullptr;
	}
public:
	Stack() : size(0), top(0) {
		items = nullptr;
	}
	Stack(const int _size) : top(0), size(_size) {
		items = new T[size]; // T에 대해서 기본 생성자를 size만큼 할당하는거임. 단순히 메모리를 할당받는게 아니라서 오버헤드가 꽤 큼.
	}						 // 이를 해결하는 방법인 uninitialized_copy라는 개념이 있는데 정답 코드 참고 (꽤 복잡함)
	Stack(const Stack& stack) {
		copyStack(stack);
	}
	// 참고로 move는 인자로 들어온 복사본을 더 이상 사용 안할때 빠르게 주소값으로 옮겨서 오버헤드를 줄임
	Stack(Stack& other) {
		size = other.size; 
		top = other.top;
		items = other.items; // 한번 한번 대입 연산으로 옮기는것 보다 주소값 한번 옮김으로 오버헤드를 줄일 수 있음.
		
		other.size = 0; // 그 후 이 복사본은 다시 사용하지 않을거니 전부 초기화
		other.top = 0;  // 절대 move 연산을 한 후는 push / pop과 같은 다시 사용하는 연산을 하면 안 됨!
		other.items = nullptr;
	}

	
	Stack& operator = (const Stack& stack) {
		if (&stack == this)
			return *this;

		deleteStack();
		copyStack(stack);

		return *this;
	}

	bool isEmpty() const {
		return top == 0;
	}
	bool isFull() const {
		return top == size;
	}

	void push(const T& item) {
		if (isFull()) {
			throw StackException<T>("Stack is Full!", item);
		}

		if (!itemValidCondition.first(item)) {
			throw invalid_argument(itemValidCondition.second);
		}

		items[top] = item;
		top++;
	}
	T& pop(void) {
		if (isEmpty()) {
			throw(StackException<T>("Stack is Empty!"));
		}
		top--;
		return items[top];
	}

	~Stack() { deleteStack(); }

	void setItemValidCondition(const function<bool(const T&)> function, string errMsg) {
		// 매번 달라지는 스택의 조건을 미리 설정하여서 더 reusable하게 만듬
		// 여기서 인자가 const T&가 되야됨. char / int처럼 가변형이기 때문
		// itemValidCondition = make_pair(function, errMsg);
		itemValidCondition.first = function;
		itemValidCondition.second = errMsg;
	}

	friend ostream& operator << (ostream& os, const Stack<T>& stack) {
		for (int i = 0; i < stack.top; i++)
			os << stack.items[i];
		os << endl;
		return os;
	}
};


int main() {
	Stack<char> alphabetStack(3);
	alphabetStack.setItemValidCondition([](const char c) { return isalpha(c); }, "Only alphabet allowed!");
	try {
		alphabetStack.pop();
	}
	catch (const StackException<char>& e) { cerr << e.what() << endl; }
	try {
		alphabetStack.push('A');
		alphabetStack.push('5');
	}
	catch (const invalid_argument& e) { cerr << e.what() << endl; }
	try {
		alphabetStack.push('B');
		alphabetStack.push('C');
		alphabetStack.push('D');
	}
	catch (const StackException<char>& e) {
		cerr << e.what() << endl;
		cerr << "Cannot push: " << e.getValue() << endl;
	}
	cout << alphabetStack;

	Stack<int> positiveNumbers(3);
	// function<반환값(인자)> 변수명 = [](const int) { return item > 0} (이 람다함수는 인자가 const int고 반환값이 bool값이니 아래처럼 선언
	function<bool(const int)> condition = [](const int item) { return item > 0; };
	positiveNumbers.setItemValidCondition(condition, "Only positive number allowed!");

	try {
		positiveNumbers.push(100);
		positiveNumbers.push(-10);
		positiveNumbers.push(200);
	}
	catch (const invalid_argument& e) {
		cerr << e.what() << endl;
	}
	catch (...) {
		
	}
}
