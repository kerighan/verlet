#ifndef __NODEH__
#define __NODEH__
#include "vec.hpp"
#include <vector>


class Node {
public:
    Node(float x, float y, float r, float m, float friction);
    void add_force(const vec2& force);
    void add_acc(const vec2& acc);
    void move(float delta);

    std::vector<float> get_position();
    std::vector<float> get_velocity();
    std::vector<float> get_before_position();
    std::vector<float> get_acceleration();
    float get_radius();

    vec2 pos;
    vec2 v;
    vec2 a;
    float r;
    float m;

private:
    vec2 pos_before;
    vec2 v_before;
    float friction;
};
#endif
