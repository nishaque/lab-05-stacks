// Copyright 2020 Yulia Timoshenko <timoshenkojulie01@gmail.com>
#include <iostream>
#ifndef INCLUDE_NODE_HPP
#define INCLUDE_NODE_HPP

template <typename T>
struct Node {
  T data;
  Node<T>* prevNode;
  ~Node(){
    std::cout<<this<<" is being deleted"<<std::endl;
  }
};



#endif  // INCLUDE_NODE_HPP
