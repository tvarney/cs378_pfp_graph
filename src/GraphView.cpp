
#include "GraphView.hpp"
#include "common.hpp"
#include "CircleData.hpp"
#include "Random.hpp"
#include "Point3.hpp"
//#include "Geometry.hpp"

#include <cstdlib>
#include <iostream>

namespace cs378 {
    typedef cs354::Point3f Point3f;
    typedef cs354::Vector3f Vector3f;
    typedef cs354::Matrix<float> Matrixf;
}

using namespace cs378;

const double GraphView::DefaultC = 15000.0;
const double GraphView::DefaultK = 0.005;
const double GraphView::DefaultMinDelta = 0.05;
const double GraphView::DefaultMaxDelta = 25.0;

GraphView::GraphView() :
    force(false), c(GraphView::DefaultC), k(GraphView::DefaultK),
    min_delta(GraphView::DefaultMinDelta),
    max_delta(GraphView::DefaultMaxDelta),
    transform(Matrixf::Identity()), undo(Matrixf::Identity()),
    density(0), grabbed(NULL), enable_mouse(false), draw_lines(true)
{ }
GraphView::~GraphView() { }

void GraphView::display() {
    if(force) {
        double largest = graph.step(max_delta, c, k);
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
    
    const std::vector<GraphNode> &nodes = graph.getNodes();
    
    /* Draw all lines */
    if(draw_lines) {
        glColor3f(0.0, 0.0, 0.7);
        glTranslatef(0,0,0.5);
        glLineWidth(1.0f);
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
    }
    
    glColor3f(1.0, 1.0, 1.0);
    for(size_t i = 0; i < graph.size(); ++i) {
        glPushMatrix();
        glTranslatef(nodes[i].position.x, nodes[i].position.y, 0);
        glScalef(7, 7, 1);
        Circle.draw();
        glPopMatrix();
    }
}

void GraphView::init() {
    /* Add initial nodes to graph */
    force = false;
    c = GraphView::DefaultC;
    k = GraphView::DefaultK;
    min_delta = GraphView::DefaultMinDelta;
    max_delta = GraphView::DefaultMaxDelta;
    transform = Matrixf::Identity();
    undo = Matrixf::Identity();
    density = 0;
    grabbed = NULL;
    
    std::cout << "Charge Force: " << c << std::endl;
    std::cout << "Spring Force: " << k << std::endl;
    std::cout << "Graph Density: " << density << std::endl;
    
    randomize_graph();
    force = false;
}
void GraphView::end() {
    /* Clear graph */
    graph.clear();
}

void GraphView::keyPressed(int ch) {
    double x, y;
    uint32_t tries, edge_id;
    GraphNode *node;
    bool has_edge;
    Point3f mod;
    if(force) {
        switch(ch) {
        case 'q':
        case 'f':
            force = false;
            std::cout << "Stopping force simulation" << std::endl;
            break;
        case 'l':
            draw_lines = !draw_lines;
            break;
        }
        return;
    }
    switch(ch) {
    case 'a':
        x = ((uint32_t)random.nextInt32()) % win.dim.width;
        y = ((uint32_t)random.nextInt32()) % win.dim.height;
        x -= float(win.dim.width) * 0.5f;
        y -= float(win.dim.height) * 0.5f;
        mod = Point3f(x, y, 0);
        mod = undo * mod;
        
        tries = getTries();
        node = &(graph.add(Point(mod.x, mod.y)));
        has_edge = false;
        for(uint32_t i = 0; i < tries; ++i) {
            edge_id = ((uint32_t)random.nextInt32()) % graph.size();
            has_edge |= node->add(&(graph.get(edge_id)));
        }
        /* Guarantee at least 1 edge */
        while(!has_edge) {
            edge_id = ((uint32_t)random.nextInt32()) % graph.size();
            has_edge |= node->add(&graph.get(edge_id));
        }
        View::PostRedisplay();
        break;
    case 'c':
        c *= 1.1;
        std::cout << "Charge Force: " << c << std::endl;
        break;
    case 'C':
        c *= 0.9090909090909091;
        std::cout << "Charge Force: " << c << std::endl;
        break;
    case 'd':
        density = (density + 1) % 5;
        std::cout << "Graph Density: " << density << std::endl;
        randomize_graph();
        View::PostRedisplay();
        break;
    case 'D':
        density -= 1;
        if(density < 0) {
            density = 4;
        }
        std::cout << "Graph Density: " << density << std::endl;
        randomize_graph();
        View::PostRedisplay();
        break;
    case 'f':
        force = true;
        std::cout << "Starting force simulation..." << std::endl;
        View::PostRedisplay();
        break;
    case 'k':
        k *= 1.1;
        std::cout << "Spring Force: " << k << std::endl;
        break;
    case 'K':
        k *= 0.9090909090909091;
        std::cout << "Spring Force: " << k << std::endl;
        break;
    case 'l':
        draw_lines = !draw_lines;
        View::PostRedisplay();
        break;
    case 'n':
        randomize_graph();
        View::PostRedisplay();
        break;
    case 'p':
        std::cout << "Preturbing nodes..." << std::endl;
        for(size_t i = 0; i < graph.size(); ++i) {
            x = double(((uint32_t)random.nextInt32()) % 100) / 49.5f - 1.0f;
            y = double(((uint32_t)random.nextInt32()) % 100) / 49.5f - 1.0f;
            graph.get(i).position += Vector(x, y) * 50.0f;
        }
        View::PostRedisplay();
        break;
    case 'q':
        std::exit(1);
        break;
    case 'r':
        transform = transform.rotate(0.017453292519943295f, cs354::AXIS_Z);
        undo = undo.rotate(-0.017453292519943295f, cs354::AXIS_Z);
        View::PostRedisplay();
        break;
    case 'R':
        transform = transform.rotate(-0.017453292519943295f, cs354::AXIS_Z);
        undo = undo.rotate(0.017453292519943295f, cs354::AXIS_Z);
        View::PostRedisplay();
        break;
    case 's':
        graph.step(max_delta, c, k);
        View::PostRedisplay();
        break;
    case '+':
        transform = transform.scale(1.1, 1.1, 1.0);
        undo = undo.scale(0.9090909090909091,0.9090909090909091,1.0);
        View::PostRedisplay();
        break;
    case '=':
        transform = transform.scale(0.9090909090909091,0.9090909090909091,1.0);
        undo = undo.scale(1.1, 1.1, 1.0);
        View::PostRedisplay();
        break;
    case cs354::KEY_UP:
        transform = transform.translate(0, -5.0f, 0);
        undo = undo.translate(0, 5.0f, 0);
        View::PostRedisplay();
        break;
    case cs354::KEY_DOWN:
        transform = transform.translate(0, 5.0f, 0);
        undo = undo.translate(0, -5.0f, 0);
        View::PostRedisplay();
        break;
    case cs354::KEY_LEFT:
        transform = transform.translate(-5.0, 0, 0);
        undo = undo.translate(5.0, 0, 0);
        View::PostRedisplay();
        break;
    case cs354::KEY_RIGHT:
        transform = transform.translate(5.0, 0, 0);
        undo = undo.translate(-5.0, 0, 0);
        View::PostRedisplay();
        break;
    default:
        break;
    }
}
void GraphView::mousePressed(cs354::MouseButton button,
                             cs354::ButtonState state)
{
    cs354::BasicView::mousePressed(button, state);
    if(force || !enable_mouse) {
        return;
    }
    
    double distsquared;
    Point position(mouse.pos.x, mouse.pos.y);
    Vector mod(float(win.dim.width)*0.5f, float(win.dim.height)*0.5f);
    position -= mod;
    Point3f npos = undo * Point3f(position.x, position.y, 0);
    position = Point(npos.x, npos.y);
    std::cout << "Scaled coordinates: " << position << std::endl;
    
    switch(button) {
    case cs354::MOUSE_BUTTON_LEFT:
        if(state == cs354::BUTTON_DOWN) {
            /* Get closest button */
            grabbed = &(graph.get(position));
            distsquared = (position - grabbed->position).magsquared();
            if(distsquared > 100.0f) {
                std::cout << "Rejecting grab: distsquared = " << distsquared <<
                    std::endl;
                grabbed = NULL;
            }else {
                std::cout << "Grabbed node " << grabbed->index << std::endl;
            }
        }else {
            grabbed = NULL;
        }
        break;
    default:
        break;
    }
}
void GraphView::motion(int x, int y) {
    if(!enable_mouse) {
        return;
    }
    Vector3f vec(x - mouse.pos.x, y - mouse.pos.y, 0);
    vec = undo * vec;
    Vector delta(vec.x, vec.y);
    
    cs354::BasicView::motion(x, y);
    if(grabbed != NULL) {
        std::cout << "Moving node " << grabbed->index << " by " << delta <<
            std::endl;
        
        graph.get(grabbed->index).position += delta;
        View::PostRedisplay();
    }
}

static uint32_t _tries[] = {
    3, 6, 15, 20, 25
};
static uint32_t _num[] = {
    20, 30, 50, 70, 100
};

uint32_t GraphView::getTries() {
    if(density < 0) {
        density = 0;
    }else if(density > 4) {
        density = 4;
    }
    
    return _tries[density];
}
void GraphView::randomize_graph() {
    graph.clear();
    
    uint32_t tries = getTries();
    //uint32_t num = ((uint32_t)random.nextInt32()) % 10 + 5*(density+1);
    uint32_t num = _num[density];
    Point3f adjusted;
    Vector3f window(float(win.dim.width)*0.5f, float(win.dim.height)*0.5f, 0);
    for(uint32_t i = 0; i < num; ++i) {
        adjusted = Point3f(((uint32_t)random.nextInt32()) % win.dim.width,
                           ((uint32_t)random.nextInt32()) % win.dim.height,
                           0.0f);
        adjusted -= window;
        adjusted = undo * adjusted;
        graph.add(Point(adjusted.x, adjusted.y));
    }
    
    GraphNode *node = NULL, *edge = NULL;
    uint32_t edge_id;
    bool has_edge;
    for(uint32_t i = 0; i < graph.size(); ++i) {
        node = &(graph.get(i));
        has_edge = false;
        for(uint32_t j = 0; j < tries; ++j) {
            edge_id = ((uint32_t)random.nextInt32()) % graph.size();
            edge = &(graph.get(edge_id));
            has_edge |= node->add(edge);
        }
        while(!has_edge) {
            edge_id = ((uint32_t)random.nextInt32()) % graph.size();
            edge = &(graph.get(edge_id));
            has_edge |= node->add(edge);
        }
    }
}
