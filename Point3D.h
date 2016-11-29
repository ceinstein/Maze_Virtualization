/**********
 * Author: Craig Einstein
 * 
 * File: Point3D.h
 *
 * Description: Header file for Point3D
 *
 **********/

#ifndef POINT3D
#define POINT3D

class Point3D{
	float x;
	float y;
	float z;

	public:
		Point3D ();
		Point3D (float x, float y, float z);
		void set(float _x, float _y, float _z);
		float getX();
		float getY();
		float getZ();

};

#endif