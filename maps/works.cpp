#include "works.hpp"

Work::Work(int id, pos2d src, pos2d dst) {
    this->id = id;
    this->src = src;
    this->dst = dst;
    this->alloc = false;
}

Work::Work() {
    this->id = -1;
    this->src = pos2d(-1, -1);
    this->dst = this->src;
}

void Work::draw() {
    if (id == 1) {
        al_draw_filled_rectangle(src.x * 10, src.y * 10, (src.x + 1) * 10,
                                 (src.y + 1) * 10, al_map_rgb(255, 0, 0));
    }
}