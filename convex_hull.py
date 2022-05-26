#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""Given a set of points P in the plane, compute a list that contains those
points from P that are the vertices of convex hull, listed in clockwise order.
"""

import matplotlib.pyplot as plt
import random


class Point:
    def __init__(self, x, y):
        self._x = x
        self._y = y

    @property
    def x(self):
        return self._x

    @property
    def y(self):
        return self._y


def to_left(p: Point, q: Point, r: Point) -> bool:
    """Test whether a point r lies to the left or to the right of a directed
    line from p to q

    Args:
        p, q, r are Point objects

    Returns:
        True if r lies to the left of the directed line from p to q. False
        otherwise.
    """
    area = p.x * q.y - p.y * q.x + q.x * r.y - q.y * r.x + r.x * p.y - r.y * p.x
    return area > 0


def compute_convex_hull(points: list) -> list:
    """Compute the convex hull CH(P) by given a set of points P
    in O(n log n) time complexity.

    Args:
        points: A list of point objects in the plane

    Returns:
        A list containing the points objects of CH(P) in clockwise order
    """
    sorted_points = sorted(points, key=lambda pt: pt.x)
    upper = [sorted_points[0], sorted_points[1]]
    lower = [sorted_points[-1], sorted_points[-2]]
    n = len(points)

    for i in range(2, n):
        upper.append(sorted_points[i])
        while len(upper) > 2 and not to_left(upper[-3], upper[-2], upper[-1]):
            upper.pop(-2)

    for i in range(n - 3, -1, -1):
        lower.append(sorted_points[i])
        while len(lower) > 2 and not to_left(lower[-3], lower[-2], lower[-1]):
            lower.pop(-2)

    # first and last points from lower are duplicates
    return upper + lower[1: len(lower) - 1]


def main():
    x = random.sample(range(1000), 100)
    y = random.sample(range(1000), 100)

    points = [Point(a, b) for i, (a, b) in enumerate(zip(x, y))]
    hull = compute_convex_hull(points)

    # draw points
    for pt in points:
        plt.plot(pt.x, pt.y, marker='x', color='r')

    for i in range(len(hull)):
        plt.plot((hull[i-1].x, hull[i].x), (hull[i-1].y, hull[i].y), color='b')
    plt.show()


if __name__ == '__main__':
    main()
