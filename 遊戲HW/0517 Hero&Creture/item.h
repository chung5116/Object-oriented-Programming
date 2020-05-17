#ifndef ITEM_H
#define ITEM_H

#include "allStruct.h"
#include"board.h"
#include"herocreature.h"

class Item{
private:

public:
	char icon = ' ';
	bool exist = true;
	Item(Position pos) { posItem.x = pos.x; posItem.y = pos.y; }
	Position posItem;
	char getIcon(){return icon;}
	Position getPos() { return posItem; }
	void setPosition(int x, int y) { this->posItem.x = x; this->posItem.y = y; }
	virtual void triggered(Hero& h) {};
	virtual void update() {};
};


#endif // !ITEM_H
