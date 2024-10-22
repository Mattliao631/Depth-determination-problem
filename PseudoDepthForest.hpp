#include <iostream>
#include <algorithm>
#include <unordered_map>

struct Node {
    int depth = 0;
    int rank = 0;
    Node* parent;
    Node(): depth(0), rank(0), parent(this) {}
    Node(int d): depth(d), rank(0), parent(this) {}
    Node(int d, Node* p): depth(d), rank(0), parent(p) {}
};

class PseudoDepthForest {
public:
    PseudoDepthForest() {
        temp = Node(0, nullptr);
    }
    void MakeTree(int u) {
        if (nodes.find(u) != nodes.end()) return;
        Node* node = new Node(0);
        nodes[u] = node;
    }
    int FindDepth(int v) {
        Node* node = nodes[v];
        findDepth(node);
        return temp.depth + node->parent->depth;
    }
    void Graft(int u, int v) {
        Node* nodeU = nodes[u];
        Node* nodeV = nodes[v];
        Node* tempU = nodeU;
        Node* tempV = nodeV;        

        findDepth(nodeU);
        nodeU = temp.parent;
        findDepth(nodeV);
        nodeV = temp.parent;
        if (nodeU == nodeV) return;
        
        Node* small = nodeU;
        Node* large = nodeV;
        
        if (small->rank > large->rank) swap(small, large);
        if (small->rank == large->rank) large->rank++;
        small->parent = large;

        // 1. norm: (tempV->depth);
        // 1. root: (tempV->depth) - nodeV->depth
        // 2. norm: (tempV->depth + nodeV->depth)
        // 2. root: (tempV->depht + nodeV->depth) - nodeV->depth
        int delta = tempV->depth - nodeV->depth * (nodeV == tempV);             // delta = effect of new root to graftee
        if (large == nodeV) {    // graft
            small->depth = small->depth + delta + 1;                   // original + delta + cat
        } else {                        // reverse graft
            delta += nodeV->depth;                                              // delta = effect of real root to pseudo root
            large->depth = large->depth + delta + 1;    // original + delta + cat
            small->depth = small->depth - large->depth;                         // original - effect of pseudo root to real root
        }
        
    }
private:
    Node temp;
    unordered_map<int, Node*> nodes;
    void findDepth(Node* node) {
        if (node == node->parent) {
            temp = Node(0, node);
            return;
        }
        findDepth(node->parent);
        node->parent = temp.parent;
        node->depth += temp.depth;
        temp.depth = node->depth;
    }
};