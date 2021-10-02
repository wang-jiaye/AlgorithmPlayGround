#include <iostream>
#include <vector>
#include <algorithm>
#include<cstddef>

using namespace std;

#define DIM 4

struct Point {
    int val[DIM];
};

struct RangeNode {
    Point val;
    RangeNode *left, *right, *subTree;
    RangeNode(Point val_): 
        val(val_), 
        left(nullptr), right(nullptr), subTree(nullptr) {}
};


vector<vector<Point>> sortedP(DIM);

// Input. A tree and two values, [x, x'] represent the range.
// Output. The node were the paths to x and x' split, 
// or the leaf where both paths end.
RangeNode* findSplitNode(RangeNode* root, pair<int, int> R, int d) {
    while (root->left != root->right && 
            (R.second <= root->val.val[d] || R.first > root->val.val[d])) {
        if (R.second <= root->val.val[d]) root = root->left;
        else root = root->right;
    }
    return root;
}

// Input. A set P of points in the plane.
// Output. The root of a N-dimensional range tree.
RangeNode* buildNDRangeTree(vector<Point> P, int d=1) {
    if (d >= DIM || !P.size()) 
        return NULL;
    int mid = P.size() / 2;
    RangeNode* node = new RangeNode(P[mid]);

    vector<Point> P1(P.begin(), P.begin() + mid);
    vector<Point> P2(P.begin() + mid + 1, P.end());

    node->left = buildNDRangeTree(P1, d);
    node->right = buildNDRangeTree(P2, d);
    node->subTree = buildNDRangeTree(sortedP[d], d + 1);
    return node;
}

vector<Point> nDRangeQuery(RangeNode* root, vector<pair<int, int>> R, int d=1) {
    vector<Point> ans;
    return ans;
}

int main(int argc, const char* argv[]) {
    /* srand((unsigned int) time (NULL)); */
    int n, i;
    vector<Point> P;
    RangeNode* root;

    n = atoi(argv[1]);
    P.resize(n);

    // Generate n randome DIM dimensional points
    for (i = 0; i < n; ++i) {
        for (int j = 0; j < DIM; ++j) {
            P[i].val[j] = rand() % 1000;
        }
    }

    // Preprocss the points, such that sort the point by each its coordinate.  
    // Finally store each sorted points into sortedP.
    for (i = 0; i < DIM; ++i) {
        vector<Point> temp = P;
        sort(temp.begin(), temp.end(), 
                [i] (const Point &a, const Point &b) {
            return a.val[i] < b.val[i];
        });
        sortedP[i] = (temp);
    }

    root = buildNDRangeTree(sortedP[0]);
}
