
#include "Graph.hpp"
#include <cmath>
#include <cstdio>
#include <iostream>

using namespace cs378;

/*
enum QuadTreeNodeType {
    QUADTREE_BRANCH,
    QUADTREE_LEAF,
};
struct QuadTreeNode {
    QuadTreeNodeType type;
};
struct QuadTreeBranch : public QuadTreeNode {
    QuadTreeBranch(QuadTreeLeaf &leaf);
    ~QuadTreeBranch();
    
    Point center
    QuadTreeNode *children[4];
};

struct QuadTree {
    QuadTree(std::vector<GraphNode> &nodes, size_t partition);
    ~QuadTree();
    
};
*/

GraphNode::GraphNode() : index(0), label("") { }
GraphNode::GraphNode(size_t index, std::string label, Point position) :
    index(index), label(label), position(position)
{ }
GraphNode::~GraphNode() { }

Graph::Graph() { }
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
    return nodes[len];
}

GraphNode & Graph::add(const std::string &label, Point position) {
    size_t len = nodes.size();
    nodes.push_back(GraphNode(len, label, position));
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
