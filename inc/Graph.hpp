
#ifndef CS378_PROJECT3_GRAPH_HPP
#define CS378_PROJECT3_GRAPH_HPP

#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

#include "Point.hpp"
#include "Vector.hpp"

namespace cs378 {
    struct GraphNode {
        GraphNode();
        GraphNode(size_t index, std::string label, Point position);
        ~GraphNode();
        
        bool add(GraphNode *edgeptr);
        
        size_t index;
        std::string label;
        Point position;
        Vector force;
        std::vector<GraphNode *> edges;
    };
    
    class Graph {
    public:
        Graph();
        ~Graph();
        double step(double max_delta, double c, double k, bool approx = false);
        
        GraphNode & add(Point position = Point::Origin);
        GraphNode & add(const std::string &label, Point position);
        GraphNode & get(Point position);
        GraphNode & get(size_t index = ((size_t)(-1)));
        void clear();
        size_t size() const;
        
        const std::vector<GraphNode> & getNodes() const;
    protected:
        void charge_approx(double c);
        void charge_normal(double c); 
        std::vector<GraphNode> nodes;
        float min_x, min_y, max_x, max_y;
    };
}

#endif
