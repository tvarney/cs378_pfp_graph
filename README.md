cs378_pfp_graph
===============

Graph Visualization using a force based approach.

Implementation of the third project for CS378 Programming for Performance, in
which we create a graph visualizer and an algorithm for creating the graph
visualization. The algorithm used is a force based algorithm using an
attractive spring force and a repulsive charge force. The charge force is
calculated in two ways; the first is the 'naieve' O(n^2) method, the second the
Barnes-Hut O(n*log(n)) approximation.

Key Bindings
============
 * 'c' -> Increase repulsive charge force.
 * 'C' -> Decrease repulsive charge force.
 * 'f' -> Start force simulation. All other keybindings are ignored until done.
 * 'k' -> Increase attractive spring force.
 * 'K' -> Decrease attractive spring force.
 * 'n' -> Create a new graph.
 * 'q' -> Quit the program.
 * 'r' -> Rotate the graph 1 degree clockwise.
 * 'R' -> Rotate the graph 1 degree counter-clockwise.
 * 's' -> Perform one step of the force simulation.
 * '=' -> Decrease visualization scale (zoom out).
 * '+' -> Increase visualization scale (zoom in).
 * Left Arrow  -> Translate the view left.
 * Right Arrow -> Translate the view right.
 * Up Arrow    -> Translate the view up.
 * Down Arrow  -> Translate the view down.
