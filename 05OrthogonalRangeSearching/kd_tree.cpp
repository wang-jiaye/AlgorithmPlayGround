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

// Sort points by x-axis
bool by_x(const Point &a, const Point &b) {
    return a.x < b.x;
}

// Sort points by y-axis
bool by_y(const Point &a, const Point &b) {
    return a.y < b.y;
}

KDNode* buildKDTree(vector<Point> P, int depth) {
    if (!P.size()) return NULL;

    if (depth & 1) sort(P.begin(), P.end(), by_y); // horizontal split
    else sort(P.begin(), P.end(), by_x);  // vertical split

    /* The textbook store the line of splitter as internal node, point as 
     * leaf nodes. This is unnecessary if you think about how the tree is 
     * built and the property of each node's left and right subtree. */
    int mid = P.size() / 2;
    KDNode *node = new KDNode(P[mid]);
    vector<Point> P1(P.begin(), P.begin() + mid);
    vector<Point> P2(P.begin() + mid + 1, P.end());
    node->left = buildKDTree(P1, depth + 1);
    node->right = buildKDTree(P2, depth + 1);
    return node;
}

// R consists of two points which are the diagonal of a rectangle.
vector<Point> searchKDTree(KDNode* root, pair<Point, Point> R, int depth=0) {
    int splitValue, min, max;
    if (!root) 
        return {};
    if (depth & 1) {
        splitValue = root->pt.y;
        min = R.first.y, max = R.second.y;
    } else {
        splitValue = root->pt.x;
        min = R.first.x, max = R.second.x;
    }

    if (splitValue < min)
        return searchKDTree(root->right, R, depth + 1);
    else if (max < splitValue) 
        return searchKDTree(root->left, R, depth + 1);
    else {
        // in-range elements could exist in both subtree
        vector<Point> l, r;
        l = searchKDTree(root->left, R, depth + 1);
        r = searchKDTree(root->right, R, depth + 1);
        l.insert(l.end(), r.begin(), r.end());
        // both coordinate of root are in range
        if (root->pt.x >= R.first.x && root->pt.x <= R.second.x && 
                root->pt.y >= R.first.y && root->pt.y <= R.second.y) {
            l.push_back(root->pt);
        }
        return l;
    }
}


int main() {
    vector<Point> pts, ans;
    pair<Point, Point> R;
    KDNode *root;

    pts = {{7,2},{5,4},{9,6},{4,7},{8,1},{2,3}};
    R = {{1,0},{8,5}};

    
    root = buildKDTree(pts, 0);
    ans = searchKDTree(root, R);

    for (auto a: ans)
        cout << a.x << " " << a.y << endl;

    printf("Done\n");
}
