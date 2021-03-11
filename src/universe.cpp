#include "universe.hpp"
#include "quadtree.h"
#include <iostream>


namespace py = pybind11;


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

    // update node positions and store them into a numpy matrix for collision
    py::array_t<float> _positions({(int)this->nodes.size(), 2});
    py::buffer_info positionsBuf = _positions.request();
    float *positions = (float *) positionsBuf.ptr;

    float x_min = INFINITY;
    float x_max = -INFINITY;
    float y_min = INFINITY;
    float y_max = -INFINITY;
    for (size_t i = 0; i < this->nodes.size(); i++){
        Node* node = this->nodes[i];
        node->move(this->delta);

        vec2 pos = node->pos;
        if (pos.x < x_min)
            x_min = pos.x;
        if (pos.x > x_max)
            x_max = pos.x;
        if (pos.y < y_min)
            y_min = pos.y;
        if (pos.y > y_max)
            y_max = pos.y;
        positions[2 * i] = pos.x;
        positions[2 * i + 1] = pos.y;
    }

    // create quadtree and manage collisions
    for (size_t iter = 0; iter < this->n_iter; iter++){
        Quadtree qt = Quadtree(x_min, y_min, (x_max - x_min), (y_max - y_min), 4);
        qt.insert(_positions);
        for (size_t i = 0; i < this->nodes.size(); i++){
            Node* node = this->nodes[i];
            vec2 pos = node->pos;
            float delta = node->r + this->max_radius;
            std::vector<size_t> select = qt.select(pos.x - delta, pos.y - delta, 2 * delta, 2 * delta);
            for (auto& j : select){
                if (j == i)
                    continue;
                
                Node* target = this->nodes[j];
                // if two nodes collide
                vec2 separation = target->pos - node->pos;
                float norm = separation.norm();
                if (norm > node->r + target->r)
                    continue;
                
                float amount = node->r + target->r - norm;
                separation = separation.unit();
                float m_src = node->m;
                float m_tgt = target->m;
                float M = m_src + m_tgt;
                target->pos += (m_src * amount / M) * separation;
                node->pos += (-m_tgt * amount / M) * separation;

                // annihilate velocities
                node->v = vec2(0, 0);
                target->v = vec2(0, 0);
            }
        }

        // collisions with boundaries
        for (size_t i = 0; i < this->nodes.size(); i++){
            Node* node = this->nodes[i];
            vec2 pos = node->pos;
            float r = node->r;
            if (pos.x < r){
                pos.x = r;
                node->v = vec2(0, 0);
            }
            else if (pos.x > 100 - r){
                pos.x = 100 - r;
            }
            if (pos.y < r){
                pos.y = r;
                node->v = vec2(0, 0);
            }
            else if (pos.y > 100 - r){
                pos.y = 100 - r;
                node->v = vec2(0, 0);
            }
            node->pos = pos;
        }
    }
}


py::array_t<float>* Universe::history(size_t iter, size_t steps){
    size_t n_nodes = this->nodes.size();

    py::array_t<float>* _positions = new py::array_t<float>({iter, n_nodes, (size_t)2});
    py::buffer_info positionsBuf = _positions->request();
    float *positions = (float *) positionsBuf.ptr;

    for (size_t i = 0; i < iter; i++){
        for (size_t s = 0; s < steps; s++)
            this->run();

        size_t shift = i * n_nodes * 2;
        for (size_t j = 0; j < n_nodes; j++){
            vec2 pos = this->nodes[j]->pos;
            positions[shift + 2*j] = pos.x;
            positions[shift + 2*j + 1] = pos.y;
        }
    }
    return _positions;
}