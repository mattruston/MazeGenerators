#include <iostream>
#include <vector>
#include <stack>
#include <stdlib.h> //rand

using namespace std;

#define TOPWALL (1 << 3)
#define RIGHTWALL (1 << 2)
#define LEFTWALL (1 << 1)
#define BOTTOMWALL 1
#define ALLWALLS 15

typedef vector<vector<int> > Maze;

enum Direction {
	UP, DOWN, LEFT, RIGHT
};

struct Point {
	int row;
	int column;

	Point(int x, int y) {
		row = y;
		column = x;
	}
};

class PathMaker {
	private:
		stack<Point> _points;
		Maze* _maze;
		Point _currentPoint;

	public:
		PathMaker(Maze* maze, Point start = Point(0, 0)) : _currentPoint(start) {
			_maze = maze;
			_points.push(start);
		}

		//returns true if it has reached its end
		bool act() {
			if (_points.size() == 0)
				return true;

			Maze& maze = *_maze;

			vector<Direction> options = getOptions(_currentPoint);

			if (options.size() == 0) {
				//Pop and step back one (if there are no more points to pop return false)
				_points.pop();

				if (_points.size() == 0) {
					return true;
				}


				_currentPoint = _points.top();
				return false;
			}

			Direction option = options[rand() % options.size()];

			switch (option) {
				case UP:
					maze[_currentPoint.column][_currentPoint.row] ^= TOPWALL;
					_currentPoint = Point(_currentPoint.column - 1, _currentPoint.row);
					maze[_currentPoint.column][_currentPoint.row] ^= BOTTOMWALL;
					// cout << "UP" << endl;
					break;
				case LEFT:
					maze[_currentPoint.column][_currentPoint.row] ^= LEFTWALL;
					_currentPoint = Point(_currentPoint.column, _currentPoint.row - 1);
					maze[_currentPoint.column][_currentPoint.row] ^= RIGHTWALL;
					// cout << "LEFT" << endl;
					break;
				case RIGHT:
					maze[_currentPoint.column][_currentPoint.row] ^= RIGHTWALL;
					_currentPoint = Point(_currentPoint.column, _currentPoint.row + 1);
					maze[_currentPoint.column][_currentPoint.row] ^= LEFTWALL;
					// cout << "RIGHT" << endl;
					break;
				case DOWN:
					maze[_currentPoint.column][_currentPoint.row] ^= BOTTOMWALL;
					_currentPoint = Point(_currentPoint.column + 1, _currentPoint.row);
					maze[_currentPoint.column][_currentPoint.row] ^= TOPWALL;
					// cout << "DOWN" << endl;
					break;
			}

			_points.push(_currentPoint);

			return false;
		}

		vector<Direction> getOptions(const Point& point) {
			Maze& maze = *_maze;
			vector<Direction> options;

			if (point.column > 0 && maze[(point.column - 1)][point.row] == ALLWALLS) {
				options.push_back(UP);
			}
			if (point.row > 0 && maze[point.column][point.row - 1] == ALLWALLS) {
				options.push_back(LEFT);
			}
			if ((point.row < maze[point.column].size() - 1) && maze[point.column][point.row + 1] == ALLWALLS) {
				options.push_back(RIGHT);
			}
			if ((point.column < maze.size() - 1) && maze[point.column + 1][point.row] == ALLWALLS) {
				options.push_back(DOWN);
			}

			return options;
		}

		int currentOptionCount() {
			return getOptions(_currentPoint).size();
		}

		Point currentPoint() {
			return _currentPoint;
		}

		bool isFinished() {
			if (_points.size() == 0)
				return true;
			return false;
		}
};