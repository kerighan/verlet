#ifndef __NODEH__
#define __NODEH__
#include "vec.hpp"
#include <vector>


class Node {
public:
    Node(float x, float y, float r, float m);
    void add_force(vec2& force);
    void add_acc(vec2& acc);
    void move(float delta);

    std::vector<float> get_position();
    std::vector<float> get_before_position();
    std::vector<float> get_acceleration();

    vec2 pos;
    float r;

private:
    vec2 pos_before;
    float m;
    vec2 a;
};
#endif
