
//Madison Sawvel

#include <iostream>
#include <string>
#include <cstdlib>
#include "RBHelper.h"
#include "RBTreeNode.h"
#include "DRT.h"

using namespace std;

RBTreeNode::RBTreeNode(string key, string data, RBTreeNode* l, RBTreeNode* r, RBTreeNode* p, RBTree* T) {
	k = key; d = data; left = l; right = r; parent = p; t = T;
}
RBTreeNode::~RBTreeNode() {
	delete left;
	delete right;
}
DRT* RBTreeNode::add(string key, string data, string n, string p) {
	if (k == key) {
		d = data;
		return new DRT(data, n, p);
	}
	if (k < key) {
		if (right) {
			return right->add(key, data, n, k);
		}
		else {
			RBTreeNode* newTreeNode = new RBTreeNode(key, data, nullptr, nullptr, this, t);
			newTreeNode->setblack(false);
			this->setright(newTreeNode);
			newTreeNode->AddProcess();
			if (t->Valid() == -1)
				cout << "NOT VALID";
			return new DRT(data, n, k);
		}
	}
	if (left) {
		return left->add(key, data, k, p);
	}
	else {
		RBTreeNode* newTreeNode = new RBTreeNode(key, data, nullptr, nullptr, this, t);
		newTreeNode->setblack(false);
		this->setleft(newTreeNode);
		newTreeNode->AddProcess();
		if (t->Valid() == -1)
			cout << "NOT VALID";
		return new DRT(data, k, p);
	}
}
DRT* RBTreeNode::searchnode(string key, string n, string p) {
	if (k == key) {
		string next, prev;
		if (!right) next = n;
		else next = right->first()->getk();
		if (!left) prev = p;
		else prev = left->last()->getk();
		return new DRT(d, next, prev);
	}
	if (k < key) {
		if (right) return right->searchnode(key, n, k);
		return new DRT("", n, k);
	}
	if (left) return left->searchnode(key, k, p);
	return new DRT("", k, p);
}
RBTreeNode* RBTreeNode::first() {
	//left on down
	if (this->getleft() != nullptr) {
		return this->getleft()->first();
	}
	return this;
}
RBTreeNode* RBTreeNode::last() {
	//right on down 
	if (this->getright() != nullptr) {
		return this->getright()->last();
	}
	return this;
}
string RBTreeNode::getk() { return k; }
string RBTreeNode::getd() { return d; }
RBTreeNode* RBTreeNode::getright() { 
	if (!this) {
		return nullptr;
	}
	if (right) {
		return right;
	}
	else {
		return nullptr;
	}
}
RBTreeNode* RBTreeNode::getleft() {
	if (!this) {
		return nullptr;
	}
	if (left) {
		return left;
	}
	else {
		return nullptr;
	}
}
string RBTreeNode::next() { return left->last()->getk(); }
string RBTreeNode::prev() { return right->first()->getk(); }
DRT* RBTreeNode::remove(string key, string n, string p) {
	if (k == key) {
		this->remove();
		if (t->Valid() == -1) {
			cout << "NOT VALID";
		}
		return new DRT("", n, p);
	}
	if (k < key) {
		if (right) {
			return right->remove(key, n, k);
			return new DRT("", n, k);
		}
	}
	if (left) {
		return left->remove(key, k, p);
	}
	return new DRT("", k, p);
}
void RBTreeNode::remove() {
	//physical removal decide whether it's 0,1, or 2 children. 
	//possibly copies key and data values and physically removes the deleted node
	if (left && right) {
		d = left->last()->getd();
		k = left->last()->getk();
		left->last()->remove();
	}
	else if (left || right) {
		if (this->parent == nullptr) {
			if (left)
			{
				t->setroot(left);
				left->setparent(nullptr);
				this->setleft(nullptr);

				if (this->isblack())
					DelProcess(left, nullptr);
			}
			else {
				t->setroot(right);
				right->setparent(nullptr);
				this->setright(nullptr);

				if (this->isblack())
					DelProcess(right, nullptr);
			}

		}
		else if (this->parent->getleft() == this) {
			if (left) {
				this->getleft()->setparent(this->parent);
				this->parent->setleft(this->getleft());
				this->setleft(nullptr);

				if (this->isblack())
					DelProcess(left, this->parent);
			}
			else {
				this->getright()->setparent(this->parent);
				this->parent->setleft(this->getright());
				this->setright(nullptr);

				if (this->isblack())
					DelProcess(right, this->parent);
			}
		}
		else {
			if (left) {
				this->getleft()->setparent(this->parent);
				this->parent->setright(this->getleft());
				this->setleft(nullptr);

				if (this->isblack())
					DelProcess(left, this->parent);
			}
			else {
				this->getright()->setparent(this->parent);
				this->parent->setright(this->getright());
				this->setright(nullptr);

				if (this->isblack())
					DelProcess(right, this->parent);
			}
		}
		this->setparent(nullptr);
	}
	else {
		if (this->parent == nullptr) {
			t->setroot(nullptr);
		}
		else if (this->parent->getleft() == this) {
			this->parent->setleft(nullptr);
		}
		else {
			this->parent->setright(nullptr);
		}
		this->setparent(nullptr);

		if (this->isblack())
			DelProcess(nullptr, this->parent);
	}

}
void RBTreeNode::setparent(RBTreeNode* p) { 
	if (this == nullptr) {
		return;
	}
	parent = p;
}
void RBTreeNode::setleft(RBTreeNode* l) { 
	if (this == nullptr) {
		return;
	}
	else {
		left = l;
	}
}
void RBTreeNode::setright(RBTreeNode* r) {
	if (this == nullptr) {
		return;
	}
	else {
		right = r;
	}
}
RBTreeNode* RBTreeNode::getparent() {
	if (this == nullptr) {
		return nullptr;
	}
	if (parent == nullptr) {
		return nullptr;
	}
	else {
		return parent;
	}
}
bool RBTreeNode::isblack(){
	return this->black;
}
void RBTreeNode::setblack(bool b){
	black = b;
}
RBTreeNode* RBTreeNode::getdirect() {
	if (parent == nullptr) {
		return nullptr;
	}
	if (this == this->getparent()->getleft()) {
		return left;
	}
	else {
		return right;
	}
}
bool RBTreeNode::isdirect() {
	if (this == nullptr) {
		return false;
	}
	if (parent->getdirect() == this) {
		return true;
	}
	else {
		return false;
	}
}
void RBTreeNode::rotate() {
	RBTreeNode* parent = this->getparent();
	RBTreeNode* grandparent = this->getparent()->getparent();
	RBTreeNode* z;
	bool temp = black;
	black = getcolor(parent);
	parent->setblack(this);
	this->setblack(black);

	if (this->parent->getleft() == this) {
		z = this->getright();
	}
	else {
		z = this->getleft();
	}
	//x parent needs to point to grandparent
	this->setparent(grandparent);
	//if gp does not exist, root needs to point to x
	if (grandparent == nullptr) {
		this->t->setroot(this);
	}
	//if p is right child of grandparent, grandparents right needs to point to x
	else if (grandparent->getright() == parent && parent != nullptr) {
		grandparent->setright(this);
	}
	//if p is left child of grandparent, grandparents left needs to point to x
	else if (grandparent->getleft() == parent && parent != nullptr) {
		grandparent->setleft(this);
	}
	//p's parent needs to point to x
	parent->setparent(this);
	//if x is a left child of p, x's right needs to point to p
	if (parent->getleft() == this) {
		this->setright(parent);
		parent->setleft(z);
	}
	//if x is right child of p, x's left needs to point to p
	else {
		this->setleft(parent);
		parent->setright(z);
	}
	//if z exists, z's parent needs to point to p
	if (z != nullptr) {
		z->setparent(parent);
	}
}
void RBTreeNode::AddProcess() {
	//if x is the root, color x black, then done
	if (this->getparent() == nullptr) {
		this->setblack(true);
		return;
	}
	//if x's parent is black, then done
	if (this->getparent()->isblack()) {
		return;
	}
	//if x's uncle is red, color x's parent and uncle black, color grandparent red, x is now x's grandparent, restart
	if (!getcolor(getsibling(this->getparent(), this->getparent()->getparent()))) {

		RBTreeNode* uncle = getsibling(this->getparent(), this->getparent()->getparent());
		if (uncle != nullptr) {
			uncle->setblack(true);
			this->getparent()->setblack(true);
			this->getparent()->getparent()->setblack(false);
			this->getparent()->getparent()->AddProcess();
			return;
		}
	}
	//if x is a direct grandchild, rotate x's parent up once, then done
	if (this->isdirect()) {
		this->getparent()->rotate();
		return;
	}
	//rotate x up twice, then done
	this->rotate();
	this->rotate();
	return;
}