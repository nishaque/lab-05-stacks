// Copyright 2020 Yulia Timoshenko <timoshenkojulie01@gmail.com>
#ifndef INCLUDE_SHAREDPTR_HPP
#define INCLUDE_SHAREDPTR_HPP

#include <atomic>
#include <iostream>

template <typename T>
class SharedPtr {
 public:
  SharedPtr() = default;
  explicit SharedPtr(T* ptr);
  SharedPtr(const SharedPtr& r);
  SharedPtr(SharedPtr&& r) noexcept;
  ~SharedPtr();
  auto operator=(const SharedPtr& r) -> SharedPtr&;
  auto operator=(SharedPtr&& r) noexcept -> SharedPtr&;

  explicit operator bool() const;
  auto operator*() const -> T&;
  auto operator->() const -> T*;

  auto get() -> T*;
  void reset();
  void reset(T* ptr);
  void swap(SharedPtr& r);
  auto use_count() const -> size_t;

 private:
  T* pointer = nullptr;
  std::atomic_uint* counter = nullptr;
};

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr) {
  pointer = ptr;
  counter = new std::atomic_uint;
  *counter = 1;
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& r) {
  counter = r.counter;
  pointer = r.pointer;
  if (counter) ++*counter;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& r) noexcept {
  pointer = std::move(r.pointer);
  r.pointer = nullptr;
  counter = std::move(r.counter);
  r.counter = nullptr;
}

template <typename T>
auto SharedPtr<T>::operator=(const SharedPtr& r) -> SharedPtr& {
  if (&r != this) {
    this->~SharedPtr();
    pointer = r.pointer;
    counter = r.counter;
    if (counter) ++*counter;
    return *this;
  } else
    return *this;
}

template <typename T>
auto SharedPtr<T>::operator=(SharedPtr&& r) noexcept -> SharedPtr& {
  if (&r != this) {
    this->~SharedPtr();
    pointer = r.pointer;
    counter = r.counter;
    r.pointer = nullptr;
    r.counter = nullptr;
    return *this;
  } else
    return *this;
}

template <typename T>
SharedPtr<T>::operator bool() const {
  return (bool)pointer;
}

template <typename T>
auto SharedPtr<T>::operator*() const -> T& {
  return *pointer;
}

template <typename T>
auto SharedPtr<T>::operator->() const -> T* {
  return pointer;
}

template <typename T>
auto SharedPtr<T>::get() -> T* {
  return pointer;
}

template <typename T>
void SharedPtr<T>::reset() {
  *this = std::move(SharedPtr<T>());
}

template <typename T>
void SharedPtr<T>::reset(T* r) {
  *this = std::move(SharedPtr<T>(r));
}

template <typename T>
void SharedPtr<T>::swap(SharedPtr<T>& r) {
  std::swap(pointer, r.pointer);
  std::swap(counter, r.counter);
}

template <typename T>
auto SharedPtr<T>::use_count() const -> size_t {
  return counter ? (size_t)*counter : 0;
}

template <typename T>
SharedPtr<T>::~SharedPtr() {
  if (counter && !--(*counter)) {
    delete pointer;
    delete counter;
  }
}

#endif  // INCLUDE_SHAREDPTR_HPP
