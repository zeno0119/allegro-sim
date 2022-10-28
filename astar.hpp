#ifndef _ASTAR_H_
#define _ASTAR_H_
#include "maps/tile.hpp"
#include <cmath>
#include <queue>
#include <stack>
#include <utility>

class pos2d {
  public:
    int x;
    int y;
    pos2d(int x, int y) {
        this->x = x;
        this->y = y;
    }
    pos2d() {
        this->x = 0;
        this->y = 0;
    }
    static int manhattan_dist(pos2d a, pos2d b) {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }
};

class astar_eval {
  public:
    pos2d pos;
    int slack;
    int dist;

    astar_eval(pos2d pos, int slack, int dist) {
        this->dist = dist;
        this->slack = slack;
        this->pos = pos;
    }
    bool operator<(const astar_eval &a) const {
        return (this->dist + this->slack) < (a.dist + a.slack);
    }
    bool operator>(const astar_eval &a) const {
        return (this->dist + this->slack) > (a.dist + a.slack);
    }
};

std::pair<std::stack<pos2d>, int> astar_calc(pos2d src, Tile *map, pos2d dim,
                                             std::vector<pos2d> dsts);

#endif