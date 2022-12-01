#include "Map.h"
//!Loading images and applying them to a particular shape in the map  
/*!
    @param 'shape' The loaded image will be applied to the shape futures
    @param 'texture' Is the loaded image
    @param 'path' Where the image is located in the OS
*/
void Map::setRectangleShapes(sf::RectangleShape& shape, sf::Texture& texture,std::string path) {
    texture.loadFromFile("L:/livecoding/Martin-c++/Project_test1/Project_test1/Images/"+path);
    shape.setTexture(&texture);
    shape.setSize(sf::Vector2f(100, 100));
}
//!Initializing the map length, width paths and walls as images from the original 'node' maze to a new myMapVec<2D RectangleShape vector> 
/*!
    @param 'maps_x_axies' The width of the maze 
    @param 'maps_y_axies' The length of the maze
*/
void Map::mapInit (sf::Vector2i map_dimensions) {
    srand(time(0));
	mainMaze.maze_X = map_dimensions.x;
	mainMaze.maze_Y = map_dimensions.y;
    //generating the maze
    mainMaze.createNewMaze();
    mainMaze.BFS_generate();

    //wall
    setRectangleShapes(wall,wallTexture,"wall.png");

    //path
    setRectangleShapes(path, pathTexture, "path.png");

    //doors
    setRectangleShapes(startDoor, startDoorTexture, "startDoor.png");
    setRectangleShapes(endDoor, endDoorTexture, "endDoor.png");

    //key
    setRectangleShapes(key, keyTexture, "key.png");
    setRectangleShapes(key2, keyTexture2, "key.png");

    // pushing_back wall, path, doors and key into myMapVec
    for (int y = 1; y < mainMaze.maze_Y + 1; y++) {
        std::vector<sf::RectangleShape> rowOfWallsAndPath;
        for (int x = 1; x < mainMaze.maze_X + 1; x++) {
            //surroundings walls
            if (x == 1 || y == 1 || y == mainMaze.maze_Y || x == mainMaze.maze_X) {
                if (y == 1) {//first row
                    if (x % 2 == 0 && mainMaze.NodesVector[(y - 1)][(x / 2) - 1] == mainMaze.start) {
                        startPoss.x = (100 * x) + 25;
                        startPoss.y = (100 * y) + 125;
                        startDoor.setPosition((100 * x), (100 * y));
                        rowOfWallsAndPath.push_back(startDoor);
                    }
                    else {
                        wall.setPosition((100 * x), (100 * y));
                        rowOfWallsAndPath.push_back(wall);
                    }
                }
                else if (y == mainMaze.maze_Y) {//last row

                    if (x % 2 == 0 && mainMaze.NodesVector[((y - 1) / 2) - 1][(x / 2) - 1] == mainMaze.end) {
                        /****************************************************************************************************************************/
                        EndPoss.x = 0;
                        EndPoss.y = 250;
                        endDoor.setPosition((100 * x), (100 * y));
                        rowOfWallsAndPath.push_back(endDoor);
                    }
                    else {
                        wall.setPosition((100 * x), (100 * y));
                        rowOfWallsAndPath.push_back(wall);
                    }
                }
                else {//rows in between the first and the last
                    wall.setPosition((100 * x), (100 * y));
                    rowOfWallsAndPath.push_back(wall);
                }
            }
            else if (y % 2 == 0 || x % 2 == 0) {
                //where all nodes are settled as(node non node)
                if (y % 2 == 0 && x % 2 == 0) {
                    if (mainMaze.NodesVector[(y / 2) - 1][((x - 1) / 2)] == mainMaze.key) {                 
                        key.setPosition((100 * x), (100 * y));
                        rowOfWallsAndPath.push_back(key);
                    }
                    else {
                        path.setPosition((100 * x), (100 * y));
                        rowOfWallsAndPath.push_back(path);                        
                    }

                }
                else {
                    //check for connection (rows)
                    if (x % 2 != 0) {
                        if (mainMaze.NodesVector[(y / 2) - 1][((x - 1) / 2) - 1]->east == mainMaze.NodesVector[(y / 2) - 1][((x - 1) / 2)] &&
                            mainMaze.NodesVector[(y / 2) - 1][((x - 1) / 2)]->west == mainMaze.NodesVector[(y / 2) - 1][((x - 1) / 2) - 1]) {
                            path.setPosition((100 * x), (100 * y));
                            rowOfWallsAndPath.push_back(path);
                        }
                        else {
                            wall.setPosition((100 * x), (100 * y));
                            rowOfWallsAndPath.push_back(wall);
                        }
                    }
                    //check for connection (columns)
                    if (y % 2 != 0) {
                        if (mainMaze.NodesVector[((y - 1) / 2) - 1][(x / 2) - 1]->south == mainMaze.NodesVector[((y - 1) / 2)][(x / 2) - 1] &&
                            mainMaze.NodesVector[((y - 1) / 2)][(x / 2) - 1]->north == mainMaze.NodesVector[((y - 1) / 2) - 1][(x / 2) - 1]) {
                            path.setPosition((100 * x), (100 * y));
                            rowOfWallsAndPath.push_back(path);
                        }
                        else {
                            wall.setPosition((100 * x), (100 * y));
                            rowOfWallsAndPath.push_back(wall);
                        }

                    }
                }
            }
            //diagonal positions
            else {
                wall.setPosition((100 * x), (100 * y));
                rowOfWallsAndPath.push_back(wall);
            }

        }
        myMapVec.push_back(rowOfWallsAndPath);
    }
    /*****************************************************************/
    //createMaze2(map_dimensions);
};

//! Get the start position of the maze to use it for player starting position
sf::Vector2f& Map::getStartPoss() { return startPoss;}

void Map::setPoss(sf::RectangleShape &shape, int &x, int &y, sf::Vector2i &old) {
    shape.setPosition((x) * 100, (old.y + (y)) * 100);
}

void Map::createMaze2(sf::Vector2i map_dimensions) {
    /**************************************/
    srand(time(0));
    mainMaze2.maze_X = map_dimensions.x;
    mainMaze2.maze_Y = map_dimensions.y + 6;
    mainMaze2.createNewMaze();
    mainMaze2.start = mainMaze2.NodesVector[0][mainMaze.end->node_x];

    mainMaze2.BFS_generate();
    // pushing_back wall, path, doors and key into myMapVec
    for (int y = 1; y < mainMaze2.maze_Y + 1; y++) {
        std::vector<sf::RectangleShape> rowOfWallsAndPath;
        for (int x = 1; x < mainMaze2.maze_X + 1; x++) {
            //surroundings walls
            if (x == 1 || y == 1 || y == mainMaze2.maze_Y || x == mainMaze2.maze_X) {
                if (y == 1) {//first row
                    if (x % 2 == 0 && mainMaze2.NodesVector[(y - 1)][(x / 2) - 1] == mainMaze2.start) {
                        setPoss(startDoor, x, y, map_dimensions);
                        //startPoss2.x = startDoor.getPosition().x + 25;
                        //startPoss2.y = startDoor.getPosition().y + 125;
                        //startDoor.setPosition((100 * x), (100 * y));
                        rowOfWallsAndPath.push_back(startDoor);
                    }
                    else {
                        setPoss(wall, x, y, map_dimensions);
                        //wall.setPosition((100 * x), (100 * y));
                        rowOfWallsAndPath.push_back(wall);
                    }
                }
                else if (y == mainMaze2.maze_Y) {//last row

                    if (x % 2 == 0 && mainMaze2.NodesVector[((y - 1) / 2) - 1][(x / 2) - 1] == mainMaze2.end) {
                        /****************************************************************************************************************************/
                        //EndPoss.x = (100 * x);
                        //EndPoss.y = (100 * y);
                        setPoss(endDoor, x, y, map_dimensions);
                        //endDoor.setPosition((100 * x), (100 * y));
                        rowOfWallsAndPath.push_back(endDoor);
                    }
                    else {
                        setPoss(wall, x, y, map_dimensions);
                        //wall.setPosition((100 * x), (100 * y));
                        rowOfWallsAndPath.push_back(wall);
                    }
                }
                else {//rows in between the first and the last
                    setPoss(wall, x, y, map_dimensions);
                    //wall.setPosition((100 * x), (100 * y));
                    rowOfWallsAndPath.push_back(wall);
                }
            }
            else if (y % 2 == 0 || x % 2 == 0) {
                //where all nodes are settled as(node non node)
                if (y % 2 == 0 && x % 2 == 0) {
                    if (mainMaze2.NodesVector[(y / 2) - 1][((x - 1) / 2)] == mainMaze2.key) {
                        setPoss(key2, x, y, map_dimensions);
                        //key.setPosition((100 * x), (100 * y));
                        rowOfWallsAndPath.push_back(key2);
                    }
                    else {
                        setPoss(path, x, y, map_dimensions);
                        //path.setPosition((100 * x), (100 * y));
                        rowOfWallsAndPath.push_back(path);
                    }

                }
                else {
                    //check for connection (rows)
                    if (x % 2 != 0) {
                        if (mainMaze2.NodesVector[(y / 2) - 1][((x - 1) / 2) - 1]->east == mainMaze2.NodesVector[(y / 2) - 1][((x - 1) / 2)] &&
                            mainMaze2.NodesVector[(y / 2) - 1][((x - 1) / 2)]->west == mainMaze2.NodesVector[(y / 2) - 1][((x - 1) / 2) - 1]) {
                            setPoss(path, x, y, map_dimensions);
                            //path.setPosition((100 * x), (100 * y));
                            rowOfWallsAndPath.push_back(path);
                        }
                        else {
                            setPoss(wall, x, y, map_dimensions);
                            //wall.setPosition((100 * x), (100 * y));
                            rowOfWallsAndPath.push_back(wall);
                        }
                    }
                    //check for connection (columns)
                    if (y % 2 != 0) {
                        if (mainMaze2.NodesVector[((y - 1) / 2) - 1][(x / 2) - 1]->south == mainMaze2.NodesVector[((y - 1) / 2)][(x / 2) - 1] &&
                            mainMaze2.NodesVector[((y - 1) / 2)][(x / 2) - 1]->north == mainMaze2.NodesVector[((y - 1) / 2) - 1][(x / 2) - 1]) {
                            setPoss(path, x, y, map_dimensions);
                            //path.setPosition((100 * x), (100 * y));
                            rowOfWallsAndPath.push_back(path);
                        }
                        else {
                            setPoss(wall, x, y, map_dimensions);
                            //wall.setPosition((100 * x), (100 * y));
                            rowOfWallsAndPath.push_back(wall);
                        }

                    }
                }
            }
            //diagonal positions
            else {
                setPoss(wall, x, y, map_dimensions);
                //wall.setPosition((100 * x), (100 * y));
                rowOfWallsAndPath.push_back(wall);
            }

        }
        myMapVec.push_back(rowOfWallsAndPath);
    }
}
