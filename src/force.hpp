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

    void add(Node* node);
    std::vector<Node*> nodes;
};


class Charge : public Force {
public:
    Charge(float x, float y, float q);
    Charge(const Charge& charge);
    Charge* clone() override{ return new Charge(*this); }

    void interact() override;

private:
    float q;
    vec2 pos;
};


class Friction : public Force {
public:
    Friction(float mu) : mu(mu){};
    void interact() override;

private:
    float mu;
};


class Link : public Force {
public:
    Link(Node* node_a, Node* node_b, float q);
    Link(const Link& force);
    Link* clone() override{ return new Link(*this); }

    void interact() override;

private:
    float q;
    Node* node_a;
    Node* node_b;
};


#endif