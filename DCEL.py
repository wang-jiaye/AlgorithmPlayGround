#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
from math import sqrt, acos, pi


"""Doubly Connected Edge List (DCEL), a powerful data structure to represent
subdivisions of a plane. It contains a record for each vertex, edge, face, and
the geometric and topological information with additional attributes of the 
subdivision. This powerful data structure will assist us in triangulation, 
Voronoi diagram, etc,...

Definitions:
    Incident: If a vertex is the endpoint of an edge, then we say that the
    vertex and edge are incident. Similarly, a face and an edge on its boundary
    are incident, and a face and a vert4ex of its boundary are incident.

Reference:
    Computational Geometry: Algorithms and Applications. Third edition 29-33
"""


class Vertex:
    """Vertex v stores the coordinates of v in a field. It also stores a list to
    an arbitrary half-edge that has v as its origin"""
    def __init__(self, name, x, y):
        self.x = x
        self.y = y
        self.name = name
        self.incident_edges = []  # list of HalfEdge objects

    def __eq__(self, other):
        if isinstance(other, Vertex):
            return self.x == other.x and self.y == other.y
        return False

    def __str__(self):
        return f'v{self.name}: ({self.x}, {self.y})'

    def __repr__(self):
        return f'v{self.name}: ({self.x}, {self.y})'


class HalfEdge:
    def __init__(self, v: Vertex, w: Vertex):
        self.origin = v  # Vertex object
        self.twin = None  # HalfEdge object
        self.next = None  # HalfEdge object
        self.prev = None  # HalfEdge Object
        self.incident_face = None  # Face object

        self.v = v
        self.w = w

    def __str__(self):
        return f'E(o:({self.v.x},{self.v.y}), d:({self.w.x},{self.w.y}))'

    def __repr__(self):
        return f'E(o:({self.v.x},{self.v.y}), d:({self.w.x},{self.w.y}))'

    def get_distance(self):
        return sqrt((self.v.x - self.w.x) ** 2 + (self.v.y - self.w.y) ** 2)

    def get_angle(self):
        dx = self.v.x - self.w.x
        dy = self.v.y - self.w.y
        dist = sqrt(dx * dx + dy * dy)
        if dy > 0:
            return acos(dx / dist)
        return 2 * pi - acos(dx / dist)


class Face:
    def __init__(self):
        self.name = None
        self.outer_component = None  # some HalfEdge on its outer boundary
        self.inner_component = None  # .. .. .. .. inner ..


class DCEL:
    def __init__(self, nodes: list, edges: list):
        self.vertices_map = {}
        self.half_edges = []
        self.faces = []

        self.__build(nodes, edges)

    def get_vertices(self):
        return list(self.vertices_map.values())

    def get_edges(self):
        return self.half_edges

    def __build(self, points: list, edges: list):
        self.__init_points(points)
        self.__init_edges(edges)
        self.__init_prev_and_next()

    def __init_points(self, points: list):
        for name, x, y in points:
            self.vertices_map[name] = Vertex(name, x, y)

    def __init_edges(self, edges: list):
        for v, w in edges:
            origin = self.vertices_map[v]
            destination = self.vertices_map[w]

            hedge = HalfEdge(origin, destination)
            twin_hedge = HalfEdge(destination, origin)

            hedge.twin = twin_hedge
            twin_hedge.twin = hedge

            self.vertices_map[v].incident_edges.append(hedge)
            self.vertices_map[w].incident_edges.append(twin_hedge)
            self.half_edges.extend([hedge, twin_hedge])

    def __init_prev_and_next(self):
        """Initialize previous and next pointers of each half-edge"""
        for v in self.vertices_map.values():
            hedges = sorted(v.incident_edges
                            , key=lambda e: e.get_angle()
                            , reverse=True)
            n = len(hedges)
            for i in range(n):
                h1, h2 = hedges[i], hedges[(i + 1) % n]
                h1.twin.next = h2
                h2.prev = h1

    def __init_faces(self):
        return

    def display(self):
        for i, vertex in self.vertices_map.items():
            plt.plot(vertex.x, vertex.y, marker='o', color='r')

        for half_edge in self.half_edges:
            x1, y1 = half_edge.origin.x, half_edge.origin.y
            x2, y2 = half_edge.twin.origin.x, half_edge.twin.origin.y
            plt.plot((x1, x2), (y1, y2), color='b')
        plt.show()


def main():
    nodes = [(1, 0, 4), (2, 2, 4), (3, 2, 2), (4, 1, 1)]
    edges = [(1, 2), (2, 3), (3, 1), (3, 4)]
    dcel = DCEL(nodes, edges)
    dcel.display()


if __name__ == '__main__':
    main()