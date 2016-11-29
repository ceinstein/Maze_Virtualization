#include <iostream>
#include "Point2D.h"
#include "Maze.h"

const char PERIMETER = '*';
const char FREE = ' ';
const char BEACON = 'B';
const char WALL = 'W';

//GRID IS DEFINED AS [ROW][COLUMN] DUE TO 2D ARRAY CREATION
//All return values will correct this issue

void Maze::initialize(int _rows, int _columns){
	rows = _rows;
	columns = _columns;
	
	allocateMemory();
	empty();
	generatePerimeter();
	generateWalls(Point2D(0,0), Point2D(columns, rows));
		generateBeacon();
}

void Maze::allocateMemory(){
	grid = (char**) malloc(rows * sizeof(long)); //Pointer to each row
	for(int i = 0; i < rows; i++){ //Memory for each row
		grid[i] = (char *) malloc(columns * sizeof(long));
	}
}

void Maze::empty(){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			grid[i][j] = FREE;
		}
	}
}

void Maze::generatePerimeter(){
	//Add top perimeter
	for(int i = 0; i < columns; i++){
			grid[0][i] = PERIMETER;
	}

	//Add left perimeter
	for(int i = 1; i < rows - 1; i++){
		grid[i][0] = PERIMETER;
	}

	//Add Right perimeter
	for(int i = 1; i < rows - 1; i++){
		grid[i][columns - 1] = PERIMETER;
	}

	//Add Right perimeter
	for(int i = 0; i < columns; i++){
		grid[rows - 1][i] = PERIMETER;
	}

}

void Maze::generateBeacon(){
	srand(time(NULL));
	int b_wall = rand() % 4;
	int rand_pos;
	switch(b_wall){
		case 0: //Top wall
			rand_pos = (rand() % (columns - 2)) + 1;
			grid[0][rand_pos] = BEACON;
			beacon.set(0, rand_pos);
			if(grid[1][rand_pos] == WALL){
				grid[1][rand_pos] = FREE;
			}
			break;
		case 1: //Left wall
			rand_pos = (rand() % (rows - 2)) + 1;
			grid[rand_pos][0] = BEACON;
			beacon.set(rand_pos, 0);
			if(grid[rand_pos][1] == WALL){
				grid[rand_pos][1] = FREE;
			}
			break;
		case 2: //Right wall
			rand_pos = (rand() % (rows - 2)) + 1;
			grid[rand_pos][columns - 1] = BEACON;
			beacon.set(rand_pos, columns - 1);
			if(grid[rand_pos][columns - 2] == WALL){
				grid[rand_pos][columns - 2] = FREE;
			}
			break;
		case 3: //Bottom wall
			rand_pos = (rand() % (columns - 2)) + 1;
			grid[rows - 1][rand_pos] = BEACON;
			beacon.set(rows - 1, rand_pos);
			if(grid[rows - 2][rand_pos] == WALL){
				grid[rows - 2][rand_pos] = FREE;
			}

			break;
	}
}

void Maze::generateWalls(Point2D start, Point2D end){
	srand(time(NULL));
	int x_diff = (end.getX() - 1) - (start.getX() + 1);
	int y_diff = (end.getY() - 1) - (start.getY() + 1);
	int rand_row, rand_col;

	if(x_diff > 6 && y_diff > 6){
		int created = 0;
		while(created == 0){
			rand_col = start.getX() + (rand() % (x_diff - 6) + 3);
			if(grid[start.getY()][rand_col] != FREE){
				created = 1;
			}

		}
		created = 0;
		while(created == 0){
			rand_row = start.getY() + (rand() % (y_diff - 6) + 3);
			if(grid[rand_row][start.getX()] != FREE){
				created = 1;

			}

		}
		

		//Makes Horizontal wall
		for(int i = start.getX() + 1; i <= start.getX() + x_diff; i++){
			grid[rand_row][i] = WALL;
		}

		//Makes left wall passes
		int count = 0;
		int num_pass = 0;
		num_pass = 1 + rand() % 2;
		while(count != num_pass){
			int rand_pass_left = (start.getX() + 1) + rand() % (rand_col - (start.getX() + 1));
			if(grid[rand_row][rand_pass_left] == WALL){
				grid[rand_row][rand_pass_left] = FREE;
				count++;
			}
		}

		//Makes right wall passes
		count = 0;
		num_pass = 1 + rand() % 2;
		while(count != num_pass){
			int rand_pass_right = (rand_col + 1) + rand() % ((end.getX() - 1) - (rand_col + 1));
			if(grid[rand_row][rand_pass_right] == WALL){
				grid[rand_row][rand_pass_right] = FREE;
				count++;
			}
		}

		//Makes vertical wall
		for(int i = start.getY() + 1; i <= start.getY() + y_diff; i++){
			grid[i][rand_col] = WALL;
		}

		//Makes top wall passes
		count = 0;
		num_pass = 1 + rand() % 2;
		while(count != num_pass){
			int rand_pass_top = (start.getY() + 1) + rand() % (rand_row - (start.getY() + 1));
			if(grid[rand_pass_top][rand_col] == WALL){
				grid[rand_pass_top][rand_col] = FREE;
				count++;
			}
		}

		//Makes bottom wall passes
		count = 0;
		num_pass = 1 + rand() % 2;
		while(count != num_pass){
			int rand_pass_bottom = (rand_row + 1) + rand() % ((end.getY() - 1) - (rand_row + 1));
			if(grid[rand_pass_bottom][rand_col] == WALL){
				grid[rand_pass_bottom][rand_col] = FREE;
				count++;
			}
		}

		generateWalls(start, Point2D(rand_col + 1, rand_row + 1)); //Top left
		generateWalls(Point2D(rand_col, start.getY()), Point2D(end.getX(), rand_row + 1)); //Top Right
		generateWalls(Point2D(start.getX(), rand_row), Point2D(rand_col + 1, end.getY())); //Bottom Left
		generateWalls(Point2D(rand_col, rand_row), end); //Bottom Right
	}

}


void Maze::print(){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			printf("%c ", grid[i][j]);
		}
		printf("\n");
	}
}

int Maze::getRows(){
	return rows;
}

int Maze::getColumns(){
	return columns;
}

char Maze::getTile(int column, int row){
	return grid[row][column];
}

char Maze::freeChar(){
	return FREE;
}

char Maze::beaconChar(){
	return BEACON;
}




