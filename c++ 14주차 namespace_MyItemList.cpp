#include <iostream>

using namespace std;

namespace shape {
	class Shape {
	public:
		virtual void draw() const = 0;
		virtual bool isEqual(const Shape* const) const = 0;
		virtual Shape* clone() const = 0;
		virtual ~Shape() = default;
	};

	class Rectangle : public Shape {
		int x1, y1, x2, y2;
	public:
		Rectangle() = default;
		Rectangle(const int x1, const int y1, const int x2, const int y2) :x1(x1), y1(y1), x2(x2), y2(y2) {}
		
		// rule of three (깊은 복사를 요하지 않음)
		Rectangle(const Rectangle&) = default;
		Rectangle& operator =(const Rectangle&) = default;
		~Rectangle() = default;

		void draw() const override {
			cout << *this;
		}

		bool isEqual(const Shape* const shape) const override {
			const Rectangle* const rectangle = dynamic_cast<const Rectangle*>(shape);
			
			return ((rectangle->x1 == this->x1) && (rectangle->x2 == this->x2) && (rectangle->y1 == this->y1) && (rectangle->y2 == this->y2));
		}

		Shape* clone() const override {
			return new Rectangle(*this);
		}
		friend ostream& operator << (ostream& os, const Rectangle& rectangle);
	};
	ostream& operator << (ostream& os, const Rectangle& rectangle) {
		os << "Rectangle: ";
		os << "(" << rectangle.x1 << ", " << rectangle.y1 << ")";
		os << "(" << rectangle.x2 << ", " << rectangle.y2 << ")" << endl;
		return os;
	}

	class Circle : public Shape {
		int x, y;
		int radius;
	public:
		Circle() = default;
		Circle(const int x, const int y, const int radius) : x(x), y(y), radius(radius) {}
		
		// rule of three (깊은 복사를 요하지 않음)
		Circle(const Circle&) = default;
		Circle& operator = (const Circle&) = default;
		~Circle() = default;
		
		void draw() const override {
			cout << *this;
		}
		bool isEqual(const Shape* const shape) const override {
			const Circle* const circle = dynamic_cast<const Circle*>(shape);

			return ((circle->x == this->x) && (circle->y == this->y) && (circle->radius == this->radius));
		}
		Shape* clone() const override {
			return new Circle(*this);
		}
		
		friend ostream& operator <<(ostream& os, const Circle& circle);
	};
	ostream& operator << (ostream& os, const Circle& circle) {
		os << "Circle: " << "(" << circle.x << ", " << circle.y << "), ";
		os << circle.radius << endl;
		return os;
	}
}

namespace mystl {
	template <typename T, int size>
	class MyArrayList {
		T* data[size];

		void initList(MyArrayList& list) {
			for (int i = 0; i < size; i++) {
				list.data[i] = nullptr;
			}
		}
		void deleteArrayElement() const {
			for (int i = 0; i < size; i++) {
				if (data[i] == nullptr)
					continue;
				else
					delete data[i];
			}
		}
	public:
		MyArrayList() {
			initList(*this);
		}

		MyArrayList(const MyArrayList&) = delete;
		MyArrayList& operator = (const MyArrayList&) = delete;

		// 메인 함수 내에서 MyArrayList의 복사를 요구하고 있지 않기 때문에
		// 명시적으로 복사생성자와 대입연산자를 delete 처리 (얕은 복사 차단)

		bool addElement(shape::Shape* shape) {
			for (int i = 0; i < size; i++) {
				if (data[i] == nullptr) {
					data[i] = shape->clone();
					return true;
				}
			}
			return false; // 배열이 가득 차 nullptr이 존재 하지 않을때
		}

		bool removeElement(shape::Shape* shape) {
			for (int i = 0; i < size; i++) {
				if (data[i] != nullptr && data[i]->isEqual(shape)) {
					delete data[i];
					data[i] = nullptr;
					return true;
				}
			}
			return false; // 똑같은 shape가 존재 하지 않을때 
		}
		T* operator [] (int i) const {
			return this->data[i];
		}

		int getSize() const {
			return size;
		}

		~MyArrayList() { deleteArrayElement(); }
	};
}

int main() {
	shape::Shape* r1 = new shape::Rectangle(0, 0, 10, 10);
	shape::Shape* r2 = new shape::Rectangle(0, 0, 20, 20);

	shape::Shape* c1 = new shape::Circle(0, 0, 10);
	shape::Shape* c2 = new shape::Circle(10, 10, 20);

	mystl::MyArrayList<shape::Shape, 5> list{};
	cout << boolalpha;
	cout << list.addElement(r1) << endl;
	cout << list.addElement(c1) << endl;
	delete c1;

	for (int i = 0; i < list.getSize(); i++) {
		shape::Shape* s = list[i];
		if (s == nullptr) continue;
		s->draw();
	}
	cout << list.removeElement(r1) << endl;
	shape::Circle temp(0, 0, 5);
	cout << list.removeElement(&temp) << endl;
	cout << list.addElement(c2) << endl;
	cout << list.addElement(r2) << endl;
	for (int i = 0; i < list.getSize(); i++) {
		shape::Shape* s = list[i];
		if (s == nullptr) continue;
		s->draw();
	}
}