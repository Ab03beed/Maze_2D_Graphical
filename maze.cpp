#include "maze.h"

//!Parametrised node constructor
/*!
	@param 'y' Is node coordinate on the Y axis 
	@param 'x' Is node coordinate on the X axis 
	@param 'nodeNumber' Is a specific number which is given to every created node 
*/   
maze::node::node(int y, int x, int nodeNumber){

	this->north = nullptr;
	this->east = nullptr;
	this->south = nullptr;
	this->west = nullptr;
	this->isVisited = false;
	this->nodeNumber = nodeNumber;
	this->node_y = y;
	this->node_x = x;
}

//!Default maze constructor
maze::maze() {
	start = nullptr;
	end = nullptr;
	key = nullptr;
	maze_Y = 0;
	maze_X = 0;
}
//!Parametrised maze constructor
/*!
	@param 'x_axis' Is the maze width on the X axis
	@param 'y_axis' Is the maze length on the Y axis
*/
maze::maze(int x_axis, int y_axis) {
	start = nullptr;
	end = nullptr;
	key = nullptr;
	maze_Y = y_axis;
	maze_X = x_axis;
}
//!Copy constructor
/*!
	@param 'src' Is a const reference maze object
*/
maze::maze(const maze& src) {

	start = nullptr;
	end = nullptr;
	key = nullptr;
	maze_Y = 0;
	maze_X = 0;

	std::vector<std::vector<node*>> NewVector;

	for (int y = 0; y < src.NodesVector.size(); y++) {
		std::vector<node*> tempVector;
		for (int x = 0; x < src.NodesVector[y].size(); x++) {
			
			tempVector.push_back(src.NodesVector[y][x]);
		}
		NewVector.push_back(tempVector);
	}
}
//!Copy assign operator.
/*!
	@param 'rhs' Is a const reference maze object
*/
maze& maze::operator =(const maze& rhs) {

	if (this != &rhs) {
		this->~maze();
		this->start = rhs.start;
		this->end = rhs.end;
		this->maze_Y = rhs.maze_Y;
		this->maze_X = rhs.maze_X;
		this->key = rhs.key;

		std::vector<std::vector<node*>> NewVector;
		for (int y = 0; y < rhs.NodesVector.size(); y++) {
			std::vector<node*> tempVector;
			for (int x = 0; x < rhs.NodesVector[y].size(); x++) {

				tempVector.push_back(rhs.NodesVector[y][x]);
			}
			NodesVector.push_back(tempVector);
		}
	}
	return *this;
}
//!Maze destructor
maze::~maze() {

	for (int y = NodesVector.size() - 1; y >= 0 ; y--) {

		for (int x = 0; x < NodesVector[y].size(); x++) {
			
			NodesVector[y][x] = nullptr;
			delete NodesVector[y][x];
		}
		NodesVector.pop_back();
	}
}

//!Creates minimal numbers of nodes according to the maze width and length, then pushing_back the nodes to NodesVector<2D vector>
void maze::createNewMaze() {
	
	//srand(time(0));

	
	//get only how many nodes will this maze contain
	int Nodes_Y_axis = (this->maze_Y - 1) / 2;
	int Nodes_X_axis = (this->maze_X - 1) / 2;
	int NodeCounter = 0;
	int randEnd = rand() % Nodes_X_axis;
	int randStart = rand() % Nodes_X_axis;
	int randKey_X = rand() % Nodes_X_axis;
	int randKey_Y = rand() % Nodes_Y_axis;

	//create a 2D vector according to the number of nodes.
	for (int y = 0; y < Nodes_Y_axis; y++) {
		std::vector<node*> tempVector;
		
		for (int x = 0; x < Nodes_X_axis; x++) {
				
				node* NewNode = new node(y, x, NodeCounter);
				NodeCounter++;
				//choosing a random start and end for this maze
				if (y == 0 && x == randStart) { start = NewNode; }
				if (y == Nodes_Y_axis - 1 && x == randEnd ) { end = NewNode; }
				if (y == randKey_Y && x == randKey_X) { key = NewNode; }
				tempVector.push_back(NewNode);

		}
		NodesVector.push_back(tempVector);
	}
}
//!Switching all nodes to unvisited
void maze::runUnvisitedNode(){
	for (int y = 0; y < NodesVector.size(); y++) {

		for (int x = 0; x < NodesVector[y].size(); x++) {
			NodesVector[y][x]->isVisited = false;
		}
	}
}
//!!check the north node, out of the current node position
/*
 @param 'currentNode' Is a node pointer reference to the current node
*/
bool maze::north_neighbourCheck( node* &currentNode) {

	node* possNeighbour;
	//check if the currentNode's neighbour outside the maze or a surrounding wall
	if ((currentNode->node_y - 1) >= 0 && (currentNode->node_y - 1) < NodesVector.size()) {
		possNeighbour = NodesVector[currentNode->node_y - 1][currentNode->node_x];
		if (!(possNeighbour->isVisited)) {return true;}
		else { return false; }
	}
	else {return false;}
}

//!check the west node, out of the current node position
/*!
 @param 'currentNode' Is a node pointer reference to the current node
*/
bool maze::west_neighbourCheck( node* &currentNode) {
	
	node* possNeighbour;
	//check if the currentNode's neighbour outside the maze or a surrounding wall
	if ((currentNode->node_x - 1) >= 0 && (currentNode->node_x - 1) < NodesVector[currentNode->node_y].size()) {

		possNeighbour = NodesVector[currentNode->node_y][currentNode->node_x-1];
		if (!(possNeighbour->isVisited)) { return true; }
		else { return false; }
	}
	else { return false; }
}

//!check the south node, out of the current node position
/*!
 @param 'currentNode' Is a node pointer reference to the current node
*/
bool maze::south_neighbourCheck( node* &currentNode) {
	
	node* possNeighbour;
	//check if the currentNode's neighbour outside the maze or a surrounding wall
	if ((currentNode->node_y +1) >= 0 && (currentNode->node_y + 1) < NodesVector.size()) {

		possNeighbour = NodesVector[currentNode->node_y+1][currentNode->node_x];
		if (!(possNeighbour->isVisited)) { return true; }
		else { return false; }
	}
	else { return false; }
}

//!check the east node, out of the current node position
/*!
 @param 'currentNode' Is a node pointer reference to the current node
*/
bool maze::east_neighbourCheck( node* &currentNode) {

	node* possNeighbour;
	//check if the currentNode's neighbour outside the maze or a surrounding wall
	if ((currentNode->node_x + 1) >= 0 && (currentNode->node_x + 1) < NodesVector[currentNode->node_y].size()) {
		possNeighbour = NodesVector[currentNode->node_y][currentNode->node_x+1];
		if (!(possNeighbour->isVisited)) { return true; }
		else { return false; }
	}
	else { return false; }
}

//!Generating maze according to the BFS algorithm
void maze::BFS_generate() {

	//Make all nodes unvisited
	for (int y = 0; y < NodesVector.size(); y++) {
		for (int x = 0; x < NodesVector[y].size(); x++) {
			NodesVector[y][x]->isVisited = false;
		}
	}

	node* currentNode;
	std::list<node*> NodesList;
	std::vector<node*> tempList;
	currentNode = start;
	currentNode->isVisited = true;
	NodesList.push_front(currentNode);

	while (!(NodesList.empty())) {
		currentNode = NodesList.back();
		NodesList.pop_back();
		std::vector <int> possDirection;
		//check if there is unvisited neighbour
		if (north_neighbourCheck(currentNode)) {
			possDirection.push_back(0);
		}
		if (east_neighbourCheck(currentNode)) {
			possDirection.push_back(1);
		}
		if (south_neighbourCheck(currentNode)) {
			possDirection.push_back(2);
		}
		if (west_neighbourCheck(currentNode)) {
			possDirection.push_back(3);
		}

		if (!(possDirection.empty())){
			NodesList.push_front(currentNode);
			int randNeighbour = rand() % possDirection.size();
			int neighbourNum = possDirection[randNeighbour];
			node* possNeighbour{};

			if (neighbourNum == 0) {
				possNeighbour = NodesVector[currentNode->node_y - 1][currentNode->node_x];
				possNeighbour->south = currentNode;
				currentNode->north = possNeighbour;
			}
			else if (neighbourNum == 1) {
				possNeighbour = NodesVector[currentNode->node_y][currentNode->node_x + 1];
				possNeighbour->west = currentNode;
				currentNode->east = possNeighbour;
			}
			else if (neighbourNum == 2) {
				possNeighbour = NodesVector[currentNode->node_y + 1][currentNode->node_x];
				possNeighbour->north = currentNode;
				currentNode->south = possNeighbour;
			}
			else if (neighbourNum == 3) {
				possNeighbour = NodesVector[currentNode->node_y][currentNode->node_x - 1];
				possNeighbour->east = currentNode;
				currentNode->west = possNeighbour;
			}
			possNeighbour->isVisited = true;
			tempList.push_back(possNeighbour);
		}
		else {
			while(!(tempList.empty())) {//before pushing_back children in the order we choose them we add them randomly
				int tempRand = rand() % tempList.size();
				NodesList.push_back(tempList[tempRand]);
				tempList.erase(tempList.begin() + tempRand);
			}
	
		}
	}
	// all nodes needs to be unvisited to print after generating (My print function will prin "." if the nodes are visited)
	for (int y = 0; y < NodesVector.size(); y++) {
		for (int x = 0; x < NodesVector[y].size(); x++) {
			NodesVector[y][x]->isVisited = false;
		}
	}
}