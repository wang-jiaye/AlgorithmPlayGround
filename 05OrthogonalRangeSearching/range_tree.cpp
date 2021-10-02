#include <iostream>
#include <vector>
#include <algorithm>
#include<cstddef>

using namespace std;

#define DIM 10

struct Point {
    int val[DIM];
};

struct RangeNode {
    Point val;
    RangeNode *left, *right, *assoc;
    RangeNode(Point val_): 
        val(val_), 
        left(nullptr), right(nullptr), assoc(nullptr) {}
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

    sort(P.begin(), P.end(), [d](const Point &a, const Point &b) {
        return a.val[d] < b.val[d];
    });
    node->assoc = buildNDRangeTree(P, d + 1);
    return node;
}

// Input. A N-dimensional range tree and a range R.
// Output. All points in the tree that lie in the range.
vector<Point> nDRangeQuery(RangeNode* root, vector<pair<int, int>> R, int d=0) {
    if (d >= DIM || !root) 
        return {};

    RangeNode *splitNode = findSplitNode(root, R[d], d);
    vector<Point> temp = nDRangeQuery(splitNode->assoc, R, d + 1);
    int a = R[d].first, b = R[d].second;
    return temp;
}

void inOrder(RangeNode* node, int d) {
    if (!node) return;
    inOrder(node->left, d);
    cout << node->val.val[d] << " ";
    inOrder(node->right, d);
}

int main(int argc, const char* argv[]) {
    /* srand((unsigned int) time (NULL)); */
    int n, i;
    vector<Point> P, ans;
    vector<pair<int, int>> R;
    RangeNode* root;

    // n = atoi(argv[1]);
    n = 20;
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
    for (auto p: sortedP[0]) {
        cout << p.val[0] << " ";
    }
    cout << endl;
    for (auto p: sortedP[1]) {
        cout << p.val[1] << " ";
    }
    cout << endl;
    root = buildNDRangeTree(sortedP[0]);
    printf("===== %d-D Range Tree Construction Complete =====\n", DIM);
    inOrder(root->right, 0);
    cout << endl;
    inOrder(root->assoc->right, 1);
    cout << endl;
    /* R = {{100,200}, {2,2000}, {3, 3000}}; */
    /* ans = nDRangeQuery(root, R); */

}
