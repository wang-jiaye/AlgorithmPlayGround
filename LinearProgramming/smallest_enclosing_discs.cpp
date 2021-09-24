// @Script: smallest_enclosing_discs.cpp
// @Author: Jiaye William Wang
// @Create At: September 23, 2021 13:05:21
// @Description: C++ implementation of the smallest enclosing discs algorithm 
// from chapter 4.7 in de Berg's Computational Geometry: Algorithms and Applications. 

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <math.h>


using namespace std;

class Point {
    public:
        float x, y;
        
        Point(float x_, float y_) {
            x = x_, y = y_;
        }
};

class Disc {
    public:
        float x, y, radius;

        Disc() {}

        Disc(float x_, float y_, float radius_) {
            x = x_, y = y_, radius = radius_;
        }

        bool isInside(Point p) {
            float dist = sqrt(pow(x - p.x, 2) + pow(y - p.y, 2) * 1.0);
            return dist <= radius;
        }
};

int n;
vector<Disc> D;

/**
 * Make a disc that passes over two points.
 * @params: two Points object
 * @return: a Disc object with center (x,y) and radius
 */
Disc makeDiscWith2Points(Point p1, Point p2) {
    float dx, dy, x, y, r;

    dx = fabs(p1.x - p2.x);
    dy = fabs(p1.y - p2.y);
    x = min(p1.x, p2.x) + dx / 2.0;
    y = min(p1.y, p2.y) + dy / 2.0;
    r = sqrt(dx * dx + dy * dy) / 2.0;
    return Disc(x, y, r);
}

/**
 * Make a disc that passes over three points. 
 * Reference: http://paulbourke.net/geometry/circlesphere/
 * @params: three Point object
 * @return: a Disc object with center (x,y) and radius
 */
Disc makeDiscWith3Point (Point p1, Point p2, Point p3) {
    float ma, mb, x, y, r;
    float x1, y1, x2, y2, x3, y3;

    x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y, x3 = p3.x, y3 = p3.y;

    ma = (y2 - y1) / (x2 - x1);
    mb = (y3 - y2) / (x3 - x2);
    x = (ma * mb * (y1 - y3) + mb * (x1 + x2) - ma * (x2 + x3)) / (2 * (mb - ma));
    y = -(x - (p1.x + p2.x) / 2) / ma + (p1.y + p2.y) / 2;
    r = sqrt(pow(x - x1, 2) + pow(y - y1, 2) * 1.0);
    return Disc(x, y, r);
}


Disc miniDiscWith2Point(vector<Point> pts, Point q1, Point q2) {
    D[0] = makeDiscWith2Points(q1, q2);
    for (int i = 0; i < n; ++i) {
        if (D[i].isInside(pts[i])) {
            D[i+1] = D[i];
        } else {
            D[i+1] = makeDiscWith3Point(q1, q2, pts[i]);
        }
    }
    return D[n-1];
}

Disc miniDiscWithPoint(vector<Point> pts, Point q) {
    D[0] = makeDiscWith2Points(pts[0], q);
    for (int i = 1; i < n; ++i) {
        if (D[i-1].isInside(pts[i])) 
            D[i] = D[i-1];
        else {
            vector<Point> next(pts.begin(), pts.end() + i);
            D[i] = miniDiscWith2Point(next, pts[i], q);
        }
    }
    return D[n-1];
}


Disc miniDisc(vector<Point> pts) {
    D[1] = makeDiscWith2Points(pts[0], pts[1]);
    for (int i = 2; i < n; ++i) {
        if (D[i-1].isInside(pts[i])) 
            D[i] = D[i-1];
        else {
            vector<Point> next(pts.begin(), pts.begin() + i);
            D[i] = miniDiscWithPoint(next, pts[i]);
        }
    }
    return D[n-1];
}


int main(int argc, char *argv[]) {
    srand((unsigned int) time (NULL));

    n = atoi(argv[1]);
    vector<Point> pts;
    D.resize(n);

    for (int i = 0; i < n; ++i) {
        float x = rand() % 100, y = rand() % 100;
        pts.push_back(Point(x, y));
    }

    for (int i = 0; i < n; ++i) 
        printf("(%.1f,%.1f),", pts[i].x, pts[i].y);
    printf("\n");
    Disc ans = miniDisc(pts);
    printf("Disc center: (%.3f, %.3f). Radius: %.3f\n", ans.x, ans.y, ans.radius);

    cout << "Done :)\n";
}

