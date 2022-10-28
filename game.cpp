#include "game.hpp"

bool Map::put(pos2d pos, Tile t) {
    if (pos.x >= size.x || pos.x < 0 || pos.y >= size.y || pos.y < 0) {
        return false;
    }
    map[pos.x + pos.y * size.x] = t;
}

void Map::draw() {
    for (int i = 0; i < size.x * size.y; i++) {
        int x = i % size.x;
        int y = i / size.x;
        if (!map[i].is_passable()) {
            al_draw_filled_rectangle(x * 10, y * 10, (x + 1) * 10, (y + 1) * 10,
                                     al_map_rgb(255, 255, 255));
        }
    }
}

Tile Map::type(pos2d pos) { return map[pos.x + size.x * pos.y]; }
Tile Map::type(int x, int y) { return map[x + size.x * y]; }

pos2d Agent::step(Map *map, std::vector<Work> *works) {
    if (this->move_stack.empty()) {

        al_draw_rectangle(pos.x * 10, pos.y * 10, (pos.x + 1) * 10,
                          (pos.y + 1) * 10, al_map_rgb(255, 0, 0), 2);
        if (!on_move) {
            std::vector<pos2d> dsts;
            // std::cout << "tansaku" << std::endl;
            for (auto &el : *works) {
                if (el.get_id() == 1 && !el.alloc) {
                    dsts.push_back(el.get_src());
                }
            }
            if (dsts.size() == 0)
                return pos2d();
            auto res = astar_calc(this->pos, map->map.data(), map->dim(), dsts);
            if (res.second != -1) {
                move_stack = res.first;
                (*works)[res.second].alloc = true;
                on_move = true;
            } else {
                std::cout << "no path" << std::endl;
            }
        } else {
            auto res = astar_calc(this->pos, map->map.data(), map->dim(),
                                  std::vector<pos2d>{alloc_work.get_dst()});
            if (res.second != -1) {
                on_move = false;
            }
        }
        // std::cout << move_stack.size() << std::endl;
    } else {
        pos2d p;
        while (!move_stack.empty()) {
            p = move_stack.top();
            move_stack.pop();
            if (p.x != pos.x || p.y != pos.y)
                break;
        }
        pos = p;
        al_draw_rectangle(pos.x * 10, pos.y * 10, (pos.x + 1) * 10,
                          (pos.y + 1) * 10, al_map_rgb(255, 0, 0), 2);
    }
    // std::cout << pos.x << pos.y << std::endl;
}