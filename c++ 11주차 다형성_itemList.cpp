#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Item {
	const string itemId;
	const string maker;
	int price;
	static int sequenceNum;
public:

	Item() = default;

	Item(const string& _maker, const int _price) : maker(_maker), itemId(_maker + "-" + to_string(++sequenceNum)) {
		setPrice(_price);
	}

	Item(const string& _maker, const int _price, const string& itemId) : maker(_maker), itemId(itemId), price(_price) {}

	virtual void print() const = 0;
	virtual Item* clone() const = 0;

	void setPrice(const int _price) { this->price = _price; }
	int getPrice() const { return this->price; }
	const string getMaker() const { return maker; }
	string getitemId() const { return itemId; }

	bool isSameId(const string& itemID) const {
		return itemId == itemID;
	}

};

int Item::sequenceNum = 0;

class CPU : public Item {
	const float speed;
public:
	CPU() = default;
	CPU(const CPU& cpu) : Item(cpu.getMaker(), cpu.getPrice(), cpu.getitemId()), speed(cpu.speed){};
	
	CPU& operator = (const CPU&) = default;

	CPU(const string& _maker, const int _price, const float _speed) : Item(_maker, _price), speed(_speed) {}

	void print() const override {
		cout << getMaker() << "\t" << getitemId() << "\t" << "$" << getPrice() << "\t" << speed << "MHz" << endl;
	}

	Item* clone() const override {
		return new CPU(*this);
	}
};

class Monitor : public Item {
	const int size;
public:
	Monitor() = default;
	Monitor(const string& _maker, const int _price, const int _size) : Item(_maker, _price), size(_size) {}
	Monitor(const Monitor& monitor) : Item(monitor.getMaker(), monitor.getPrice(), monitor.getitemId()), size(monitor.size) {}

	void print() const override {
		cout << getMaker() << "\t" << getitemId() << "\t" << "$" << getPrice() << "\t" << size  << "Inch" << endl;
	}
	Item* clone() const override {
		return new Monitor(*this);
	}
};
class ItemList {
	vector<Item*> items;

	void copyItems(const ItemList& itemlist) {
		for (const Item* item : itemlist.items) {
			items.push_back(item->clone());
		}
	}

	void deleteItems() {
		for (auto it = items.begin(); it != items.end(); ++it) {
			delete (*it);
		}
	}

public:
	ItemList() = default;

	ItemList(const ItemList& itemlist) {
		copyItems(itemlist);
	}

	ItemList& operator = (const ItemList& itemlist) {
		deleteItems();
		items.clear();
		copyItems(itemlist);

		return *this;
	}

	string addItem(const Item* item) {
		Item* newItem = item->clone();
		items.push_back(newItem);

		return newItem->getitemId();
	}

	Item* findItem (const string& itemID) const {
		for (Item* item : items) {
			if (item->isSameId(itemID))
				return item;
		}
		return nullptr;
	}
	void removeItem(const string& itemID) {
		for (auto it = items.begin(); it != items.end(); ++it) {
			if ((*it)->isSameId(itemID)) {
				delete (*it);
				items.erase(it);
				break;
			}
		}
	}

	void print() const {
		int totalPrice = 0;
		for (const Item* item : items) {
			item->print();
			totalPrice += item->getPrice();
		}
		cout << "Total price: " << totalPrice << endl;
	}

	~ItemList() { deleteItems(); }
};

ostream& operator << (ostream& os, const ItemList& list) {
	list.print();
	return os;
}

int main() {
	ItemList list1{};
	string intelCPU1Id, intelCPU2Id;
	{
		CPU cpu1("Intel", 200, 5.5F); // maker, price, speed
		CPU cpu2("Intel", 300, 7.8F);
		intelCPU1Id = list1.addItem(&cpu1);
		intelCPU2Id = list1.addItem(&cpu2);
		Monitor monitor1("LG", 1000, 40); // maker, price, size
		list1.addItem(&monitor1);
	}
	cout << "Section 1" << endl;
	cout << list1 << '\n';
	{
		cout << "Section 2" << endl;
		ItemList list2{ list1 };
		Item* cpu2 = list2.findItem(intelCPU2Id);
		cpu2->setPrice(250);
		cout << list2 << '\n';
		cout << "Section 3" << endl;
		list2.removeItem(intelCPU2Id);
		cout << list2 << '\n';
	}
	
	{
		ItemList list3;
		list3 = list1;
	}
	
	cout << "Section 4" << endl;
	CPU cpu3 = CPU("Apple", 170, 20.8F);
	list1.addItem(&cpu3);
	list1.removeItem(intelCPU1Id);
	cout << list1 << '\n';
	
}
