/**********
 * Author: Craig Einstein
 * 
 * File: Point2D.h
 *
 * Description: Header file for Point2D
 *		Point2D stores a 2D point
 *		Contains access and functional methods for 2D points
 *
 **********/
#ifndef POINT2D
#define POINT2D

class Point2D{
	int x;
	int y;

	public:
		Point2D ();
		Point2D (int _x, int _y);
		void set(int, int);
		int getX();
		int getY();

};

#endif