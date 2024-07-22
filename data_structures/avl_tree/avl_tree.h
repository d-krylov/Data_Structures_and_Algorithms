#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <cstdint>

struct AVLTreeNode {
  AVLTreeNode(int64_t v) : data_(v) {}
  int64_t data_;
  int32_t height_{1};
  AVLTreeNode *children_[2] = {nullptr};
};

class AVLTree {
public:
  void Insert(int64_t v);

  void VisitInorder() { VisitInorder(root_); }

protected:
  AVLTreeNode *Rotate(AVLTreeNode *node, int64_t direction);
  AVLTreeNode *Balance(AVLTreeNode *node);
  AVLTreeNode *Insert(AVLTreeNode *node, int64_t v);

  void FixHeight(AVLTreeNode *node);
  void VisitInorder(AVLTreeNode *node);

private:
  AVLTreeNode *root_{nullptr};
};

#endif // AVL_TREE_H