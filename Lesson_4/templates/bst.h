#ifndef BSTREE_H_
#define BSTREE_H_

#include <iostream>
#include <iomanip>

/* Node */
// ------------------------------------------------------------------------------------------------
template <typename T>
struct Node {
  Node* parent;
  Node* left;
  Node* right;
  const T value;

  Node(const T& value);
  virtual ~Node();
};

template <typename T>
Node<T>::Node(const T& value)
  : parent(nullptr)
  , left(nullptr)
  , right(nullptr)
  , value(value) {
}

template <typename T>
Node<T>::~Node() {
  parent = nullptr;
  left = nullptr;
  right = nullptr;
}

template <typename T>
void printNode(Node<T>* node) {
  std::cout << std::setprecision(4) << node->value << " ";
}

template <typename T>
void destroyNode(Node<T>* node) {
  if (node != nullptr) { delete node; }
  node = nullptr;
}

/* Binary Search Tree */
// ------------------------------------------------------------------------------------------------
template <typename T>
class BSTree {
public:
  BSTree();
  virtual ~BSTree();

  typedef void (*NodeOperation)(Node<T>*);

  /**
   * @defgroup Interface Common BST operations
   * @{
   */
  Node<T>* search(const T& value) const;
  bool contains(const T& value) const;
  void insert(const T& value);
  void remove(const T& value);
  /** @} */  // end of Interface group

  /**
   * @defgroup Statistics Get information about BST content
   * @{
   */
  Node<T>* minimum();
  Node<T>* maximum();
  /** @} */  // end of Statistics group

  void print();

private:
  Node<T>* m_root;

  Node<T>* search(Node<T>* node, const T& value) const;
  void insert(Node<T>* node, const T& value);
  void transplant(Node<T>* source, Node<T>* dest);
  void remove(Node<T>* node);

  Node<T>* minimum(Node<T>* node);
  Node<T>* maximum(Node<T>* node);
  Node<T>* successor(Node<T>* node);
  Node<T>* predecessor(Node<T>* node);

  void walk(Node<T>* node, NodeOperation operation);
};

/* Implementation */
// ------------------------------------------------------------------------------------------------
template <typename T>
BSTree<T>::BSTree()
  : m_root(nullptr) {
}

template <typename T>
BSTree<T>::~BSTree() {
  walk(m_root, destroyNode);
}

/* Interface group */
// ------------------------------------------------------------------------------------------------
template <typename T>
Node<T>* BSTree<T>::search(const T& value) const {
  return search(m_root, value);
}

template <typename T>
Node<T>* BSTree<T>::search(Node<T>* node, const T& value) const {
  while (node != nullptr && value != node->value) {
    if (value < node->value) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return node;
}

template <typename T>
bool BSTree<T>::contains(const T& value) const {
  return search(value) != nullptr;
}

template <typename T>
void BSTree<T>::insert(const T& value) {
  insert(m_root, value);
}

template <typename T>
void BSTree<T>::insert(Node<T>* start, const T& value) {
  Node<T>* node = new Node<T>(value);
  Node<T>* prev = nullptr;
  while (start != nullptr) {
    prev = start;
    if (node->value < start->value) {
      start = start->left;
    } else {
      start = start->right;
    }
  }
  node->parent = prev;
  if (prev == nullptr) {
    m_root = node;
  } else if (node->value < prev->value) {
    prev->left = node;
  } else {
    prev->right = node;
  }
}

template <typename T>
void BSTree<T>::transplant(Node<T>* source, Node<T>* dest) {
  if (source->parent == nullptr) {
    m_root = dest;
  } else if (source == source->parent->left) {
    source->parent->left = dest;
  } else {
    source->parent->right = dest;
  }
  if (dest != nullptr) {
    dest->parent = source->parent;
  }
}

template <typename T>
void BSTree<T>::remove(const T& value) {
  Node<T>* node = search(value);
  remove(node);
}

template <typename T>
void BSTree<T>::remove(Node<T>* node) {
  if (node == nullptr) {
    return;
  } else {
    if (node->left == nullptr) {
      transplant(node, node->right);
    } else if (node->right == nullptr) {
      transplant(node, node->left);
    } else {
      Node<T>* aux_node = minimum(node->right);
      if (aux_node->parent != node) {
        transplant(aux_node, aux_node->right);
        aux_node->right = node->right;
        aux_node->right->parent = aux_node;
      }
      transplant(node, aux_node);
      aux_node->left = node->left;
      aux_node->left->parent = aux_node;
    }
  }
}

/* Statistics group */
// ------------------------------------------------------------------------------------------------
template <typename T>
Node<T>* BSTree<T>::minimum() {
  return minimum(m_root);
}

template <typename T>
Node<T>* BSTree<T>::maximum() {
  return maximum(m_root);
}

template <typename T>
Node<T>* BSTree<T>::minimum(Node<T>* node) {
  if (node == nullptr) {
    return node;
  } else {
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
  }
}

template <typename T>
Node<T>* BSTree<T>::maximum(Node<T>* node) {
  if (node == nullptr) {
    return node;
  } else {
    while (node->right != nullptr) {
      node = node->right;
    }
    return node;
  }
}

template <typename T>
Node<T>* BSTree<T>::successor(Node<T>* node) {
  if (node == nullptr) {
    return node;
  } else {
    if (node->right != nullptr) {
      return minimum(node->right);
    }
    Node<T>* successor_node = node->parent;
    while (successor_node != nullptr && node == successor_node->right) {
      node = successor_node;
      successor_node = successor_node->parent;
    }
    return successor_node;
  }
}

template <typename T>
Node<T>* BSTree<T>::predecessor(Node<T>* node) {
  if (node == nullptr) {
    return node;
  } else {
    if (node->left != nullptr) {
      return maximum(node->left);
    }
    Node<T>* predecessor_node = node->parent;
    while (predecessor_node != nullptr && node == predecessor_node->left) {
      node = predecessor_node;
      predecessor_node = predecessor_node->parent;
    }
    return predecessor_node;
  }
}

template <typename T>
void BSTree<T>::walk(Node<T>* node, BSTree<T>::NodeOperation operation) {
  if (node != nullptr) {
    Node<T>* left = node->left;
    Node<T>* right = node->right;
    walk(left, operation);
    operation(node);
    walk(right, operation);
  }
}

// ------------------------------------------------------------------------------------------------
template <typename T>
void BSTree<T>::print() {
  walk(m_root, printNode);
}

#endif  // BSTREE_H_

