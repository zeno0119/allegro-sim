#ifndef _WORKS_H_
#define _WORKS_H_

#include "../astar.hpp"
#include <allegro5/allegro_primitives.h>
class Work {
  private:
    int id;
    pos2d src;
    pos2d dst;

  public:
    bool alloc;
    Work(int id, pos2d src, pos2d dst);
    Work();
    int get_id() { return this->id; }
    pos2d get_src() { return this->src; }
    pos2d get_dst() { return this->dst; }
    void draw();
};

#endif