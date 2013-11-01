
#include "GraphView.hpp"
#include "common.hpp"
#include "CircleData.hpp"
#include "Random.hpp"

#include <cstdlib>
#include <iostream>

using namespace cs378;

GraphView::GraphView() :
    force(false), c(15000.0), k(0.005), min_delta(0.1), max_delta(15),
    transform(cs354::Matrix<float>::Identity())
{ }
GraphView::~GraphView() { }

void GraphView::display() {
    if(force) {
        double largest = graph.step(c, k);
        if(largest < min_delta) {
            std::cout << "Largest delta smaller than lower bound, ending force"
                " simulation." << std::endl;
            force = false;
        }
        View::PostRedisplay(); /*< Schedule a new redisplay */
    }
    
    glViewport(0,0,win.dim.width, win.dim.height);
    glEnable(GL_DEPTH_TEST);
    
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    float left, right, top, bottom;
    right = float(win.dim.width) / 2.0f;
    left = -right;
    bottom = float(win.dim.height) / 2.0f;
    top = -bottom;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left, right, bottom, top, -1.0f, 1.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glLoadMatrixf(transform.data);
    //glTranslatef(translate.x, translate.y, 0.0f);
    //glScalef(scale, scale, 1);
    
    const std::vector<GraphNode> &nodes = graph.getNodes();
    
    /* Draw all lines */
    glTranslatef(0,0,0.5);
    glLineWidth(2.0f);
    // #2186D9
    glColor3f(0.13, 0.53, 0.85);
    glBegin(GL_LINES); {
        for(size_t i = 0; i < graph.size(); ++i) {
            for(size_t j = 0; j < nodes[i].edges.size(); ++j) {
                glVertex2f(nodes[i].position.x, nodes[i].position.y);
                glVertex2f(nodes[i].edges[j]->position.x,
                           nodes[i].edges[j]->position.y);
            }
        }
    }glEnd();
    
    glTranslatef(0,0,-0.5);
    // #D97421
    glColor3f(0.85, 0.45, 0.13);
    for(size_t i = 0; i < nodes.size(); ++i) {
        glPushMatrix();
        glTranslatef(nodes[i].position.x, nodes[i].position.y, 0);
        glScalef(7, 7, 1);
        Circle.draw();
        glPopMatrix();
    }
}

void GraphView::init() {
    /* Add initial nodes to graph */
    randomize_graph();
    force = false;
}
void GraphView::end() {
    /* Clear graph */
    graph.clear();
}

void GraphView::keyPressed(int ch) {
    if(force) {
        force = (ch != 'f');
        return;
    }
    switch(ch) {
    case '+':
        transform = transform.scale(1.1, 1.1, 1.0);
        View::PostRedisplay();
        break;
    case '=':
        transform = transform.scale(0.9090909090909091,0.9090909090909091,1.0);
        View::PostRedisplay();
        break;
    case 'f':
        force = !force;
        View::PostRedisplay();
        break;
    case 'n':
        randomize_graph();
        View::PostRedisplay();
        break;
    case 'r':
        transform = transform.rotate(0.017453292519943295f, cs354::AXIS_Z);
        View::PostRedisplay();
        break;
    case 'R':
        transform = transform.rotate(-0.017453292519943295f, cs354::AXIS_Z);
        View::PostRedisplay();
        break;
    case 's':
        graph.step(c, k);
        View::PostRedisplay();
        break;
    case cs354::KEY_UP:
        transform = transform.translate(0, -5.0f, 0);
        View::PostRedisplay();
        break;
    case cs354::KEY_DOWN:
        transform = transform.translate(0, 5.0f, 0);
        View::PostRedisplay();
        break;
    case cs354::KEY_LEFT:
        transform = transform.translate(-5.0, 0, 0);
        View::PostRedisplay();
        break;
    case cs354::KEY_RIGHT:
        transform = transform.translate(5.0, 0, 0);
        View::PostRedisplay();
        break;
    case 'q':
        std::exit(1);
        break;
    default:
        break;
    }
}
void GraphView::mousePressed(cs354::MouseButton button,
                             cs354::ButtonState state)
{
    cs354::BasicView::mousePressed(button, state);
    
}
void GraphView::motion(int x, int y) {
    cs354::BasicView::motion(x, y);
}

static GraphNode _GN_none;

void GraphView::randomize_graph() {
    RandomLCG random;
    graph.clear();
    
    float half_width = float(win.dim.width) * 0.5f;
    float half_height = float(win.dim.height) * 0.5f;
    
    uint32_t num = ((uint32_t)random.nextInt32()) % 15 + 10;
    uint32_t tries = ((uint32_t)random.nextInt32()) % 5 + 2;
    float x, y;
    for(uint32_t i = 0; i < num; ++i) {
        y = ((uint32_t)random.nextInt32()) % win.dim.height - half_height;
        x = ((uint32_t)random.nextInt32()) % win.dim.width - half_width;
        graph.add(Point(x, y));
    }
    
    GraphNode *node = NULL, *edge = NULL;
    uint32_t edge_id;
    bool add;
    for(uint32_t i = 0; i < graph.size(); ++i) {
        node = &(graph.get(i));
        for(uint32_t j = 0; j < tries; ++j) {
            edge_id = ((uint32_t)random.nextInt32()) % graph.size();
            edge = &(graph.get(edge_id));
            add = true;
            for(size_t k = 0; k < node->edges.size(); ++k) {
                if(node->edges[k] == edge) {
                    add = false;
                    break;
                }
            }
            
            if(add) {
                node->edges.push_back(edge);
                edge->edges.push_back(node);
            }
        }
    }
}
