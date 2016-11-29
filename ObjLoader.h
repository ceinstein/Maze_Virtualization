/**********
 * Author: Craig Einstein
 * 
 * File: ObjLoader.h
 *
 * Description: Header file for ObjLoader
 *		ObjLoader loads a .obj file and places the vertices, normals, and UVs into Point3Ds
 *		The ObjLoader object can then be used by OpenGl
 *
 **********/
#ifndef OBJLOADER
#define OBJLOADER
#include "Point3D.h"
#include <stdio.h>
#include <iostream>

class ObjLoader{
	int vertCount;
	int faceCount;
	Point3D* vertices;
	Point3D* textureUVs;
	Point3D* normals;
	int** faces;
	int fileType;

	public:
		ObjLoader (std::string obj);
		int resolveFileType(const char* str);
		int getVCount();
		int getFaceCount();
		int getFileType(); 
		int getFaceVertex(int i);
		int getFaceTextureUV(int i);
		int getFaceNormal(int i);
		Point3D getVertex(int i);
		Point3D getTextureUV(int i);
		Point3D getNormal(int i);





};

#endif
