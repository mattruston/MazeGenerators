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

void runDFSMaze() {
	srand (time(NULL));

	//ROWS x COL
	Maze maze(15, vector<int>(15, ALLWALLS));
	PathMaker p(&maze);

	bool finished = false;

	while (finished == false) {
		finished = p.act();
	}

	draw(maze);
}

void runBFSMaze() {
	srand (time(NULL));

	//ROWS x COL
	Maze maze(45, vector<int>(80, ALLWALLS));

	vector<PathMaker> makers;
	PathMaker p(&maze);

	makers.push_back(p);

	while (makers.size() > 0) {
		vector<PathMaker> newMakers;

		//Loop through current makers and create new branches
		for (int x = 0; x < makers.size(); ++x) {
			PathMaker& currentMaker = makers[x];

			//If there is more than one path, put a new maker at that point
			if (currentMaker.currentOptionCount() > 1) {
				int additionalBranches = currentMaker.currentOptionCount() - 1;
				for (int c = 0; c < additionalBranches; ++c) {
					PathMaker maker(&maze, currentMaker.currentPoint());
					newMakers.push_back(maker);
				}
			}
		}

		//add new makers
		makers.insert(makers.end(), newMakers.begin(), newMakers.end());

		//loop through and act all
		vector<int> toDelete;
		for (int x = 0; x < makers.size(); ++x) {
			PathMaker& currentMaker = makers[x];

			bool finished = currentMaker.act();
			if (finished == true) {
				toDelete.push_back(x);
			}
		}

		for (int x = toDelete.size() - 1; x >= 0; --x) {
			int d = toDelete[x];
			makers.erase(makers.begin() + d);
		}
	}

	draw(maze);
}

int main(int argc, char** args) {
	
	runBFSMaze();

	return 0;
}
