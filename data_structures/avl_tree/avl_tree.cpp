#include "avl_tree.h"
#include <algorithm>
#include <iostream>

int32_t Height(AVLTreeNode *node) { return node ? node->height_ : 0; }

int32_t GetBalance(AVLTreeNode *node) {
  return Height(node->children_[1]) - Height(node->children_[0]);
}

AVLTreeNode *AVLTree::Rotate(AVLTreeNode *node, int64_t d) {
  auto *t = node->children_[1 - d];
  node->children_[1 - d] = t->children_[d];
  t->children_[d] = node;
  FixHeight(node);
  FixHeight(t);
  return t;
}

void AVLTree::FixHeight(AVLTreeNode *node) {
  auto hL = Height(node->children_[0]);
  auto hR = Height(node->children_[1]);
  node->height_ = std::max(hL, hR) + 1;
}

AVLTreeNode *AVLTree::Balance(AVLTreeNode *node) {
  FixHeight(node);
  auto b = GetBalance(node);
  if (std::abs(b) == 2) {
    auto d = int32_t(b > 0);
    auto q = GetBalance(node->children_[d]);
    if (q * b < 0) {
      node->children_[d] = Rotate(node->children_[d], d);
    }
    return Rotate(node, 1 - d);
  }
  return node;
}

AVLTreeNode *AVLTree::Insert(AVLTreeNode *node, int64_t v) {
  if (node == nullptr) {
    return new AVLTreeNode(v);
  }
  auto i = 1 - int32_t(v < node->data_);
  node->children_[i] = Insert(node->children_[i], v);
  return Balance(node);
}

void AVLTree::Insert(int64_t v) { root_ = Insert(root_, v); }

void AVLTree::VisitInorder(AVLTreeNode *node) {
  if (node->children_[0] != nullptr) {
    VisitInorder(node->children_[0]);
  }

  std::cout << "Value: " << node->data_;

  if (node->children_[1] != nullptr) {
    VisitInorder(node->children_[1]);
  }
}

int main() {
  AVLTree tree;

  tree.Insert(1);
  tree.Insert(3);
  tree.Insert(2);
  tree.Insert(4);
  tree.Insert(8);
  tree.Insert(6);
  tree.Insert(5);

  tree.VisitInorder();

  return 0;
}