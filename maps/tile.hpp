#ifndef _TILE_H_
#define _TILE_H_

#include <allegro5/allegro5.h>
#include <string>

class Tile {
  public:
    Tile(bool passable, int cost, std::string path, bool connectable) {
        this->passable = passable;
        this->cost = cost;
        this->connectable = connectable;
    }

    bool is_passable() { return this->passable; }
    int get_cost() { return this->cost; }

  private:
    bool passable;
    int cost;
    bool connectable;
};
#endif