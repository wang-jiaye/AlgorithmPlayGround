#include <iostream>
#include <vector>
#include <algorithm>
#include <cstddef>

using namespace std;


struct Point {
    int x, y;
};

struct KDNode {
    Point pt;
    KDNode *left, *right;
    KDNode(Point pt_): pt(pt_), left(nullptr), right(nullptr) {}
};

bool by_x(const Point &a, const Point &b) {
    return a.x < b.x;
}

bool by_y(const Point &a, const Point &b) {
    return a.y < b.y;
}

KDNode* buildKDTree(vector<Point> P, int depth) {
    if (!P.size()) 
        return NULL;
    if (depth & 1) 
        sort(P.begin(), P.end(), by_y);
    else 
        sort(P.begin(), P.end(), by_x);

    int mid = P.size() / 2;
    KDNode *node = new KDNode(P[mid]);
    vector<Point> P1(P.begin(), P.begin() + mid);
    vector<Point> P2(P.begin() + mid + 1, P.end());
    node->left = buildKDTree(P1, depth + 1);
    node->right = buildKDTree(P2, depth + 1);
    return node;
}

int main() {
    vector<Point> pts = {{7,2},{5,4},{9,6},{4,7},{8,1},{2,3}};
    KDNode *root = buildKDTree(pts, 0);
    printf("Done\n");
}
