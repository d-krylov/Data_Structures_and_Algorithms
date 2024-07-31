#include "red_black_tree.h"
#include <iostream>

RedBlackTreeNode sentinel{{&sentinel, &sentinel}, nullptr, Color::BLACK, 0};
RedBlackTreeNode *NIL = &sentinel;

RedBlackTree::RedBlackTree() { root_ = NIL; }

void RedBlackTree::Rotate(RedBlackTreeNode *node, uint64_t index) {
  std::cout << "Rotate: " << node << " "
            << " Value: " << node->data_ << std::endl;
  auto *t = node->children_[1 - index];
  node->children_[1 - index] = t->children_[index];
  if (t != NIL) {
    t->parent_ = node->parent_;
  }
  if (t->children_[index] != NIL) {
    t->children_[index]->parent_ = node;
  }
  if (node->parent_ != nullptr) {
    auto s = (node == node->parent_->children_[index]) ? index : (1 - index);
    node->parent_->children_[s] = t;
  } else {
    root_ = t;
  }
  t->children_[index] = node;
  if (node != NIL) {
    node->parent_ = t;
  }
}

void RedBlackTree::InsertFixup(RedBlackTreeNode *node) {
  std::cout << "Fixup: " << node << " "
            << "Value: " << node->data_ << std::endl;
  while (node != root_ && node->parent_->color_ == Color::RED) {
    auto d = uint64_t(node->parent_ == node->parent_->parent_->children_[0]);
    auto t = node->parent_->parent_->children_[d];
    if (t->color_ == Color::RED) {
      node->parent_->color_ = Color::BLACK;
      t->color_ = Color::BLACK;
      node->parent_->parent_->color_ = Color::RED;
      node = node->parent_->parent_;
    } else {
      if (node == node->parent_->children_[d]) {
        node = node->parent_;
        Rotate(node, 1 - d);
      }
      node->parent_->color_ = Color::BLACK;
      node->parent_->parent_->color_ = Color::RED;
      Rotate(node->parent_->parent_, d);
    }
  }
  root_->color_ = Color::BLACK;
}

RedBlackTreeNode *RedBlackTree::Insert(int64_t v) {
  RedBlackTreeNode *current = root_, *parent = nullptr, *node = nullptr;
  while (current != NIL) {
    if (v == current->data_) {
      return current;
    }
    uint64_t to = 1 - uint64_t(v < current->data_);
    parent = current;
    current = current->children_[to];
  }
  node = new RedBlackTreeNode{{NIL, NIL}, parent, Color::RED, v};
  if (parent != nullptr) {
    uint64_t d = 1 - uint64_t(v < parent->data_);
    parent->children_[d] = node;
  } else {
    root_ = node;
  }
  InsertFixup(node);
  return node;
}

void RedBlackTree::DeleteFixup(RedBlackTreeNode *node) {
  while (node != root_ && node->color_ == Color::BLACK) {
    auto d = uint64_t(node == node->parent_->children_[0]);
    auto t = node->parent_->children_[d];
    if (t->color_ == Color::RED) {
      t->color_ = Color::BLACK;
      node->parent_->color_ = Color::RED;
      Rotate(node->parent_, 1 - d);
      t = node->parent_->children_[d];
    }
    if (t->children_[0]->color_ == Color::BLACK &&
        t->children_[1]->color_ == Color::BLACK) {
      t->color_ = Color::RED;
      node = node->parent_;
    } else {
      if (t->children_[d]->color_ == Color::BLACK) {
        t->children_[1 - d]->color_ = Color::BLACK;
        t->color_ = Color::RED;
        Rotate(t, d);
        t = t->parent_->children_[d];
      }
      t->color_ = node->parent_->color_;
      node->parent_->color_ = Color::BLACK;
      t->children_[d]->color_ = Color::BLACK;
      Rotate(node->parent_, 1 - d);
      node = root_;
    }
  }
  node->color_ = Color::BLACK;
}

void RedBlackTree::DeleteNode(RedBlackTreeNode *node) {
  RedBlackTreeNode *x, *y;
  if (node == nullptr || node == NIL) {
    return;
  }
  if (node->children_[0] == NIL || node->children_[1] == NIL) {
    y = node;
  } else {
    y = node->children_[1];
    while (y->children_[0] != NIL) {
      y = y->children_[0];
    }
  }
  auto d = uint64_t(y->children_[0] != NIL);
  x = y->children_[1 - d];
  x->parent_ = y->parent_;
  if (y->parent_ != nullptr) {
    auto i = uint64_t(y == y->parent_->children_[0]);
    y->parent_->children_[1 - i] = x;
  } else {
    root_ = x;
  }
  if (y != node) {
    node->data_ = y->data_;
  }
  if (y->color_ == Color::BLACK) {
    DeleteFixup(x);
  }
  delete y;
}

RedBlackTreeNode *RedBlackTree::FindNode(int64_t data) {
  auto *current = root_;
  while (current != NIL) {
    if (data == current->data_) {
      return (current);
    } else {
      auto to = 1 - uint64_t(data < current->data_);
      current = current->children_[to];
    }
  }
  return nullptr;
}

void RedBlackTree::VisitInorder(RedBlackTreeNode *node) {
  if (node->children_[0] != NIL) {
    VisitInorder(node->children_[0]);
  }

  std::cout << "Value: " << node->data_ << std::endl;

  if (node->children_[1] != NIL) {
    VisitInorder(node->children_[1]);
  }
}

int main() {
  RedBlackTree tree;

  tree.Insert(1);
  tree.Insert(3);
  tree.Insert(2);
  tree.Insert(4);
  tree.Insert(8);
  tree.Insert(6);
  tree.Insert(5);

  tree.VisitInorder();

  auto *d = tree.FindNode(8);
  tree.DeleteNode(d);

  d = tree.FindNode(2);
  tree.DeleteNode(d);

  tree.VisitInorder();

  return 0;
}