//!	Class: Creating a maze by using BFS algorithm. Struct node was used to navigate the directions of the new generated maze. 
/*!
	Auther: Abdulhadi Daher and Yazan Bahem
	Date: 20 / 11 / 2022
*/
#ifndef MAZE_H
#define MAZE_H
#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <string>
#include<algorithm>

class maze {
public:

	maze();
	maze(const int sizeX, const int sizeY);
	maze(const maze& src);
	maze& operator =(const maze& rhs);
	~maze();


	void createNewMaze();
	void runUnvisitedNode();
	void BFS_generate();

	//!	Maze will contain multiple minimal numbers of nodes, which has some features to be able to navigate the directions given by the BFS algorithm in the new generated maze  
	struct node {
		node(int y, int x, int nodeNumber);
		bool isVisited;
		node* north;
		node* west;
		node* south;
		node* east;
		int nodeNumber;
		int node_y;
		int node_x;
	};
	bool north_neighbourCheck( node* &currentNode);
	bool west_neighbourCheck( node* &currentNode);
	bool south_neighbourCheck( node* &currentNode);
	bool east_neighbourCheck( node* &currentNode);

public:
	int maze_Y;
	int maze_X;
	node* start;
	node* end;
	node* key;
	std::vector<std::vector<node*>> NodesVector;

};
#endif