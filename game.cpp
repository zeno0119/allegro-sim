#include "game.hpp"

bool Map::put(pos2d pos, int type) {
  if (pos.x >= size.x || pos.x < 0 || pos.y >= size.y || pos.y < 0) {
    return false;
  }
  map[pos.x + pos.y * size.x] = type;
}

void Map::draw() {
  for (int i = 0; i < size.x * size.y; i++) {
    int x = i % size.x;
    int y = i / size.x;
    if (map[i] == -1) {
      al_draw_filled_rectangle(x * 10, y * 10, (x + 1) * 10, (y + 1) * 10,
                               al_map_rgb(255, 255, 255));
    }else if(map[i] == 50){
      al_draw_filled_rectangle(x * 10, y * 10, (x + 1) * 10, (y + 1) * 10,
                              al_map_rgb(0, 255, 0));
    }
  }
}

int Map::type(pos2d pos) { return map[pos.x + size.x * pos.y]; }

pos2d Agent::step(Map *map) {
  if (this->move_stack.empty()) {
    auto a = astar();
    int mindist = 1 << 30;
    pos2d minpos;
    for(int i = 0;i < map->dim().x * map->dim().y;i++){
      auto p = pos2d(i % map->dim().x, i / map->dim().x);
      if(map->type(p) == 50 && mindist > pos2d::manhattan_dist(pos, p)){
        mindist = pos2d::manhattan_dist(pos, p);
        minpos = p;
      }
    }
    // std::cout << "tansaku" << std::endl;
    move_stack = a.astar_calc(this->pos, 50, map->map.data(), map->dim(), minpos);
    // std::cout << move_stack.size() << std::endl;
  }else{
    pos2d p;
    while(!move_stack.empty()){
      p = move_stack.top();
      move_stack.pop();
      if(p.x != pos.x || p.y != pos.y)break;
    }
    pos = p;
    al_draw_rectangle(pos.x * 10, pos.y * 10, (pos.x + 1) * 10, (pos.y + 1) * 10, al_map_rgb(255, 0, 0), 2);
    if((pos.x == 10 && pos.y == 10) || (pos.x == 40 && pos.y == 40)){
      // std::cout << "arrive" << std::endl;
      map->put(pos2d(10, 10), 50);
      map->put(pos2d(40, 40), 50);
      map->put(pos, -1);
    }
  }
}