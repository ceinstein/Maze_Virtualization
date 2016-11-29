/**********
 * Author: Craig Einstein
 * 
 * File: Point2D.cpp
 *
 * Description: Contains the class functions for Point2D
 *
 **********/
#include "Point2D.h"

Point2D::Point2D (){
	x = 0;
	y = 0;
}

Point2D::Point2D(int _x, int _y){
	x = _x;
	y = _y;
}

void Point2D::set(int _x, int _y){
	x = _x;
	y = _y;
}

int Point2D::getX(){
	return x;
}

int Point2D::getY(){
	return y;
}