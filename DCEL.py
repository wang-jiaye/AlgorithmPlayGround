#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
from math import sqrt, acos, pi


"""Doubly Connected Edge List (DCEL), a powerful data structure to represent
subdivisions of a plane. It contains a record for each vertex, edge, face, and
the geometric and topological information with additional attributes of the 
subdivision. This powerful data structure will assist us in triangulation, 
Voronoi diagram, trapezoidal map, etc,...

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

    def __eq__(self, other):
        return self.v is other.origin and self.w is other.twin.origin

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
        self.outer_component = []  # some HalfEdge on its outer boundary
        self.inner_component = []  # .. .. .. .. inner ..

    def __repr__(self):
        return f'f{self.name}'

    def __str__(self):
        return f'f{self.name}'


class BoundingBox(Face):
    """Container of our DCEL. Itself is a Face, too."""
    def __init__(self, ul: Vertex, dl: Vertex, ur: Vertex, dr: Vertex):
        super().__init__()
        self.name = "Bounding Box"
        self.ul = ul
        self.dl = dl
        self.ur = ur
        self.dr = dr

        self.left_seg = self.right_seg = self.up_seg = self.down_seg = None

    def __init_seg(self, v: Vertex, w: Vertex):
        hedge = HalfEdge(v, w)
        twin_hedge = HalfEdge(w, v)
        hedge.twin = twin_hedge
        twin_hedge.twin = hedge

    @property
    def vertices(self):
        return [self.ul, self.dl, self.ur, self.dr]

    @property
    def segments(self):
        return [self.left_seg, self.right_seg, self.up_seg, self.down_seg]


class DCEL:
    def __init__(self, nodes: list, edges: list):
        self.vertices_map = {}
        self.half_edges = []
        self.faces = []
        self.bounding_box = None

        self.__build(nodes, edges)

    def get_vertices(self):
        return list(self.vertices_map.values())

    def get_edges(self):
        return self.half_edges

    def __build(self, points: list, edges: list):
        self.__init_points(points)
        self.__init_edges(edges)
        self.__init_prev_and_next()
        self.__init_bounding_box()
        self.__init_faces()

    def __init_bounding_box(self):
        min_x, max_x = float('inf'), float('-inf')
        min_y, max_y = float('inf'), float('-inf')
        for v in self.vertices_map.values():
            min_x, min_y = min(min_x, v.x), min(min_y, v.y)
            max_x, max_y = max(max_x, v.x), max(max_y, v.y)

        self.bounding_box = BoundingBox(
            Vertex('ul', min_x - 1, max_y + 1)
            , Vertex('ll', min_x - 1, min_y - 1)
            , Vertex('ur', max_x + 1, max_y + 1)
            , Vertex('lr', max_x + 1, min_y - 1)
        )

    def __init_points(self, points: list):
        """Convert each coordinate into a Vertex object"""
        for name, x, y in points:
            self.vertices_map[name] = Vertex(name, x, y)

    def __init_edges(self, edges: list):
        """Split each edge into a half-edge and its twin"""
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
            # sort the half-edges in clockwise order.
            hedges = sorted(v.incident_edges
                            , key=lambda e: e.get_angle()
                            , reverse=True)
            n = len(hedges)
            for i in range(n):
                x, y = hedges[i], hedges[(i + 1) % n]
                x.twin.next = y
                y.prev = x

    def __init_faces(self):
        face_label = 1  # 0 is the outer component
        for hedge in self.half_edges:
            if not hedge.incident_face:
                face = Face()
                face.name = face_label
                self.faces.append(face)

                hedge.incident_face = face
                temp = hedge
                while not temp.next == hedge:
                    temp.incident_face = face
                    temp = temp.next
                face_label += 1
            # print(hedge, hedge.incident_face)

    def display(self):
        for i, vertex in self.vertices_map.items():
            plt.plot(vertex.x, vertex.y, marker='o', color='r')

        for bv in self.bounding_box.vertices:
            plt.plot(bv.x, bv.y, marker='x', color='g')

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
