#include <iostream>
#include <vector>
#include <algorithm>

//여기서는 각 서브 클래스에서 메모리 할당을 안해서 서브클래스에서 메모리 회수도 한번 연습해볼 것

using namespace std;

constexpr float PI = 3.141592F;
enum class Color { BLACK, RED, BLUE, YELLOW };

class Point {
private:
	float x;
	float y;
public:
	Point() = default;
	Point(float _x, float _y) : x(_x), y(_y) {}
	Point(const Point&) = default;
	Point& operator = (const Point&) = default;

	float getX() const { return this->x; }
	float getY() const { return this->y; }
};

Point operator + (const Point& mine, const Point& other) {
	Point p1((mine.getX() + other.getX()), (mine.getY() + other.getY()));
	return p1;
}

ostream& operator << (ostream& os, const Point& other) {
	os << "(" << other.getX() << ", " << other.getY() << ")";
	return os;
}

class ClosedShape { // abstract class
	Color lineColor;

protected:
	ClosedShape(const ClosedShape&) = default;

public:
	ClosedShape(const Color color = Color::BLACK)
		: lineColor(color) {}

	Color getLineColor() const { return lineColor; }

	virtual ClosedShape* clone() const = 0;
	virtual void print() const = 0;
	virtual float getLength() const = 0;
	virtual float getArea() const = 0;

	// 필요한 함수 추가
};

class ClosedShapeList{
	vector<ClosedShape*> shapes;
	void deleteShape() {
		for (ClosedShape* const shape : shapes) {
			delete shape;
		}
	}

public:
	ClosedShapeList() = default;

	void addShape (const ClosedShape* const other) {
		ClosedShape* shape = other->clone();
		(this->shapes).push_back(shape);
	}

	void print() const{

		/* 
		for (const ClosedShape* const shape : shapes) {
			shape->print();
		}
		*/

		for_each(shapes.cbegin(), shapes.cend(),
			[](const ClosedShape* const shape) { shape->print(); });
	}
	float getTotalLength() {
		float total = 0;
		for_each(shapes.cbegin(), shapes.cend(),
			[&total](const ClosedShape* const shape) { total += shape->getLength(); }
		);
		return total;
	}
	float getTotalArea() const {
		float total = 0;
		for_each(shapes.cbegin(), shapes.cend(),
			[&total](const ClosedShape* const shape) {total += shape->getArea(); }
		);
		return total;
	}

	~ClosedShapeList() {
		deleteShape();
	}
};

string toString(const Color color) {
	string colorString;
	if (color == Color::BLACK)
		colorString = "BLACK";
	else if (color == Color::BLUE)
		colorString = "BLUE";
	else if (color == Color::RED)
		colorString = "RED";
	else
		colorString = "YELLOW";
	return colorString;
}

ostream& operator << (ostream& os, const Color& other) {
	return os << toString(other);
}

class Polygon : public ClosedShape {
private:
	vector<Point> points;
protected:
	void addPoint(const Point& p) { points.push_back(p); }
	const vector<Point>& getPoints() const { return points; }

public:
	Polygon() = default;
	Polygon() :ClosedShape(Color::BLACK) {}
	Polygon(Color color) : ClosedShape(color) {}
	float getLength() const {
		float len = 0;
		for (int i = 0; i < points.size(); ++i) {
			Point p1 = points[i];
			Point p2 = points[(i + 1) % points.size()];
			float dx = p1.getX() - p2.getX();
			float dy = p1.getY() - p2.getY();
			len += sqrt(dx * dx + dy * dy);
		}
		return len;
	}
	float getArea() const {
		float area = 0;
		for (int i = 0; i < points.size(); ++i) {
			Point p1 = points[i];
			Point p2 = points[(i + 1) % points.size()];
			area += p1.getX() * p2.getY() - p2.getX() * p1.getY();
		}
		return fabs(area) * 0.5F;
	}
};

class Rectangle : public Polygon {
public:
	Rectangle(Point p1, Point p2, Point p3, Point p4, Color color)
		: Polygon(color) {
		addPoint(p1);
		addPoint(p2);
		addPoint(p3);
		addPoint(p4);
	}

	Rectangle(Point p1, Point p2, Point p3, Point p4) : Polygon(Color::BLACK){
		addPoint(p1);
		addPoint(p2);
		addPoint(p3);
		addPoint(p4);
	}

	ClosedShape* clone() const override {
		ClosedShape* clone = new Rectangle(*this);
		return clone;
	}

	void print() const override {
		const vector<Point>& point = getPoints();
		cout << "Rectangle: " << getLineColor() << " ";
		for (const Point& p : point) {
			cout << p;
		}
		cout << endl;
	}
};

class Triangle : public Polygon {
public:
	Triangle() = default;
	Triangle(Point p1, Point p2, Point p3, Color color) : Polygon(color) {
		addPoint(p1);
		addPoint(p2);
		addPoint(p3);
	}

	Triangle(const Triangle&) = default;
	Triangle& operator = (const Triangle&) = default;

	ClosedShape* clone() const override {
		ClosedShape* const clone = new Triangle(*this);
		return clone;
	}
	void print() const override {
		vector<Point> point = getPoints();
		cout << "Triangle: " << getLineColor() << " ";
		for (const Point& p : point) {
			cout << p;
		}
		cout << endl;
	}
	
};

class Circle : public ClosedShape {
	Point p1;
	float radius;
public:
	Circle(const Point& other, const float _radius, const Color& c1) : p1(other.getX(), other.getY()), ClosedShape(c1) {
		radius = _radius;
	}
	Circle(const Circle&) = default;

	ClosedShape* clone() const override {
		ClosedShape* clone = new Circle(*this);
		return clone;
	}
	void print() const override {
		cout << "Circle: " << getLineColor() << " " << p1 << " " << radius << endl;
	}
	float getLength() const override {
		return radius * 2 * PI;
	}
	float getArea() const override {
		return radius * radius * PI;
	}
};

int main() {
	Point p1(0, 0), p2(0, 10), p3(20, 20), p4(20, 30);

	ClosedShape* const r1 = new Rectangle(p1, p2, p3, p4, Color::BLUE);
	ClosedShape* const r2 = new Rectangle(p1, p2, p3, p4); // default color: BLACK
	ClosedShape* const t = new Triangle(p1, p2, p3 + Point(10, 10), Color::YELLOW);
	ClosedShape* const c = new Circle(Point(1.0F, 1.0F), 10.0F, Color::RED);

	ClosedShapeList list{};
	list.addShape(r1);
	list.addShape(t);
	list.addShape(r2);
	list.addShape(c);

	delete r1; delete r2; delete t; delete c;


	list.print();
	cout << "Total length: " << list.getTotalLength() << endl;
	cout << "Total area: " << list.getTotalArea() << endl;
}
