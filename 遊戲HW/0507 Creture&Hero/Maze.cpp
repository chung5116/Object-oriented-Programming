#include <iostream>
#include <vector>
#include <time.h>
#include <stack>
#include <ctime>
#include <windows.h>
#include"stdafx.h"

int gSIZE = 15;
int gHPOSX = 0;
int gHPOSY = 0;
using namespace std;
struct Cell
{
	bool visited;
	bool top_wall;
	bool bot_wall;
	bool left_wall;
	bool right_wall;
	char display;
};


// FUNCTION DECLARATIONS
void Initialize(vector<vector<Cell>>& Level);
void ClearScreen();
void Redraw(vector<vector<Cell>>& Level);
void GenerateMaze(vector<vector<Cell>>& Level, int& posX, int& posY, int& goalX, int& goalY);
//void SaveMaze(vector<vector<Cell>>&Level);

// MAIN
vector<vector<char>> maze() {
	int size = 0;
	while (true) {
		cout << "Enter this size. 15~25\n";
		cin >> size;
		if (size >= 15 && size <= 25) {
			if (size % 2 == 0)size++;
			gSIZE = size;
			break;
		}
	}
	vector<vector<Cell>>Level;
	vector<vector<char>>res;
	Level.resize(gSIZE);
	res.resize(gSIZE);
	for (int i = 0; i < gSIZE; i++) {
		Cell c = Cell();
		Level[i].resize(gSIZE, c);
		res[i].resize(gSIZE, '*');
	}
	int posX = 0;
	int posY = 0;
	int goalX = 0;
	int goalY = 0;
	bool game_over = false;


	system("cls");
	Initialize(Level);
	Redraw(Level);
	GenerateMaze(Level, posX, posY, goalX, goalY);
	//SaveMaze(Level);

	char input;
	for (int i = 0; i < gSIZE; i++) {
		for (int j = 0; j < gSIZE; j++) {
			res[i][j] = Level[i][j].display;
		}
	}

	return res;
}

// INITIALIZE MAZE
void Initialize(vector<vector<Cell>>& Level) {
	for (int i = 0; i < gSIZE; i++) {
		for (int j = 0; j < gSIZE; j++) {
			Level[i][j].display = '*';
			Level[i][j].visited = false;
			Level[i][j].top_wall = true;
			Level[i][j].bot_wall = true;
			Level[i][j].left_wall = true;
			Level[i][j].right_wall = true;
		}
	}
	for (int i = 1; i < gSIZE - 1; i++) {
		for (int j = 1; j < gSIZE - 1; j++) {
			// Border Cells have fewer accessible walls
			Level[1][j].top_wall = false;
			Level[gSIZE - 2][j].bot_wall = false;
			Level[i][1].left_wall = false;
			Level[i][gSIZE - 2].right_wall = false;
		}
	}
}

// CLEAR SCREEN
void ClearScreen()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

// REDRAW MAZE
void Redraw(vector<vector<Cell>>& Level) {
	for (int i = 0; i < gSIZE; i++) {
		cout << endl;
		for (int j = 0; j < gSIZE; j++)
			cout << " " << Level[i][j].display;
	}
}

// GENERATE MAZE
void GenerateMaze(vector<vector<Cell>>& Level, int& posX, int& posY, int& goalX, int& goalY) {
	srand((unsigned)time(NULL));                                                                            // Pick random start cell
	int random = 0;
	int randomX = ((2 * rand()) + 1) % (gSIZE - 1);                                          // Generate a random odd number between 1 and gSIZE
	int randomY = ((2 * rand()) + 1) % (gSIZE - 1);                                          // Generate a random odd number between 1 and gSIZE
	posX = randomX;                                                                 // Save player's initial X position
	posY = randomY;                                                                 // Save player's initial Y position
	int visitedCells = 1;
	int totalCells = ((gSIZE - 1) / 2) * ((gSIZE - 1) / 2);
	int percent = 0;
	stack<int> back_trackX, back_trackY;                                            // Stack is used to trace the reverse path

	//Level[randomY][randomX].display = 'H';                                          // Set S as the start cell
	gHPOSX = randomY;
	gHPOSY = randomX;
	Level[randomY][randomX].visited = true;                                         // Set start cell as visited;

	while (visitedCells < totalCells)
	{
		if ((randomY - 2 > 1 && (Level[randomY - 2][randomX].visited == false) && (Level[randomY][randomX].top_wall == true && Level[randomY - 2][randomX].bot_wall == true)) ||
			(randomY + 2 < gSIZE && (Level[randomY + 2][randomX].visited == false) && (Level[randomY][randomX].bot_wall == true && Level[randomY + 2][randomX].top_wall == true)) ||
			(randomX - 2 > 0 && (Level[randomY][randomX - 2].visited == false) && (Level[randomY][randomX].left_wall == true && Level[randomY][randomX - 2].right_wall == true)) ||
			(randomX + 2 < gSIZE && (Level[randomY][randomX + 2].visited == false) && (Level[randomY][randomX].right_wall == true && Level[randomY][randomX + 2].left_wall == true)))
		{
			random = (rand() % 4) + 1;              // Pick a random wall 1-4 to knock down

			 // GO UP
			if ((random == 1) && (randomY > 1)) {
				if (Level[randomY - 2][randomX].visited == false) {        // If not visited
					Level[randomY - 1][randomX].display = ' ';        // Delete display
					Level[randomY - 1][randomX].visited = true;       // Mark cell as visited
					Level[randomY][randomX].top_wall = false;       // Knock down wall

					back_trackX.push(randomX);                      // Push X for back track
					back_trackY.push(randomY);                      // Push Y for back track

					randomY -= 2;                                   // Move to next cell
					Level[randomY][randomX].visited = true;         // Mark cell moved to as visited
					Level[randomY][randomX].display = ' ';          // Update path
					Level[randomY][randomX].bot_wall = false;       // Knock down wall
					visitedCells++;                                 // Increase visitedCells counter
				}
				else
					continue;
			}

			// GO DOWN
			else if ((random == 2) && (randomY < gSIZE - 2)) {
				if (Level[randomY + 2][randomX].visited == false) {        // If not visited
					Level[randomY + 1][randomX].display = ' ';        // Delete display
					Level[randomY + 1][randomX].visited = true;       // Mark cell as visited
					Level[randomY][randomX].bot_wall = false;       // Knock down wall

					back_trackX.push(randomX);                      // Push X for back track
					back_trackY.push(randomY);                      // Push Y for back track

					randomY += 2;                                   // Move to next cell
					Level[randomY][randomX].visited = true;         // Mark cell moved to as visited
					Level[randomY][randomX].display = ' ';          // Update path
					Level[randomY][randomX].top_wall = false;       // Knock down wall
					visitedCells++;                                 // Increase visitedCells counter
				}
				else
					continue;
			}

			// GO LEFT
			else if ((random == 3) && (randomX > 1)) {
				if (Level[randomY][randomX - 2].visited == false) {        // If not visited
					Level[randomY][randomX - 1].display = ' ';        // Delete display
					Level[randomY][randomX - 1].visited = true;       // Mark cell as visited
					Level[randomY][randomX].left_wall = false;      // Knock down wall

					back_trackX.push(randomX);                      // Push X for back track
					back_trackY.push(randomY);                      // Push Y for back track

					randomX -= 2;                                   // Move to next cell
					Level[randomY][randomX].visited = true;         // Mark cell moved to as visited
					Level[randomY][randomX].display = ' ';          // Update path
					Level[randomY][randomX].right_wall = false;     // Knock down wall
					visitedCells++;                                 // Increase visitedCells counter
				}
				else
					continue;
			}

			// GO RIGHT
			else if ((random == 4) && (randomX < gSIZE - 2)) {
				if (Level[randomY][randomX + 2].visited == false) {        // If not visited
					Level[randomY][randomX + 1].display = ' ';        // Delete display
					Level[randomY][randomX + 1].visited = true;       // Mark cell as visited
					Level[randomY][randomX].right_wall = false;     // Knock down wall

					back_trackX.push(randomX);                      // Push X for back track
					back_trackY.push(randomY);                      // Push Y for back track

					randomX += 2;                                   // Move to next cell
					Level[randomY][randomX].visited = true;         // Mark cell moved to as visited
					Level[randomY][randomX].display = ' ';          // Update path
					Level[randomY][randomX].left_wall = false;      // Knock down wall
					visitedCells++;                                 // Increase visitedCells counter
				}
				else
					continue;
			}

			percent = (visitedCells * 100 / totalCells * 100) / 100;                // Progress in percentage
			cout << endl << "       Generating a Random Maze... " << percent << "%" << endl;
		}
		else {
			if (!back_trackX.empty()) {
				randomX = back_trackX.top();
				back_trackX.pop();
			}
			if (!back_trackY.empty()) {
				randomY = back_trackY.top();
				back_trackY.pop();
			}
		}

		ClearScreen();
		Redraw(Level);
	}

	goalX = randomX;
	goalY = randomY;
	Level[goalY][goalX].display = '@';
	system("cls");
	ClearScreen();
	Redraw(Level);
	cout << endl << "\a\t   Complete!" << endl;
}