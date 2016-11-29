#ifndef MAZEGENERATOR
#define MAZEGENERATOR

#include "Point2D.h"

class Maze{

	char** grid;
	int rows;
	int columns;
	Point2D beacon;
	
	public:
		void initialize(int _rows, int _columns);
		void print();
		int getRows();
		int getColumns();
		char getTile(int column, int row);
		char freeChar();
		char beaconChar();

	private:
		void allocateMemory();
		void empty();
		void generatePerimeter();
		void generateBeacon();
		void generateWalls(Point2D start, Point2D end);

};

#endif