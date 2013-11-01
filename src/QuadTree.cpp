
#include "QuadTree.hpp"
#include <cmath>

using namespace cs378;

RegionData::RegionData() :
    type(cs378::QUADTREE_DATAPTR)
{
    data.particle = NULL;
}
RegionData::~RegionData() {
    if(type == QUADTREE_REGION) {
        delete data.qtr;
    }
}

Point RegionData::center() const {
    if(type == QUADTREE_REGION) {
        return data.qtr->center_of_mass;
    }
    return (data.particle != NULL) ? data.particle->position : Point(0,0);
}
size_t RegionData::mass() const {
    if(type == QUADTREE_REGION) {
        return data.qtr->mass;
    }
    return (data.particle != NULL) ? 1 : 0;
}

QuadTreeRegion::QuadTreeRegion(Point origin, Vector dim) :
    origin(origin), center(origin + dim * 0.5f), dim(dim)
{ }
QuadTreeRegion::~QuadTreeRegion() { }

/**
 *       |
 * (-,-) | (+,-)
 * ------|------
 * (-,+) | (+,+)
 *       |
 * 
 * ul, ur
 * ll, lr
 */
void QuadTreeRegion::add(GraphNode *particle) {
    Point pos = particle->position;
    Vector diff = pos - center;
    Vector half = dim * 0.5f;
    GraphNode *temp;
    if(diff.x > 0.0f) {
        if(diff.y > 0.0f) {
            /* (+, +) -> lr */
            if(lr.type == QUADTREE_DATAPTR) {
                if(lr.data.particle == NULL) {
                    lr.data.particle = particle;
                }else {
                    temp = lr.data.particle;
                    lr.data.qtr = new QuadTreeRegion(center, half);
                    lr.data.qtr->add(temp);
                    lr.data.qtr->add(particle);
                }
            }else {
                lr.data.qtr->add(particle);
            }
        }else {
            /* (+, -) -> ur */
            if(ur.type == QUADTREE_DATAPTR) {
                if(ur.data.particle == NULL) {
                    ur.data.particle = particle;
                }else {
                    temp = ur.data.particle;
                    ur.data.qtr = new QuadTreeRegion(Point(center.x, origin.y),
                                                     half);
                    ur.data.qtr->add(temp);
                    ur.data.qtr->add(particle);
                }
            }else {
                ur.data.qtr->add(particle);
            }
        }
    }else {
        if(diff.y > 0.0f) {
            /* (-, +) -> ll */
            if(ll.type == QUADTREE_DATAPTR) {
                if(ll.data.particle == NULL) {
                    ll.data.particle = particle;
                }else {
                    temp = ll.data.particle;
                    ll.data.qtr = new QuadTreeRegion(origin, half);
                    ll.data.qtr->add(temp);
                    ll.data.qtr->add(particle);
                }
            }else {
                ur.data.qtr->add(particle);
            }
        }else {
            /* (-, -) -> ul */
            if(ul.type == QUADTREE_DATAPTR) {
                if(ul.data.particle == NULL) {
                    ul.data.particle = particle;
                }else {
                    /* Check if positions are equal here */
                    temp = ul.data.particle;
                    ll.data.qtr = new QuadTreeRegion(origin, half);
                    ll.data.qtr->add(temp);
                    ll.data.qtr->add(particle);
                }
            }else {
                ul.data.qtr->add(particle);
            }
        }
    }
}

void QuadTreeRegion::process() {
    if(ul.type == QUADTREE_REGION) {
        ul.data.qtr->process();
    }
    if(ur.type == QUADTREE_REGION) {
        ur.data.qtr->process();
    }
    if(ll.type == QUADTREE_REGION) {
        ll.data.qtr->process();
    }
    if(lr.type == QUADTREE_REGION) {
        lr.data.qtr->process();
    }
    mass = ul.mass() + ur.mass() + ll.mass() + lr.mass();
    float div = 0.0f;
    center_of_mass = Point(0,0);
    if(ul.data.particle != NULL) {
        div += 1.0f;
        center_of_mass += (ul.center() - center);
    }
    if(ur.data.particle != NULL) {
        div += 1.0f;
        center_of_mass += (ur.center() - center);
    }
    if(ll.data.particle != NULL) {
        div += 1.0f;
        center_of_mass += (ll.center() - center);
    }
    if(lr.data.particle != NULL) {
        div += 1.0f;
        center_of_mass += (lr.center() - center);
    }
    
    if(div == 0.0f) {
        center_of_mass = center;
    }else {
        center_of_mass.x /= div;
        center_of_mass.y /= div;
    }
}
void QuadTreeRegion::force(GraphNode *node, double c, double ts) {
    Vector diff = (center_of_mass - node->position);
    float magsquared = diff.magsquared();
    if(magsquared > ts) {
        /* Make unit */
        diff /= std::sqrt(magsquared);
        node->force -= float(mass) * ((diff * c) / magsquared);
    }else {
        
    }
}

QuadTree::QuadTree(Point origin, Vector dim) :
    region(origin, dim)
{ }
QuadTree::~QuadTree() { }

void QuadTree::add(GraphNode *ptr) {
    region.add(ptr);
}
void QuadTree::process() {
    region.process();
}

void QuadTree::force(std::vector<GraphNode> &nodes, double c, double theta) {
    theta *= theta;
    for(size_t i = 0; i < nodes.size(); ++i) {
        region.force(&(nodes[i]), c, theta);
    }
}
