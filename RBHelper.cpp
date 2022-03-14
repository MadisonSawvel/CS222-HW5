
//Madison Sawvel

#include <iostream>
#include <string>
#include <cstdlib>
#include "RBHelper.h"

using namespace std;

bool getcolor(RBTreeNode* n) {
	if (n == nullptr) {
		return true;
	}
	return n->isblack();
}
RBTreeNode* getsibling(RBTreeNode* n, RBTreeNode* p) {
	if (p->getleft() == n) {
		return p->getright();
	}
	return p->getleft();
}
void DelProcess(RBTreeNode* x, RBTreeNode* p) {
	//if x is red, color x black, then done
	if (!getcolor(x)) {
		x->setblack(true);
		return;
	}
	//if x is root, (if p in null),then done
	if (p == nullptr) {
		return;
	}
	//w is x's current sibling
	RBTreeNode* w = getsibling(x, p);
	//if w is red, rotate up once, restart
	if (!getcolor(w)) {
		w->rotate();
		DelProcess(x, x->getparent());
		return;
	}
	//if w's children are both black, color w red. x is now p, p is now p's parents, restart
	if(getcolor(w->getleft()) && getcolor(w->getright())) {
		DelProcess(p, p->getparent());
		return;
	}
	//if w's direct child is red, color child black, rotate w up once, then done
	if (!getcolor(w->getdirect())) {
		w->getdirect()->setblack(true);
		w->rotate();
		return;
	}
	//rotate w's zigzag child up twice, recolor black, then done
	RBTreeNode* zigzag = getsibling(w->getdirect(), w->getparent());
	zigzag->rotate();
	zigzag->rotate();
	w->setblack(true);
	return;

}