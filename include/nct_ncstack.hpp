// Copyright 2020 Yulia Timoshenko <timoshenkojulie01@gmail.com>
#ifndef INCLUDE_NCT_NCSTACK_HPP
#define INCLUDE_NCT_NCSTACK_HPP
#include <iostream>

#include "Node.hpp"

template <typename T>
class nct_ncstack {
 public:
  template <typename... Args>
  void push_emplace(Args &&...value);
  void push(T &&value);
  const T &head() const;
  T pop();

  nct_ncstack();
  nct_ncstack(const nct_ncstack &) = delete;
  nct_ncstack(nct_ncstack &&);

  auto operator=(const nct_ncstack &) -> nct_ncstack & = delete;
  auto operator=(nct_ncstack &&) -> nct_ncstack &;

  operator bool() const;

 private:
  Node<T> *top = nullptr;
};

template <typename T>
template <typename... Args>
void nct_ncstack<T>::push_emplace(Args &&...value) {
  auto nelem = T{std::forward<Args>(value)...};
  push(std::move(nelem));
}

template <typename T>
void nct_ncstack<T>::push(T &&value) {
  auto *newtop = new Node<T>{std::forward<T>(value), top};
  top = newtop;
}

template <typename T>
const T &nct_ncstack<T>::head() const {
  if (top)
    return top->data;
  else
    throw std::out_of_range{"Empty"};
}

template <typename T>
T nct_ncstack<T>::pop() {
  if (top == nullptr) throw std::out_of_range{"Stack is empty"};
  auto rv = std::move(top->data);
  auto *tbd = top;
  top = top->prevNode;
  delete tbd;
  //  delete &tbd->data;
  //  tbd->prevNode=nullptr;
  return rv;
}

template <typename T>
nct_ncstack<T>::nct_ncstack() {
  if (!std::is_move_constructible<T>::value ||
      !std::is_move_assignable<T>::value ||
      std::is_copy_constructible<T>::value || std::is_copy_assignable<T>::value)
    throw std::runtime_error{"Type isn't non-copyable and movable"};
}
template <typename T>
nct_ncstack<T>::nct_ncstack(nct_ncstack &&s) {
  top = s.top;
  s.top = nullptr;
}
template <typename T>
auto nct_ncstack<T>::operator=(nct_ncstack &&s) -> nct_ncstack & {
  if (&s != this) {
    this->~nct_ncstack();
    top = s.top;
    s.top = nullptr;
  }
  return *this;
}
template <typename T>
nct_ncstack<T>::operator bool() const {
  return (bool)top;
}
#endif  // INCLUDE_NCT_NCSTACK_HPP
