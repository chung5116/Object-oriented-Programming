#ifndef OTHERITEMS_H
#define OTHERITEMS_H

#include"item.h"


class Trigger :public Item {
private:

public:
	int static numofT;   //how many trigger in the board
	int boardHeight = 0;
	Trigger(Board& bd, Position pos);
	//Trigger(Board& bd,char icon);
	//Position getPos(void) { return this->posItem; }
	//char getIcon(void) { return this->icon; }
	Position generateRandomXY(Board& bd);
	void triggered(Hero& h)override;
	void update()override;
};

/* ------------Door----------*/
class Door:public Item{
private:

public:
	Door(Position pos);
	virtual void triggered(Hero& h)override;
	virtual void update()override;
};


/* ------------Potion----------*/
class Potion:public Item{
private:
public:
	Potion(Position pos);
	virtual void triggered(Hero& h)override;
	virtual void update()override;
};


/* ------------Weapon----------*/
class Weapon:public Item{
private:
public:
	Weapon(Position pos);
	virtual void triggered(Hero& h)override;
	virtual void update()override;
};

#endif // !OTHERITEMS_H
