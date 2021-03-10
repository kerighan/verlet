#ifndef __FORCEH__
#define __FORCEH__

#include <vector>
#include "vec.hpp"
#include "node.hpp"


class Force {
public:
    Force(){};
    virtual Force* clone(){ return new Force(); }
    virtual void interact(){}
    std::vector<Node*> nodes;
};


class Charge : public Force {
public:
    Charge(float x, float y, float q);
    Charge(const Charge& charge);
    Charge* clone() override{ return new Charge(*this); }

    void add(Node* node);
    void interact() override;

private:
    float q;
    vec2 pos;
};

#endif