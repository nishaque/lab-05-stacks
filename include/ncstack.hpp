// Copyright 2020 Yulia Timoshenko <timoshenkojulie01@gmail.com>
#ifndef INCLUDE_NCSTACK_HPP
#define INCLUDE_NCSTACK_HPP
#include <iostream>
#include <stdexcept>
#include <utility>

#include "Node.hpp"

template <typename T>
class ncstack {
 public:
  void push(T &&value);
  void push(const T &value);
  void pop();
  const T &head() const;

  ncstack() = default;
  ncstack(ncstack &) = delete;
  ncstack(ncstack &&);

  auto operator=(ncstack &) -> ncstack & = delete;
  auto operator=(ncstack &&) -> ncstack &;

  ~ncstack();


 private:
  Node<T> *top;
};

template <typename T>
ncstack<T>::~ncstack<T>() {
  while (top != nullptr) pop();
}

template <typename T>
void ncstack<T>::push(T &&value) {
  top = std::move(new Node<T>{std::forward<T>(value), top});
}
template <typename T>
void ncstack<T>::push(const T &value) {
  top = std::move(new Node<T>{value, top});
}
template <typename T>
void ncstack<T>::pop() {
  if (top == nullptr) {
    throw std::out_of_range("Stack is empty!");
  } else {
    auto *newtop = top;
    top = top->prevNode;
    delete newtop;

  }
}
template <typename T>
const T &ncstack<T>::head() const {
  if (!top) throw std::out_of_range("Stack is empty!");
  return top->data;
}
template <typename T>
ncstack<T>::ncstack(ncstack &&s) {
  top = s.top;
  s.top = nullptr;
}
template <typename T>
auto ncstack<T>::operator=(ncstack &&s) -> ncstack & {
  if (&s != this) {
    this->~ncstack();
    top = s.top;
    s.top = nullptr;
  }
  return *this;
}

#endif  // INCLUDE_NCSTACK_HPP
