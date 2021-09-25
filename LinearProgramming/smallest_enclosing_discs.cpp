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
        float x, y, r;

        Disc() {}

        Disc(float x_, float y_, float r_) {
            x = x_, y = y_, r = r_;
        }

        bool isInside(Point p) {
            float dist = sqrt(pow(x - p.x, 2) + pow(y - p.y, 2) * 1.0);
            return dist <= r;
        }
};


/**
 * Make a disc that passes over two points.
 * @params: two Points object
 * @return: a Disc object with center (x,y) and radius
 */
Disc makeDiscWith2Points(Point p1, Point p2) {
    float cx, cy;

    cx = (p1.x + p2.x) * .5;
    cy = (p1.y + p2.y) * .5;
    return Disc(cx, cy, sqrt((p1.x-cx) * (p1.x-cx) + (p1.y-cy) * (p1.y-cy)));
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
    int n, k;
    Disc ans;

    n = pts.size();
    ans = makeDiscWith2Points(q1, q2);

    for (k = 0; k < n; ++k) {
        if (!ans.isInside(pts[k])) 
            ans = makeDiscWith3Point(q1, q2, pts[k]);
    }
    return ans;
}


Disc miniDiscWithPoint(vector<Point> pts, Point q) {
    int n, j;
    Disc ans;

    n = pts.size();
    ans = makeDiscWith2Points(pts[0], q);

    for (j = 1; j < n; ++j) {
        if (!ans.isInside(pts[j])) {
            vector<Point> next(pts.begin(), pts.begin() + j);
            ans = miniDiscWith2Point(pts, pts[j], q);
        } 
    }
    return ans;
}


Disc miniDisc(vector<Point> pts) {
    int n, i;
    Disc ans;

    n = pts.size();
    ans = makeDiscWith2Points(pts[0], pts[1]);

    for (i = 2; i < n; ++i) {
        if (!ans.isInside(pts[i])) {
            vector<Point> next(pts.begin(), pts.begin() + i);
            ans = miniDiscWithPoint(next, pts[i]);
        } 
    }
    return ans;
}


int main(int argc, char *argv[]) {
    srand((unsigned int) time (NULL));
    int n, i;

    n = atoi(argv[1]);
    vector<Point> pts;

    if (n < 2) {
        printf("Error: At least need two points\n");
        exit(1);
    }

    for (i = 0; i < n; ++i) {
        float x = rand() % 100, y = rand() % 100;
        pts.push_back(Point(x, y));
    }

    for (i = 0; i < n; ++i) {
        printf("(%.1f,%.1f)", pts[i].x, pts[i].y);
        if (i != n - 1) 
            printf(",");
    }

    printf("\n");
    Disc ans = miniDisc(pts);
    printf("Disc formula: (x-%.3f)^2+(y-%.3f)^2=%.3f^2\n", ans.x, ans.y, ans.r);

    return 0;
}
