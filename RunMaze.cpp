#include <iostream>
#include <vector>
#include <sstream>

#include "PathMaker.h"

#define WALLICON "#"
#define SPACEICON " "

using namespace std;

void draw(const Maze& maze) {
	for(int col = 0; col < maze.size(); ++col) {
		ostringstream middlerow;
		ostringstream bottomrow;

		for(int row = 0; row < maze[0].size(); ++row) {
			int walls = maze[col][row];
			bool lastRow = (col == (maze.size() - 1));

			cout << WALLICON;
			if (walls & TOPWALL) {
				cout << WALLICON;
			} else {
				cout << SPACEICON;
			}

			if (walls & LEFTWALL) {
				middlerow << WALLICON;
			} else {
				middlerow << SPACEICON;
			}
			middlerow << SPACEICON;

			if (lastRow) {
				bottomrow << WALLICON;
				if (walls & BOTTOMWALL) {
					bottomrow << WALLICON;
				} else {
					bottomrow << SPACEICON;
				}
			}

			if (row == (maze[0].size() - 1)) {
				cout << WALLICON;
				if (walls & RIGHTWALL) {
					middlerow << WALLICON;
				} else {
					middlerow << SPACEICON;
				}

				if (lastRow) {
					bottomrow << WALLICON;
				}
			}
		}

		cout << endl << middlerow.str() << endl;

		if (col == (maze.size() - 1))
			cout << bottomrow.str() << endl;
	}
}

void print(const Maze& maze) {
	for(int col = 0; col < maze.size(); ++col) {
		for(int row = 0; row < maze[0].size(); ++row) {
			cout << maze[col][row] << "\t";
		}
		cout << endl;
	}

	cout << endl << endl;
}

int main() {
	srand (time(NULL));

	//ROWS x COL
	Maze maze(30, vector<int>(50, ALLWALLS));
	PathMaker p(&maze);

	bool finished = false;

	while (finished == false) {
		finished = p.act();
	}

	draw(maze);

	return 0;
}