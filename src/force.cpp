#include "force.hpp"
#include <iostream>


void Force::add(Node* node){
    this->nodes.push_back(node);
}


Charge::Charge(float x, float y, float q){
    this->pos = vec2(x, y);
    this->q = q;
}


Charge::Charge(const Charge& charge){
    this->pos = charge.pos;
    this->q = charge.q;
    this->nodes = charge.nodes;
}


void Charge::interact(){
    for (size_t i = 0; i < this->nodes.size(); i++){
        Node* node = this->nodes[i];
        vec2 node_pos = node->pos;
        vec2 acc = this->q * (this->pos - node_pos).unit();
        node->add_acc(acc);
    }
}


void Friction::interact(){
    for (size_t i = 0; i < this->nodes.size(); i++){
        Node* node = this->nodes[i];
        float norm = (node->v).norm();
        vec2 acc = (-this->mu * norm * norm) * (node->v).unit();
        node->add_acc(acc);
    }
}


Link::Link(Node* node_a, Node* node_b, float q){
    this->node_a = node_a;
    this->node_b = node_b;
    this->q = q;
}


Link::Link(const Link& force){
    this->q = force.q;
    this->node_a = force.node_a;
    this->node_b = force.node_b;
}


void Link::interact(){
    Node* node_a = this->node_a;
    Node* node_b = this->node_b;

    vec2 acc = this->q * (node_b->pos - node_a->pos);
    node_a->add_acc(acc);
    node_b->add_acc(-acc);
}