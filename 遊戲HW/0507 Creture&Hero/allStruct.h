// Name: ±i¥Ã©Ó	
// Date: 2020.03.31
// Last Update: 2020.03.27
// Problem statement: Hero & Creature
#ifndef ALLSTRUCT_H
#define ALLSTRUCT_H
#include<map>

struct Position {

	int x = 0; // X, y Coordinate
	int y = 0;
};

struct cDirection{

	int x;
	int y;
};

const enum ValidInput
{
	w = 0,		//up
	a = 1,		//left
	s = 2,		//down
	d = 3,		//right
	k = 4,		//attack
	j = 5,		//add creature
	l = 6,		//add trigger
	space = 7,	//space
};

const enum CretureType {
	B = 0,     //bat
	W = 1,	//wolf
	G = 2,		//ghost
	C = 3,		//Crocodilia
	T = 4,		//tiger
	L = 5	//lion
};

/*map<int, char>gCreatureMap = {
	{0,'B'},
	{1,'W'},
	{2,'G'},
	{3,'C'},
	{4,'T'},
	{5,'L'}
};*/



#endif // !ALLSTRUCT_H