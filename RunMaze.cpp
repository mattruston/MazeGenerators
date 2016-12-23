#include <iostream>
#include <vector>

#include "PathMaker.h"

using namespace std;

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

	vector<vector<int> > maze(5, vector<int>(5, ALLWALLS));

	PathMaker p(&maze);

	print(maze);

	bool finished = false;

	while (finished == false) {
		finished = p.act();
		print(maze);
	}

	return 0;
}