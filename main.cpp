#include "DepthForest.hpp"
#include "PseudoDepthForest.hpp"
#include <cstdlib>
#include <ctime>

#define SIZE_A 300
#define SIZE_B 500
#define OPERATION_RATIO 7
#define epochs 100

// #define OUTPUT

void TestDepthForest();
void TestPseudoDepthForest();

int ErrorFlag = 0;

void Test();

int main() {
    srand(time(0));
    TestDepthForest();
    TestPseudoDepthForest();
    for (int i = 0; i < epochs;i ++) {
        cout << "Epoch " << i << endl;
        Test();
    }
    if (ErrorFlag) cout << ErrorFlag << endl;
    else cout << "All tests passed" << endl;
    return 0;
}

void Test() {
    #ifdef OUTPUT
    cout << "Test" << endl;
    #endif
    DepthForest F1;
    PseudoDepthForest F2;

    int n = SIZE_A * SIZE_B;
    for (int i = 0; i < n; i++) {
        F1.MakeTree(i);
        F2.MakeTree(i);
    }
    int m = OPERATION_RATIO * n;
    for (int i = 0; i < n; i++) {
        int u = rand() % n;
        int v = rand() % n;
        if (F1.Graft(u, v)) {
            F2.Graft(u, v);
        }
    }
    #ifdef OUTPUT
    for (int i = 0; i < SIZE_A; i++) {
        cout << "DepthForest(Sols): ";
        for (int j = 0; j < SIZE_B; j++) {
            cout << F1.FindDepth(i * SIZE_B + j) << " ";
        }
        cout << endl;
        cout << "PseudoDepthForest: ";
        for (int j = 0; j < SIZE_B; j++) {
            cout << F2.FindDepth(i * SIZE_B + j) << " ";
        }
        cout << endl;
        cout << endl;
    }
    #endif
    for (int i = 0; i < n; i++) {
        if (F1.FindDepth(i) != F2.FindDepth(i)) {
            ErrorFlag = 1;
            break;
        }
    }
}

void TestPseudoDepthForest() {
    cout << "PseudoDepthForest" << endl;
    PseudoDepthForest forest;
    forest.MakeTree(1);
    forest.MakeTree(2);
    forest.MakeTree(3);
    forest.MakeTree(4);
    forest.MakeTree(5);
    forest.MakeTree(6);
    forest.MakeTree(7);

    forest.Graft(2, 1);
    forest.Graft(3, 1);
    forest.Graft(4, 2);
    forest.Graft(5, 2);
    forest.Graft(6, 3);
    for (int i = 1; i <= 7; i++) {
        cout << "Depth of " << i << " is " << forest.FindDepth(i) << endl;
    }
    cout << endl;
    forest.Graft(1, 7);
    for (int i = 1; i <= 7; i++) {
        cout << "Depth of " << i << " is " << forest.FindDepth(i) << endl;
    }
    cout << endl;
}

void TestDepthForest() {
    cout << "DepthForest" << endl;
    DepthForest forest;
    forest.MakeTree(1);
    forest.MakeTree(2);
    forest.MakeTree(3);
    forest.MakeTree(4);
    forest.MakeTree(5);
    forest.MakeTree(6);
    forest.MakeTree(7);


    forest.Graft(2, 1);
    forest.Graft(3, 1);
    forest.Graft(4, 2);
    forest.Graft(5, 2);
    forest.Graft(6, 3);
    for (int i = 1; i <= 7; i++) {
        cout << "Depth of " << i << " is " << forest.FindDepth(i) << endl;
    }
    cout << endl;
    forest.Graft(1, 7);
    for (int i = 1; i <= 7; i++) {
        cout << "Depth of " << i << " is " << forest.FindDepth(i) << endl;
    }
    cout << endl;
}