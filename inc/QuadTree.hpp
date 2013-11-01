
#ifndef CS378_PROJECT3_QUADTREE_HPP
#define CS378_PROJECT3_QUADTREE_HPP

#include "Graph.hpp"
#include "Point.hpp"
#include "Vector.hpp"

#include <vector>

namespace cs378 {
    struct QuadTreeRegion;
    enum RegionType {
        QUADTREE_REGION,
        QUADTREE_DATAPTR,
    };
    struct RegionData {
        RegionData();
        ~RegionData();
        Point center() const;
        size_t mass() const;
        
        RegionType type;
        union {
            QuadTreeRegion *qtr;
            GraphNode *particle;
        } data;
    };
    struct QuadTreeRegion {
        QuadTreeRegion(Point origin, Vector dim);
        ~QuadTreeRegion();
        void add(GraphNode *particle);
        void process();
        void force(GraphNode *node, double c, double ts);
        
        size_t mass;
        Point origin, center, center_of_mass;
        Vector dim;
        RegionData ul, ur, ll, lr;
    };
    class QuadTree {
    public:
        QuadTree(Point origin, Vector dim);
        ~QuadTree();
        void add(GraphNode *ptr);
        void process();
        
        void force(std::vector<GraphNode> &nodes, double c, double theta);
    protected:
        QuadTreeRegion region;
    };
}

#endif
