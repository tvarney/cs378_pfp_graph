
#ifndef CS378_PROJECT3_GRAPH_VIEW_HPP
#define CS378_PROJECT3_GRAPH_VIEW_HPP

#include "Graph.hpp"
#include "Matrix.hpp"
#include "View.hpp"

namespace cs378 {
    class GraphView : public cs354::BasicView {
    public:
        GraphView();
        ~GraphView();
        
        void display();
        void init();
        void end();
        
        void keyPressed(int ch);
        void mousePressed(cs354::MouseButton button, cs354::ButtonState state);
        void motion(int x, int y);
    protected:
        void randomize_graph();
        
        bool force;
        double c, k;
        double min_delta, max_delta;
        cs354::Matrix<float> transform;
        int mouse_mode;
        Graph graph;
    };
}

#endif
