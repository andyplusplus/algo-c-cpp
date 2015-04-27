/*
search maze from start position to end position:
0 - is passable;
1 - not passable

  1 1 0 1 1 1 0 1 1 1 1 1 0 1 0 0 0 1 1
  1 0 0 1 1 1 1 0 0 1 0 0 0 0 0 0 1 1 0
  1 0 0 0 0 0 0 0 1 0 1 1 1 1 0 0 0 0 1
  0 1 1 1 1 1 0 1 0 1 0 1 1 1 1 1 1 1 1
  0 1 0 1 1 1 0 0 0 1 0 1 1 0 0 0 0 0 0
  1 1 0 0 0 0 1 0 0 0 0 0 0 0 1 0 1 1 1
  1 0 0 0 1 1 1 1 0 1 1 0 1 0 1 0 0 1 0
  0 0 0 0 1 1 1 0 0 0 1 0 0 0 1 1 0 1 1
  0 0 1 1 0 0 1 0 0 0 1 1 1 1 0 0 0 0 0
  1 1 0 0 1 1 0 0 1 1 1 1 0 1 1 1 0 0 1
  0 0 0 0 1 1 1 0 0 0 1 1 0 1 0 1 1 0 0
  0 1 1 1 0 1 0 0 0 1 0 0 1 0 0 1 1 1 1
  0 0 1 0 0 1 0 1 0 1 0 1 1 0 1 0 0 1 1

  the following implementation:
  1. search one path,
  2. confirm the path
  3. and print the path

*/

#include <array>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

using std::array;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;


struct Position;

bool search_helper( vector<vector<int>>* maze,
                            const Position& s, Position& e, vector<Position>* path);

bool is_passable(const Position& s, const vector<vector<int>>& maze);


struct Position {
        int x, y;
        bool operator==(const Position &that) const {
                return x==that.x && y == that.y;
        }
};


vector<Position> search( vector<vector<int>> maze, const Position& s, Position& e ){
        vector<Position> path;
        maze[s.x][s.y] = 1;
        path.push_back(s);
        if( !search_helper(&maze, s, e, &path) ){
                path.pop_back();
        }
        return path;
}


//find path via Depth First Search
bool search_helper( vector<vector<int>>* maze,
                    const Position& s, Position& e, vector<Position>* path) {
        if (s == e){
                return true;
        }
        const array<array<int, 2>, 4> next_moves =
                {{{{0, 1}}, {{0, -1}}, {{1, 0}}, {{-1, 0}}}};

        for(const auto& move : next_moves){
                Position next{s.x + move[0], s.y + move[1]};
                if (is_passable(next, *maze)){
                        (*maze)[next.x][next.y] = 1;
                        path->push_back(next);
                        if (search_helper(maze, next, e, path)){
                                return true;
                        }
                        path->pop_back();
                }
        }
        return false;
}


bool is_passable(const Position& s, const vector<vector<int>>& maze) {
        return s.x >= 0 && s.x < maze.size() &&
               s.y >= 0 && s.y < maze[s.x].size() && maze[s.x][s.y] == 0;
}


int main(int argc, char* argv[]) {
        default_random_engine gen((random_device())());
        for (int times = 0; times < 100; ++times) {

                //Init Maze, 0 passable
                uniform_int_distribution<int> dis(1, 30);
                int n = dis(gen);
                int m = dis(gen);
                vector<vector<int>> maze(n, vector<int>(m));

                for (int i = 0; i < n; ++i) {
                        for (int j = 0; j < m; ++j) {
                                uniform_int_distribution<int> zero_or_one(0, 1);
                                maze[i][j] = zero_or_one(gen);
                        }
                }

                //Print maze
                vector<Position> steps;
                for (int i = 0; i < n; ++i) {
                        for (int j = 0; j < m; ++j) {
                                if (maze[i][j] == 0) {
                                        steps.push_back(Position{i, j});
                                }
                                cout << maze[i][j] << ' ';
                        }
                        cout << endl;
                }
                cout << endl;

                if (steps.size()) {
                        uniform_int_distribution<int> dis(0, steps.size() - 1);
                        int start = dis(gen);
                        int end = dis(gen);
                        cout << steps[start].x << ' ' << steps[start].y << endl;
                        cout << steps[end].x << ' ' << steps[end].y << endl;
                        vector<Position> path = search(maze, steps[start], steps[end]);

                        //assert the path is correct
                        if (!path.empty()) {
                                assert(steps[start] == path.front() && steps[end] == path.back());
                        }
                        for (int i = 0; i < path.size(); ++i) {
                                if (i > 0) {
                                        assert(abs(path[i - 1].x - path[i].x) +
                                               abs(path[i - 1].y - path[i].y) == 1);
                                }
                                cout << '(' << path[i].x << ',' << path[i].y << ')' << endl;
                        }
                }
        }
        return 0;
}
