// Copyright 2020 Yulia Timoshenko <timoshenkojulie01@gmail.com>

#ifndef INCLUDE_NODE_HPP
#define INCLUDE_NODE_HPP

template <typename T>
struct Node {
  T data;
  Node<T>* prevNode;
};

#endif  // INCLUDE_NODE_HPP
