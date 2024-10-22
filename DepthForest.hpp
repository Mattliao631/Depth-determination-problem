#include <iostream>
#include <algorithm>
#include <unordered_map>


using namespace std;

struct DepthTreeNode {
    DepthTreeNode* parent;
    DepthTreeNode(): parent(this) {}
};


class DepthForest {
public:
    DepthForest() {}
    void MakeTree(int u) {
        if (nodes.find(u) != nodes.end()) return;
        DepthTreeNode* node = new DepthTreeNode();
        nodes[u] = node;
    }
    int FindDepth(int v) {
        DepthTreeNode* node = nodes[v];
        int depth = 0;
        while(node != node->parent) {
            depth++;
            node = node->parent;
        }
        return depth;
    }
    bool Graft(int u, int v) {
        DepthTreeNode* nodeU = nodes[u];
        DepthTreeNode* nodeV = nodes[v];
        if (nodeU != nodeU->parent) { // u must be a root
            return false;
        }
        DepthTreeNode* tempU = nodeU;
        DepthTreeNode* tempV = nodeV;
        while (nodeU != nodeU->parent) {
            nodeU = nodeU->parent;
        }
        while (nodeV != nodeV->parent) {
            nodeV = nodeV->parent;
        }
        if (nodeU == nodeV) return false;

        tempU->parent = tempV;
        return true;
    }

private:
    unordered_map<int, DepthTreeNode*> nodes;
};