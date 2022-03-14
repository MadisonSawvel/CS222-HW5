
//Madison Sawvel

#include <iostream>
#include <string>
#include <cstdlib>
#include "RBTree.h"
#include "DRT.h"
#include "RBTreeNode.h"

using namespace std;

RBTree::RBTree() { root = NULL; }
RBTree::~RBTree() { delete root; }

DRT* RBTree::add(string key, string data) {
	if (!root) {
		root = new RBTreeNode(key, data, NULL, NULL, NULL, this);
		root->setblack(true);
		return new DRT("", "", "");
	}
	return root->add(key, data, "", "");
}

void RBTree::setroot(RBTreeNode* r) { root = r; }

DRT* RBTree::searchnode(string key) {
	//searches tree for given key
	if (root) {
		return root->searchnode(key, "", "");
	}
	return new DRT("", "", "");
}
string RBTree::first() {
	//make
	if (root) {
		return root->first()->getk();
	}
	return "";
}
string RBTree::last() {
	//last key in the tree (right on down)
	if (root) {
		return root->last()->getk();
	}
	return "";
}
DRT* RBTree::remove(string key) {
	//removes an item from the list
	if (!root) {
		return new DRT("", "", "");
	}
	return root->remove(key, "", "");
}
DRT* RBTree::search(string key) {
	//database search method
	//checks to see if we're searching on the empty string,
	//if so buils a DRT with first and last, otherwise calls searchnode
	if (key == "") {
		return new DRT("", first(), last());
	}
	if (root) {
		return root->searchnode(key, "", "");
	}
	return new DRT("", "", "");
}
DRT* RBTree::modify(string key, string data) {
	//database modify method
	if (key == "") {
		return new DRT("", first(), last());
	}
	if (data == "") {
		return remove(key);
	}
	return add(key, data);
}