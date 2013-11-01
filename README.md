cs378_pfp_graph
===============

Graph Visualization using a force based approach.

Implementation of the third project for CS378 Programming for Performance, in
which we create a graph visualizer and an algorithm for creating the graph
visualization. The algorithm used is a force based algorithm using an
attractive spring force and a repulsive charge force. The charge force is
calculated in two ways; the first is the 'naieve' O(n^2) method, the second the
Barnes-Hut O(n*log(n)) approximation.
