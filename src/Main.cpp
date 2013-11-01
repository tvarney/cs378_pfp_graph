
#include "GraphView.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "View.hpp"
#include "Window.hpp"

#include <iostream>

int main(int argc, char **argv) {
    cs354::Window win("Graph View", 800, 600);
    cs354::View::InitViewSystem(&argc, argv, &win);
    cs378::GraphView view;
    cs354::View::EnterMainLoop(view);
    
    /*
    cs378::Vector v1(1.0, -1.0);
    cs378::Vector v2(-1.0, 1.0);
    cs378::Vector v3 = v1 + v2;
    
    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    std::cout << "v3 = v1 + v2 = " << v3 << std::endl;
    v3 += v1;
    std::cout << "(v3 += v1) = " << v3 << std::endl;
    cs378::Vector v4 = v3 * 2;
    std::cout << "v4 = v3 * 2 = " << v4 << std::endl;
    v4 *= 1.5;
    std::cout << "(v4 *= 1.5) = " << v4 << std::endl;
    
    cs378::Point p1(1.0, 1.0);
    cs378::Point p2(4.5, 8.1);
    cs378::Vector direction = p2 - p1;
    std::cout << "p1 = " << p1 << std::endl;
    std::cout << "p2 = " << p2 << std::endl;
    std::cout << "direction = p2 - p1 = " << direction << std::endl;
    */
    return 0;
}
