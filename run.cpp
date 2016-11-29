/**********
 * Author: Craig Einstein
 * 
 * File: run.cpp
 *
 * Descirption: Handles the set up and running of the virtualization
 *
 **********/
#include <iostream>
#include "Maze.h"
 #include "Robot.h"
#include "Point2D.h"
#include "Point3D.h"
#include "ObjLoader.h"
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <stdio.h>
#include "lib3ds/file.h"
#include "lib3ds/mesh.h"
#include "lib3ds/material.h"
#include "ObjLoader.h"
#include "Point3D.h"
#include "SOIL/SOIL.h"

GLuint wall;
GLuint beacon;

int XX = 0;
int YY = 0;
int ZED = 0;
int LOOKX = 0;
int LOOKY = 0;
int g = 0;
const char * WALL = "wall";
const char * BEACON = "beacon";
Maze maze;
Robot robot;

void start(int argc,char** argv);

int main(int argc,char** argv){
    if(argc < 3){
        printf("Must Include Row and Column Arguments!\nExiting!\n");
        return 1;
    }
    if(atoi(argv[1]) < 6 || atoi(argv[2])< 6){
        printf("Maze must be bigger!\nExiting!\n");
        return 1;
    }
    maze.initialize(atoi(argv[1]), atoi(argv[2]));
    maze.print();
    start(argc, argv);

    return 0;
}


void createObject(char *file, GLuint* object){

    int v, t, n;
    Point3D vertex, texture, normal;
    *object = glGenLists(1);
    glNewList(*object, GL_COMPILE);
    ObjLoader o(file);
    glPushMatrix();
    GLuint tex_2d;
    if(g == 0){
        tex_2d = SOIL_load_OGL_texture(
        "Models/iss044e045565.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    }else{
        tex_2d = SOIL_load_OGL_texture(
        "Models/purple.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    }
    glBegin(GL_QUADS);

    switch(o.getFileType()){
        case 1:
            for(int i = 0; i < o.getFaceCount() * 4; i++){
                v = o.getFaceVertex(i);
                vertex = o.getVertex(v);
                glNormal3f(0, 0, -1);
                glVertex3f(vertex.getX(), vertex.getY(), vertex.getZ());
            }
            break;
        case 2:
            for(int i = 0; i < o.getFaceCount() * 4; i++){
                v = o.getFaceVertex(i);
                n = o.getFaceNormal(i);
                vertex = o.getVertex(v);
                normal = o.getNormal(n);
                glNormal3f(normal.getX(), normal.getY(), normal.getZ());
                glVertex3f(vertex.getX(), vertex.getY(), vertex.getZ());
            }
            break;
        case 3:
             for(int i = 0; i < o.getFaceCount() * 4; i++){
                v = o.getFaceVertex(i);
                n = o.getFaceNormal(i);
                vertex = o.getVertex(v);
                normal = o.getNormal(n);
                glNormal3f(normal.getX(), normal.getY(), normal.getZ());
                glVertex3f(vertex.getX(), vertex.getY(), vertex.getZ());
            }
            break;
        case 4:
                glBindTexture(GL_TEXTURE_2D, tex_2d);

                for(int i = 0; i < o.getFaceCount() * 4; i++){
                    v = o.getFaceVertex(i);
                    t = o.getFaceTextureUV(i);
                    n = o.getFaceNormal(i);
                    vertex = o.getVertex(v);
                    texture = o.getTextureUV(t);
                    normal = o.getNormal(n);
                    glNormal3f(normal.getX(), normal.getY(), normal.getZ());
                    glTexCoord2f(texture.getX(), texture.getY());
                    glVertex3f(vertex.getX(), vertex.getY(), vertex.getZ());
                }
            break;


    }
   
    glEnd();
    glPopMatrix();
    glEndList();
}

void drawObject(float x, float z, GLuint* object){
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glTranslatef(-x, 0, z);
    glScalef(1,1,1);
    glCallList(*object);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
}

void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
    //glOrtho(-25,25,-2,2,0.1,100);
    glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
    glClearColor (0.0,0.0,0.0,1.0);
    // background color 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // glEnable(GL_LIGHTING);
   // glEnable(GL_LIGHT0);
  //  glEnable(GL_TEXTURE_2D);    
    glEnable(GL_DEPTH_TEST);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   for(int i = maze.getRows() - 1; i >= 0; i--){ //Rows
    	for(int j = 0; j < maze.getColumns(); j++){ //Columns
    		if(maze.getTile(j, i) != maze.freeChar() && maze.getTile(j, i) != maze.beaconChar()){
    			drawObject(j * 5.8, ((maze.getRows() - 1) - i) * 5.8, &wall);
    		}

    		if(maze.getTile(j, i) == maze.beaconChar()){
            	drawObject(j * 5.8, ((maze.getRows() - 1) - i) * 5.8, &beacon);
            }
    	}
    }
    glFlush();

    glLoadIdentity();
   // std::cout << (glutGet(GLUT_WINDOW_WIDTH)/2) + LOOKX << std::endl;
    gluLookAt(XX, YY, ZED, (glutGet(GLUT_WINDOW_WIDTH)/2) + LOOKX, (glutGet(GLUT_WINDOW_HEIGHT)/2) + LOOKY, 1000, 0, 1, 0);
    float lightPos[] = { 0 , 0 + YY , 0 ,1 };        // light position
    // float noAmbient[] = { 0.2, 0.2, 0.2, 1 };     // low ambient light
    float diffuse[] = { 0.2, 0.2, 0.2, 1 };        // full diffuse colour
    float specular[] = {0, 0, 1, 1};
    //glLightfv(GL_LIGHT0, GL_AMBIENT, noAmbient);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR,specular);
    glLightfv(GL_LIGHT0, GL_POSITION,lightPos);
    
    glutSwapBuffers(); //swap the buffers
}

void keyPressed(unsigned char key, int x, int y){
	if(key == 'w'){
		ZED += 5;
    //    LOOKX+= 100;
	}
	if(key == 's'){
		ZED -= 5;
	}
	if(key == 'a'){
		XX += 5;
	}
	if(key == 'd'){
		XX -= 5;
	}
	if(key == 'q'){
		YY += 5;
	}
	if(key == 'e'){
		YY -= 5;
	}
    if(key == 'g'){
        if(g == 0){
            g = 1;
        }else{
            g = 0;
        }
        
        createObject("Models/bruh.obj", &wall);
    }
    if(key == 'r'){
        LOOKX = 0;
        LOOKY = 0;
        ZED = 0;
        XX = 0;
        YY = 0;
    }

}

void mouse(int x, int y){
    //std::cout << x << " " << y << " " << std::endl;
    LOOKX = x;
    LOOKY = -y;
}
void start(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(800,450);
    glutInitWindowPosition(20,20);
    glutCreateWindow("ObjLoader");
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);


    glShadeModel (GL_SMOOTH);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutPassiveMotionFunc(mouse);
    glutKeyboardFunc(keyPressed);
    createObject("Models/untitled.obj", &wall);
    createObject("Models/HUMAN.obj", &beacon);

    glutMainLoop();
}
