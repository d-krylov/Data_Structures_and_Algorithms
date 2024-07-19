#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <cstdint>

enum class Color { RED, BLACK };

struct RedBlackTreeNode {
  RedBlackTreeNode *children_[2] = {nullptr};
  RedBlackTreeNode *parent_{nullptr};
  Color color_{Color::RED};
  int64_t data_;
};

class RedBlackTree {
public:
  RedBlackTree();

  RedBlackTreeNode *Insert(int64_t v);
  void DeleteNode(RedBlackTreeNode *node);

  void VisitInorder() { VisitInorder(root_); }

  [[nodiscard]] RedBlackTreeNode *FindNode(int64_t data);

protected:
  void Rotate(RedBlackTreeNode *node, uint64_t index);
  void InsertFixup(RedBlackTreeNode *node);
  void DeleteFixup(RedBlackTreeNode *node);
  void VisitInorder(RedBlackTreeNode *node);

private:
  RedBlackTreeNode *root_{nullptr};
};

#endif // RED_BLACK_TREE_H