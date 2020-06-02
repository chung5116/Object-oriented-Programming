#include"otherItems.h"
using namespace std;


Door::Door(Position pos) :Item(pos) {
	icon = '@';
}

void Door::triggered(Hero& h) {
	Position posH = h.getPos();
	if (posH.x == posItem.x) {
		if (abs(posH.y - posItem.y) <= 1)
			update();
	}
	else if (posH.y == posItem.y) {
		if (abs(posH.x - posItem.x) <= 1)
			update();
	}
}

void Door::update() {
	cout << "You WIN !\n";
	system("pause");
	exit(1);
}


/*---------------------Potion---------------*/
Potion::Potion(Position pos) : Item(pos) {
	icon = 'P';
}
void Potion::triggered(Hero& h) {
	Position pos = h.getPos();
	if (pos.x == posItem.x && pos.y == posItem.y) {
		h.hp += 10;
		update();
	}
}
void Potion::update() {
	exist = false;
}


/*---------------------Weapon---------------*/
Weapon::Weapon(Position pos) : Item(pos) {
	icon = 'W';
}
void Weapon::triggered(Hero& h) {
	Position pos = h.getPos();
	if (pos.x == posItem.x && pos.y == posItem.y) {
		h.damage++;
		this->update();
	}
}
void Weapon::update() {
	exist = false;
}