#include <vector>
#include "astar.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

class Map{
    private:
    pos2d size;
    public:
    std::vector<int> map;
    Map(int x, int y){
        this->map = std::vector<int>(x * y);
        this->size = pos2d(x, y);
        for(int i = 0;i < size.x * size.y;i++){
            map[i] = 0;
        }
    }
    bool put(pos2d pos, int type);

    void draw();

    pos2d dim(){
        return this->size;
    }

    int type(pos2d pos);
};

class Agent{
    public:
    pos2d step(Map *map);
    Agent(pos2d pos){
        this->pos = pos;
    }

    private:
    std::stack<pos2d> move_stack;
    bool on_move;
    pos2d pos;
};