# Kruskal's Minimum Spanning Tree algorithm on IP nodes - MST-IPs
A C++ Implementation of Kruskal's Minimum Spanning Tree algorithm on IP nodes
## Introduction
Kruskal’s algorithm is the concept that is introduced in the graph theory of discrete mathematics. It is used to discover the shortest path between two points in a connected weighted graph. This algorithm converts a given graph into the forest, considering each node as a separate tree. These trees can only link to each other if the edge connecting them has a low value and doesn’t generate a cycle in MST structure.
## Algorithm
```
* create a forest F (a set of trees), where each vertex in the graph is a separate tree
* create a set S containing all the edges in the graph
* while S is nonempty and F is not yet spanning
  * remove an edge with minimum weight from S
  * if the removed edge connects two different trees then add it to the forest F, combining two trees into a single tree

At the termination of the algorithm, the forest forms a minimum spanning forest of the graph. If the graph is connected, the forest has a single component and forms a minimum spanning tree. 
```
## Pseudocode

The following code is implemented with a disjoint-set data structure. Here, the forest F represented as a set of edges, and use the disjoint-set data structure to efficiently determine whether two vertices are part of the same tree.
```
algorithm Kruskal(G) is
    F:= ∅
    for each v ∈ G.V do
        MAKE-SET(v)
    for each (u, v) in G.E ordered by weight(u, v), increasing do
        if FIND-SET(u) ≠ FIND-SET(v) then
            F:= F ∪ {(u, v)} ∪ {(v, u)}
            UNION(FIND-SET(u), FIND-SET(v))
    return F
```
