#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "node.hpp"
#include "force.hpp"

namespace py = pybind11;


class Universe {
public:
    Universe(float delta, size_t capacity, size_t n_iter) : delta(delta), capacity(capacity), n_iter(n_iter){}

    void add_nodes(std::vector<Node*> nodes);
    void add_force(Force* force);
    void add_forces(std::vector<Force*> forces);
    void run();
    py::array_t<float>* history(size_t iter, size_t steps);

private:
    float delta;
    size_t capacity;
    int n_iter; 
    float max_radius = 0;
    std::vector<Node*> nodes;
    std::vector<Force*> forces;
};
