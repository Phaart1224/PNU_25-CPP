#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

enum EmployeeLevel { sawon, daeri, gwajang, chajang, bujang };

class Employee {
	string name;
	const EmployeeLevel level;
public:
	Employee(const string& _name, const EmployeeLevel _level) : name(_name), level(_level) {}

	Employee(const Employee& _Employee) : name(_Employee.name), level(_Employee.level) {}

	friend ostream& operator << (ostream& os, const Employee& employee);

	const string& getName() const { return this->name; }
	const EmployeeLevel& getLevel() const { return this->level; }
};

ostream& operator << (ostream& os, const Employee& employee) {
	os << employee.level << "\t" << employee.name << endl;
	return os;
}

class Manager : public Employee {
	vector<Employee*> group;
	
	void deleteMember() {
		for (Employee* member : group)
			delete member;
	}
public:
	Manager(const string& _name, const EmployeeLevel _level) : Employee(_name, _level) {}

	void addEmployee(Employee* const employee) {
		Employee* e1 = new Employee((*employee));
		group.push_back(e1);
	}
	friend ostream& operator << (ostream& os, const Manager& manager);

	~Manager() {
		deleteMember();
	}
};

ostream& operator << (ostream& os, const Manager& manager) {
	os << manager.getLevel() << "\t" << manager.getName();
	cout << endl << "List of employees managed by me" << endl;
	for (auto it = manager.group.begin(); it != manager.group.end(); ++it) {
		os << (*it)->getLevel() << "\t" << (*it)->getName() << endl;
	}
	return os;
}

int main() {
	Manager m1("Tom", chajang);

	Employee* e1 = new Employee("hong", sawon);
	Employee* e2 = new Employee("kim", daeri);
	Employee* e3 = new Employee("cha", sawon);

	vector<Employee*> members{ e1, e2, e3 };
	for (Employee* const e : members) m1.addEmployee(e);

	for_each(members.cbegin(), members.cend(), [](const Employee* const member) { // for each는 첫째 인자부터 두번째 인자까지 세번째 인자(행동)를 각각 실행한다는 함수
		cout << *member;
		}
	);

	for (Employee* const e : members) delete e;

	cout << endl << "Imformation for manager" << endl;
	cout << m1;
}