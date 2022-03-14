
//Madison Sawvel

#include <iostream>
#include <string>
#include <cstdlib>
#include "RBTree.h"
#include "RBTreeNode.h"
using namespace std;

int RBTree::Valid() {

    int r;

    if (!root) {
        r = 1;
    }
    else {
        if (!root->isblack() || root->getparent()) {
            r = 0;
        }
        else {
            r = root->ValidNode() != -1;
        }
    }
    return r;
}

int RBTreeNode::ValidNode() {

    int lc, rc, r;

    if (!black && parent && !parent->isblack()) {
        r = -1;
    }
    else {
        if (left && left->getparent() != this) {
            r = -1;
        }
        else {
            if (left && left->getk() >= k) {
                r = -1;
            }
            else {
                if (right && right->getparent() != this) {
                    r = -1;
                }
                else {
                    if (right && right->getk() <= k) {
                        r = -1;
                    }
                    else {
                        if (left) {
                            lc = left->ValidNode();
                        }
                        else {
                            lc = 0;
                        }
                        if (lc == -1) {
                            r = -1;
                        }
                        else {
                            if (right) {
                                rc = right->ValidNode();
                            }
                            else {
                                rc = 0;
                            }
                            if (rc == -1) {
                                r = -1;
                            }
                            else {
                                if (lc != rc) {
                                    r = -1;
                                }
                                else {
                                    if (black) {
                                        r = lc + 1;
                                    }
                                    else {
                                        r = lc;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return r;
}