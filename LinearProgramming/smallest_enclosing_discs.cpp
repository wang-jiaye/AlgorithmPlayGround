// @Script: smallest_enclosing_discs.cpp
// @Author: Jiaye William Wang
// @Create At: September 23, 2021 13:05:21
// @Description: C++ implementation of the smallest enclosing discs algorithm 
// from chapter 4.7 in de Berg's Computational Geometry: Algorithms and 
// Applications. 

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

class Discs {
    public:
        float x, y, radius;
        Discs() {}
        Discs(float x_, float y_, float radius_) {
            x = x_, y = y_, radius = radius_;
        }

        /**
         * check point p is inside the discs
         * @param: a Point object, p
         * @return: true if p inside the discs, false otherwise
         */
        bool isInside(Point p) {
            float dist = sqrt(pow(x - p.x, 2) + pow(y - p.y, 2) * 1.0);
            return dist <= radius;
        }
};

int n;
vector<Discs> D;

Discs makeDiscWith2Points(Point p1, Point p2) {
    float dx = fabs(p1.x - p2.x), dy = fabs(p1.y - p2.y);
    float radius = sqrt(dx * dx + dy * dy) / 2.0;
    float x = min(p1.x, p2.x) + dx / 2.0, y = min(p1.y, p2.y) + dy / 2.0;
    return Discs(x, y, radius);
}

Discs makeDiscWith3Point (Point p1, Point p2, Point p3) {

}

Discs miniDiscWithPoint(vector<Point> pts, Point q) {
    for (int i = 1; i < n; ++i) {

    }
}

void miniDiscWith2Point(vector<Point> pts, Point q1, Point q2) {
    for (int i = 0; i < n; ++i) {

    }
}


Discs miniDisc(vector<Point> pts) {
    D[1] = makeDiscWith2Points(pts[0], pts[1]);
    for (int i = 2; i < n; ++i) {
        if (D[i-1].isInside(pts[i])) 
            D[i] = D[i-1];
        else {
            auto next = 
            D[i] = miniDiscWithPoint(pts, pts[i]);
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
    miniDisc(pts);
}
