#include <vector>
#include "node.hpp"
#include "force.hpp"

class Universe {
public:
    Universe(float delta) : delta(delta){}

    void add_nodes(std::vector<Node*> nodes);
    void add_force(Force* force);
    void add_forces(std::vector<Force*> forces);
    void run();
private:
    float delta;
    float max_radius = 0;
    std::vector<Node*> nodes;
    std::vector<Force*> forces;
};
