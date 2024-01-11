#include "20191244.h"

void generateMaze(vector<vector<Cell> >& maze, int x, int y) {
    maze[y][x].visited = true;

    while (true) {
        vector<Direction> directions;

        if (y > 0 && !maze[y - 1][x].visited) directions.push_back(NORTH);
        if (y < maze.size() - 1 && !maze[y + 1][x].visited) directions.push_back(SOUTH);
        if (x > 0 && !maze[y][x - 1].visited) directions.push_back(WEST);
        if (x < maze[0].size() - 1 && !maze[y][x + 1].visited) directions.push_back(EAST);

        if (directions.empty()) return;

        Direction dir = directions[rand() % directions.size()]; // 랜덤 방향 설정

        switch (dir) {
            case NORTH:
                maze[y][x].topWall = false;
                maze[y - 1][x].bottomWall = false;
                generateMaze(maze, x, y - 1);
                break;
            case SOUTH:
                maze[y][x].bottomWall = false;
                maze[y + 1][x].topWall = false;
                generateMaze(maze, x, y + 1);
                break;
            case WEST:
                maze[y][x].leftWall = false;
                maze[y][x - 1].rightWall = false;
                generateMaze(maze, x - 1, y);
                break;
            case EAST:
                maze[y][x].rightWall = false;
                maze[y][x + 1].leftWall = false;
                generateMaze(maze, x + 1, y);
                break;
        }
    }
}

int main() {
    srand(time(NULL));

    int width, height, startX, startY;
    ofstream outFile;
    cin >> width >> height;
    startX = rand() % width;
    startY = rand() % height;
    vector<vector<Cell> > maze(height, vector<Cell>(width));

    generateMaze(maze, startX, startY);

    outFile.open("result.maz");
    if(!outFile){
        cerr << "File Open Error" << endl;
        exit(1);
    }
    outFile << '+';
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++)
            outFile << (maze[i][j].topWall ? "-+" : " +");
        outFile << endl << '|';
        for(int j=0; j<width; j++)
            outFile << (maze[i][j].rightWall ? " |" : "  ");
        outFile << endl << '+';
    }

    for(int j=0; j<width; j++){
        outFile << "-+";
    }

    outFile.close();

    return 0;
}