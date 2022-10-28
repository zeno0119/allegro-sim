#include "astar.hpp"
#include "maps/tile.hpp"
#include "maps/works.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <vector>

class Map {
  private:
    pos2d size;

  public:
    std::vector<Tile> map;
    Map(int x, int y) {
        this->map;
        this->size = pos2d(x, y);
        for (int i = 0; i < size.x * size.y; i++) {
            map.push_back(Tile(true, 1, "", false));
        }
    }
    bool put(pos2d pos, Tile t);

    void draw();

    pos2d dim() { return this->size; }

    Tile type(pos2d pos);
    Tile type(int x, int y);
};

class Agent {
  public:
    pos2d step(Map *map, std::vector<Work> *works);
    Agent(pos2d pos) {
        this->pos = pos;
        on_move = false;
    }
    Work alloc_work;

  private:
    std::stack<pos2d> move_stack;
    bool on_move;
    pos2d pos;
};