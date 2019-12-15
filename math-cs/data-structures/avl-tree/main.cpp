#include <iostream>

#include "node.h"
#include "tree.h"

using namespace std;

int main() {
    Tree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);
    tree.print2D();
    return 0;
}