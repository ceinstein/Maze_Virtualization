/**********
 * Author: Craig Einstein
 * 
 * File: Point3D.cpp
 *
 * Description: Contains the class functions for Point3D
 *
 **********/
#include "Point3D.h"

Point3D::Point3D (){
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Point3D::Point3D (float _x, float _y, float  _z){
	x = _x;
	y = _y;
	z = _z;
}

void Point3D::set(float _x, float _y, float _z){
	x = _x;
	y = _y;
	z = _z;
}

float Point3D::getX(){
	return x;
}

float Point3D::getY(){
	return y;
}

float Point3D::getZ(){
	return z;
}