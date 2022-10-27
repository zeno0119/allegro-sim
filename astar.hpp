#include <queue>
#include <stack>
#include <cmath>

class pos2d{
    public:
    int x;
    int y;
    pos2d(int x, int y){
        this->x = x;
        this->y = y;
    }
    pos2d(){
        this->x = 0;
        this->y = 0;
    }
    static int manhattan_dist(pos2d a, pos2d b){
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }
};

class astar_eval{
    public:
    pos2d pos;
    int slack;
    int dist;

    astar_eval(pos2d pos, int slack, int dist){
        this->dist = dist;
        this->slack = slack;
        this->pos = pos;
    }
    bool operator< (const astar_eval& a)const {
        return (this->dist + this->slack) < (a.dist + a.slack);
    }
    bool operator> (const astar_eval& a)const {
        return (this->dist + this->slack) > (a.dist + a.slack);
    }
};

class astar{
    public:
    std::stack<pos2d> astar_calc(pos2d src, int dst, int *map, pos2d dim, pos2d dst_tmp);
    astar(){

    }
    private:
    int *mapc;
    std::priority_queue<astar_eval, std::vector<astar_eval>, std::greater<astar_eval>> q;

};