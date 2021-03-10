#include "universe.hpp"


void Universe::add_nodes(std::vector<Node*> nodes){
    for (size_t i = 0; i < nodes.size(); i++){
        this->nodes.push_back(nodes[i]);
        if (nodes[i]->r > this->max_radius)
            this->max_radius = nodes[i]->r;
    }
}


void Universe::add_forces(std::vector<Force*> forces){
    for (size_t i = 0; i < forces.size(); i++){
        this->forces.push_back(forces[i]);
    }
}

void Universe::add_force(Force* force){
    this->forces.push_back(force);
}

void Universe::run(){
    for (size_t i = 0; i < this->forces.size(); i++){
        this->forces[i]->interact();
    }
    for (size_t i = 0; i < this->nodes.size(); i++){
        this->nodes[i]->move(this->delta);
    }
}