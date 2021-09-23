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
            x = x_;
            y = y_;
        }
};

class Discs {
    public:
    float x, y, radius;
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

Discs makeDiscWith2Point(Point p1, Point p2) {
    float dx = fabs(p1.x - p2.x), dy = fabs(p1.y - p2.y);
    float radius = sqrt(dx * dx + dy * dy) / 2.0;
    float x = min(p1.x, p2.x) + dx / 2.0, y = min(p1.y, p2.y) + dy / 2.0;
    return Discs(x, y, radius);
}


void miniDisc(vector<Point> pts) {
    int n = pts.size();
    for (int i = 1; i < n; ++i) {

    }
}

void miniDiscWithPoint(vector<Point> pts, Point q) {
    int n = pts.size();
    for (int i = 1; i < n; ++i) {

    }
}

void miniDiscWith2Point(vector<Point> pts, Point q1, Point q2) {
    int n = pts.size();
    for (int i = 0; i < n; ++i) {

    }
}

int main() {
    int n = 5;
    vector<Point> pts;
    srand((unsigned int) time (NULL));

    for (int i = 0; i < n; ++i) {
        float x = rand() % 100, y = rand() % 100;
        pts.push_back(Point(x, y));
    }
    Discs d = Discs(58.5, 62, 35.0036);
    cout << d.isInside(Point(83,87)) << endl;
}
