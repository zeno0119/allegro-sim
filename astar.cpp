#include "astar.hpp"
#include <stdlib.h>
#include <iostream>

// int main(){
//     int width = 64;
//     int height = 64;
//     int map[25] = {0, 0, 0, 0, 0,
//                 0, -1, -1, -1, 0,
//                 0, 0, 0, 0, 0,    
//                 -1, -1, 50, -1, -1,
//                 2, 0, 50, 0, 2};
//     auto a = astar();
//     auto res = a.astar_calc(pos2d(0, 0), 2, map, pos2d(5, 5), pos2d(4, 4));
//     std::cout << res.size() << std::endl;
//     int c = 0;
//     if(res.size() == 0){
//         std::cout << "No path" << std::endl;
//     }
//     while(!res.empty()){
//         auto el = res.top();
//         std::cout << el.x << ", " << el.y << std::endl;
//         res.pop();
//     }
// }


std::stack<pos2d> astar::astar_calc(pos2d src, int dst, int *map, pos2d dim, pos2d dst_tmp){
    while(!q.empty()){
        q.pop();
    }
    q.push(astar_eval(src, pos2d::manhattan_dist(src, dst_tmp), 0));
    int *mapc = (int *)malloc(sizeof(int) * dim.x * dim.y);
    pos2d *prev = (pos2d *)malloc(sizeof(pos2d) * dim.x * dim.y);
    for(int i = 0;i < dim.x * dim.y;i++){
        mapc[i] = 1 << 30;
    }
    mapc[src.x + src.y * dim.x] = 0;
    while(!q.empty()){
        auto el = q.top();
        q.pop();
        if(map[el.pos.x + el.pos.y * dim.x] == dst){
            //backtrack
            auto now = el.pos;
            auto res = std::stack<pos2d>();
            while(1){
                res.push(now);
                if(now.x == src.x && now.y == src.y)break;
                now = prev[now.x + now.y * dim.x];
            }
            free(mapc);
            free(prev);
            return res;
        }
        
        if(el.pos.x > 0){
            if(mapc[el.pos.x - 1 + el.pos.y * dim.x] > el.dist + 1 && map[el.pos.x - 1 + el.pos.y * dim.x] >= 0){
                auto dst2 = pos2d(el.pos.x - 1, el.pos.y);
                mapc[dst2.x + dst2.y * dim.x] = el.dist + 1;
                prev[dst2.x + dst2.y * dim.x] = el.pos;
                q.push(astar_eval(dst2, pos2d::manhattan_dist(dst_tmp, dst2), el.dist + 1));
                // std::cout << q.top().pos.x << std::endl;
            }
        }
        if(el.pos.x < dim.x - 1){
            // std::cout << "2" << std::endl;
            if(mapc[el.pos.x + 1 + el.pos.y * dim.x] > el.dist + 1 && map[el.pos.x + 1 + el.pos.y * dim.x] >= 0){
                auto dst2 = pos2d(el.pos.x + 1, el.pos.y);
                mapc[dst2.x + dst2.y * dim.x] = el.dist + 1;
                prev[dst2.x + dst2.y * dim.x] = el.pos;
                // std::cout << dst2.x << ", " << dst2.y << std::endl;
                q.push(astar_eval(dst2, pos2d::manhattan_dist(dst_tmp, dst2), el.dist + 1));
            }
        }

        if(el.pos.y > 0){
            // std::cout << "3" << std::endl;
            if(mapc[el.pos.x + (el.pos.y - 1) * dim.x] > el.dist + 1 && map[el.pos.x + (el.pos.y - 1) * dim.x] >= 0){
                auto dst2 = pos2d(el.pos.x, el.pos.y - 1);
                mapc[dst2.x + dst2.y * dim.x] = el.dist + 1;
                prev[dst2.x + dst2.y * dim.x] = el.pos;
                // std::cout << dst2.x << ", " << dst2.y << std::endl;
                q.push(astar_eval(dst2, pos2d::manhattan_dist(dst_tmp, dst2), el.dist + 1));
            }
        }
        if(el.pos.y < dim.y - 1){
            // std::cout << "4" << std::endl;
            if(mapc[el.pos.x + (el.pos.y + 1) * dim.x] > el.dist + 1 && map[el.pos.x + (el.pos.y + 1) * dim.x] >= 0){
                auto dst2 = pos2d(el.pos.x, el.pos.y + 1);
                mapc[dst2.x + dst2.y * dim.x] = el.dist + 1;
                prev[dst2.x + dst2.y * dim.x] = el.pos;
                // std::cout << dst2.x << ", " << dst2.y << std::endl;
                q.push(astar_eval(dst2, pos2d::manhattan_dist(dst_tmp, dst2), el.dist + 1));
            }
        }
    }
    return std::stack<pos2d>();
}