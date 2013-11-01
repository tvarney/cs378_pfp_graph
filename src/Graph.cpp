
#include "Graph.hpp"
#include <cfloat>
#include <cmath>
#include <cstdio>
#include <iostream>

using namespace cs378;

GraphNode::GraphNode() : index(0), label("") { }
GraphNode::GraphNode(size_t index, std::string label, Point position) :
    index(index), label(label), position(position)
{ }
GraphNode::~GraphNode() { }

bool GraphNode::add(GraphNode *edgeptr) {
    if(edgeptr == this) {
        return false;
    }
    
    bool add = true;
    for(size_t i = 0; i < edges.size(); ++i) {
        if(edges[i] == edgeptr) {
            add = false;
            break;
        }
    }
    if(add) {
        edges.push_back(edgeptr);
        edgeptr->edges.push_back(this);
    }
    
    return add;
}

Graph::Graph() :
    min_x(FLT_MAX), min_y(FLT_MAX), max_x(-FLT_MAX), max_y(-FLT_MAX)
{ }
Graph::~Graph() { }

double Graph::step(double max_delta, double c, double k, bool approx) {
    /* Calculate charge force */
    if(approx) {
        charge_approx(c);
    }else {
        charge_normal(c);
    }
    
    /* Calculate spring force */
    Vector force;
    for(size_t i = 0; i < nodes.size(); ++i) {
        //nodes[i].force = Vector(0,0);
        for(size_t j = 0; j < nodes[i].edges.size(); ++j) {
            force = (nodes[i].edges[j]->position - nodes[i].position) * k;
            /* Attactive force in the direction of the unit vector, addition */
            nodes[i].force += force;
        }
    }
    
    /* Apply forces */
    double largest = 0.0, next;
    for(size_t i = 0; i < nodes.size(); ++i) {
        next = std::fabs(nodes[i].force.magnitude());
        if(next > max_delta) {
            next = max_delta;
        }
        if(next > largest) {
            largest = next;
        }
        nodes[i].position += nodes[i].force;
    }
    return largest;
}

GraphNode & Graph::add(Point position) {
    char buffer[256];
    size_t len = nodes.size();
    std::sprintf(buffer, "Node %llu", (unsigned long long)len);
    std::string label(buffer);
    nodes.push_back(GraphNode(len, label, position));
    if(position.x < min_x) {
        min_x = position.x;
    }
    if(position.x > max_x) {
        max_x = position.x;
    }
    if(position.y < min_y) {
        min_y = position.y;
    }
    if(position.y > max_y) {
        max_y = position.y;
    }
    return nodes[len];
}

GraphNode & Graph::add(const std::string &label, Point position) {
    size_t len = nodes.size();
    nodes.push_back(GraphNode(len, label, position));
    if(position.x < min_x) {
        min_x = position.x;
    }
    if(position.x > max_x) {
        max_x = position.x;
    }
    if(position.y < min_y) {
        min_y = position.y;
    }
    if(position.y > max_y) {
        max_y = position.y;
    }
    return nodes[len];
}

GraphNode & Graph::get(Point position) {
    GraphNode &closest = nodes[0];
    double next, dist = (closest.position - position).magsquared();
    for(size_t i = 0; i < nodes.size(); ++i) {
        next = (nodes[i].position - position).magsquared();
        if(next < dist) {
            dist = next;
            closest = nodes[i];
        }
    }
    return closest;
}

GraphNode & Graph::get(size_t index) {
    if(index >= nodes.size()) {
        return nodes.back();
    }
    return nodes[index];
}

void Graph::clear() {
    nodes.erase(nodes.begin(), nodes.end());
}
size_t Graph::size() const {
    return nodes.size();
}

const std::vector<GraphNode> & Graph::getNodes() const {
    return nodes;
}

void Graph::charge_approx(double c) {
    charge_normal(c);
}
void Graph::charge_normal(double c) {
    /* Calculate repulsive force */
    Vector unit;
    double r2;
    for(size_t i = 0; i < nodes.size(); ++i) {
        nodes[i].force = Vector(0,0);
        for(size_t j = 0; j < i; ++j) {
            unit = nodes[j].position - nodes[i].position;
            r2 = unit.magsquared();
            unit = unit.normalize();
            /* It pushes away in the unit direction, so subtract */
            nodes[i].force -= (unit * c) / r2;
        }
        for(size_t j = i + 1; j < nodes.size(); ++j) {
            unit = nodes[j].position - nodes[i].position;
            r2 = unit.magsquared();
            unit = unit.normalize();
            /* As above */
            nodes[i].force -= (unit * c) / r2;
        }
    }
}
