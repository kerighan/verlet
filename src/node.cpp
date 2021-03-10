#include "node.hpp"
#include <vector>
#include <iostream>


Node::Node(float x, float y, float r, float m){
    this->pos = vec2(x, y);
    this->pos_before = vec2(x, y);
    this->a = vec2(0, 0);
    this->r = r;
    this->m = m;
}

void Node::add_force(vec2& force){
    this->a += force * (1/this->m);
}

void Node::add_acc(vec2& acc){
    this->a += acc;
}

std::vector<float> Node::get_acceleration(){
    std::vector<float> acc(2);
    acc[0] = this->a.x;
    acc[1] = this->a.y;
    return acc;
}

std::vector<float> Node::get_position(){
    std::vector<float> p(2);
    p[0] = this->pos.x;
    p[1] = this->pos.y;
    return p;
}

std::vector<float> Node::get_before_position(){
    std::vector<float> p(2);
    p[0] = this->pos_before.x;
    p[1] = this->pos_before.y;
    return p;
}

void Node::move(float delta){
    vec2 new_pos(0, 0);
    new_pos = (2. * this->pos) - this->pos_before + delta * delta * this->a;
    this->pos_before = this->pos;
    this->pos = new_pos;

    // clear forces
    this->a.x = 0;
    this->a.y = 0;
}