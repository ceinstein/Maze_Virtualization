/**********
 * Author: Craig Einstein
 * 
 * File: ObjLoader.cpp
 *
 * Description: Contains the class functions for ObjLoader
 *		- Currently accepts Blender 2.76 obj files
 *		- Must use a different obj file for every component of an object
 *
 **********/
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <iostream>
#include <fstream>
#include "ObjLoader.h"
#include <stdio.h>
#include "Point3D.h"


ObjLoader::ObjLoader(std::string obj){

	char data[1000];
	int vert = 0;
	int vn = 0;
	int vt = 0;
	int f = 0;
	int fType = 0; 
	//0 = unset, 1 = just vertices, 2 = vertices/normals, 3 = vert//norm, 4 = vert/uv/norm, -1 = undetected
	std::ifstream file;
	file.open(obj);
	std::string str;
	while(std::getline(file, str)){
		if (str[0] == 'v' && str[1] != 'n'){
			vert++;
		}

		if (str[0] == 'v' && str[1] == 't'){
			vt++;
		}

		if (str[0] == 'v' && str[1] == 'n'){
			vn++;
		}

		if (str[0] == 'f'){
			if(fType == 0){
				fType = resolveFileType((const char *)str.c_str());
				fileType = fType;
			}
			f++;
		}

	}
	file.close();
	vertCount = vert;
	faceCount = f;

	vertices = (Point3D *) malloc(sizeof(Point3D) * vertCount);
	textureUVs = (Point3D *) malloc(sizeof(Point3D) * vt);
	normals = (Point3D *) malloc(sizeof(Point3D) * vn);
	
	faces = (int **) malloc(sizeof(long) * (faceCount * 4));
	for(int i = 0; i < faceCount * 4; i++){
		faces[i] = (int *) malloc(sizeof(long) * 3);
	}

	file.open(obj);

	char c;
	int line = 0, countV = 0, countT = 0, countN = 0, countF = 0;
	int v1, v2, v3, v4, t;
	int t1, t2, t3, t4;
	int n1, n2, n3, n4;
	float x, y, z;
    str = "";

	while(std::getline(file, str)){
		const char * data= str.c_str();
		if (str[0] == 'v' && str[1] != 'n'){
			line = std::sscanf(data, "%c %f %f %f", &c, &x, &y, &z);
			vertices[countV++].set(x, y, z);

			
		}

		if (str[0] == 'v' && str[1] == 't'){
			z = 0;
			line = std::sscanf(data, "%c%c %f %f", &c, &c, &x, &y);
			textureUVs[countT++].set(x, y, z);
		}

		if (str[0] == 'v' && str[1] == 'n'){
			line = std::sscanf(data, "%c%c %f %f %f", &c, &c, &x, &y, &z);
			normals[countN++].set(x, y, z);
		}

		if (str[0] == 'f'){
			switch(fileType){
				case 1:
					line = std::sscanf(data, "%c %i %i %i %i", &c, &v1, &v2, &v3, &v4);
					faces[countF++][0] = v1; 
					faces[countF++][0] = v2; 
					faces[countF++][0] = v3; 
					faces[countF++][0] = v4; 
					break;
				case 2: //Can get normals by analyzing each plane
						line = std::sscanf(data, "%c %i/%i %i/%i %i/%i %i/%i", &c, &v1, &n1, &v2, &n2, &v3, &n3, &v4, &n4);
						faces[countF][0] = v1; faces[countF++][2] = n1;
						faces[countF][0] = v2; faces[countF++][2] = n2;
						faces[countF][0] = v3; faces[countF++][2] = n3;
						faces[countF][0] = v4; faces[countF++][2] = n4;
					break;
				case 3:
						line = std::sscanf(data, "%c %i//%i %i//%i %i//%i %i//%i", &c, &v1, &n1, &v2, &n2, &v3, &n3, &v4, &n4);
			
						faces[countF][0] = v1; faces[countF++][2] = n1;
						faces[countF][0] = v2; faces[countF++][2] = n2;
						faces[countF][0] = v3; faces[countF++][2] = n3;
						faces[countF][0] = v4; faces[countF++][2] = n4;
					break;
				case 4:
						int temp = 0;
						line = std::sscanf(data, "%c %i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i", &c, &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3, &v4, &t4, &n4);
						faces[countF][0] = v1; faces[countF][1] = t1; faces[countF++][2] = n1;
						faces[countF][0] = v2; faces[countF][1] = t2; faces[countF++][2] = n2;
						faces[countF][0] = v3; faces[countF][1] = t3; faces[countF++][2] = n3;
						faces[countF][0] = v4; faces[countF][1] = t4; faces[countF++][2] = n4;
					break;
			}




			   

		}

	}
}

int ObjLoader::resolveFileType(const char* str){
	
	int i = 2;
	
	while(str[i] != ' ' && str[i] != '/' && str[i] != '\n'){
		i++;
	}

	if(str[i] == ' '){ //ONLY GIVES VERTICES (%i)
		return 1;
	}

	int j = i + 1;
	while(str[j] != ' ' && str[j] != '/' && str[j] != '\n'){
		j++;
	}


	if(str[j] == ' '){ //GIVES VERTICES AND NORMALS WITH SPACE FOR UV (%i/%i)
		return 2;
	}else if(j == (i + 1)){ //GIVES VERTICES AND NORMALS BUT HAS SPACE FOR UV (%i//%i)
		return 3;
	}else{ //GIVES VERTICES, UV, AND NORMALS
		return 4; 
	}

	return -1; //HAVE NOT YET ENCOUNTERED THIS FORMAT
}

int ObjLoader::getVCount(){
	return vertCount;
}

int ObjLoader::getFaceCount(){
	return faceCount;
}

int ObjLoader::getFileType(){
	return fileType;
}

int ObjLoader::getFaceVertex(int i){
	return faces[i][0];
}

int ObjLoader::getFaceTextureUV(int i){
	return faces[i][1];
}

int ObjLoader::getFaceNormal(int i){
	return faces[i][2];
}

Point3D ObjLoader::getVertex(int i){
	i -= 1;
	return vertices[i];
}

Point3D ObjLoader::getTextureUV(int i){
	i -= 1;
	return textureUVs[i];
}

Point3D ObjLoader::getNormal(int i){
	i -= 1;
	return normals[i];
}

/*int main(){
	ObjLoader obj("stylized_levi.obj");
	return 1;
}*/

