/**********
 * Author: Craig Einstein
 * 
 * File: Robot.h
 *
 * Description: Contains the class definitions for the Robot class. 
 *
 **********/

 #ifndef ROBOT
 #define ROBOT
 #include <stdio.h>
 #include "Maze.h"
 #include "Point3D.h"


 class Robot{
 	Point3D position;
 	Point3D direction;
 	int turnAmount;
 	Maze maze;


 	public:
 		void initialize(Maze maze);








 };

 #endif