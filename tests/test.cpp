// Copyright 2020 Yulia Timoshenko <timoshenkojulie01@gmail.com>
#include <gtest/gtest.h>

#include "ncstack.hpp"
#include "nct_ncstack.hpp"

TEST(Example, EmptyTest) {
  int* a = new int;
  *a = 5;
}

TEST(ncstack, typeTraits) {
  EXPECT_FALSE(std::is_copy_constructible<ncstack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<ncstack<int>>::value);
  EXPECT_TRUE(std::is_move_constructible<ncstack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<ncstack<int>>::value);
}
TEST(nct_ncstack, typeTraits) {
  EXPECT_FALSE(std::is_copy_constructible<nct_ncstack<ncstack<int>>>::value);
  EXPECT_FALSE(std::is_copy_assignable<nct_ncstack<ncstack<int>>>::value);
  EXPECT_TRUE(std::is_move_constructible<nct_ncstack<ncstack<int>>>::value);
  EXPECT_TRUE(std::is_move_assignable<nct_ncstack<ncstack<int>>>::value);
}
TEST(ncstack, pushRvalue) {
  ncstack<int> st{};
  st.push(5);
  ASSERT_EQ(st.head(), 5);
  st.push(10);
  ASSERT_EQ(st.head(), 10);
}

TEST(ncstack, pushLvalue) {
  ncstack<int> st{};
  int a = 5;
  st.push(a);
  ASSERT_EQ(st.head(), 5);
  a = 10;
  st.push(a);
  ASSERT_EQ(st.head(), 10);
}
TEST(ncstack, pop) {
  ncstack<int> st{};
  st.push(5);
  st.push(6);
  st.pop();
  ASSERT_EQ(st.head(), 5);
}
TEST(ncstack, constructor) {
  ncstack<int> st{};
  st.push(5);
  st.push(6);
  ncstack<int> st2{std::move(st)};
  ASSERT_EQ(6, st2.head());
}
TEST(ncstack, assign) {
  ncstack<int> st{};
  st.push(5);
  st.push(6);
  ncstack<int> st2{};
  st2 = std::move(st);
  ASSERT_EQ(6, st2.head());
}
TEST(nct_ncstack, pushEmplace) {
  struct ncpy_mv {
    ncpy_mv(const ncpy_mv&) = delete;
    ncpy_mv(ncpy_mv&&) = default;
    auto operator=(const ncpy_mv&) -> ncpy_mv& = delete;
    auto operator=(ncpy_mv&&) -> ncpy_mv& = default;
    int a;
    int b;
  };
  nct_ncstack<ncpy_mv> a{};
  a.push_emplace<int, int>(5, 3);
  ASSERT_EQ(a.head().a, 5);
  ASSERT_EQ(a.head().b, 3);
}

TEST(nct_ncstack, push) {
  nct_ncstack<ncstack<int>> a{}, b{};
  ncstack<int> childa{}, childb{};
  childa.push(4);
  childb.push(3);
  a.push(std::forward<ncstack<int>>(childa));
  b.push(std::forward<ncstack<int>>(childb));
  ASSERT_EQ(a.head().head(), 4);
  ASSERT_EQ(b.head().head(), 3);
}

TEST(nct_ncstack, move) {
  nct_ncstack<ncstack<int>> a{};
  ncstack<int> childa{}, childb{}, childc{};
  childa.push(4);
  childb.push(3);
  childc.push(2);
  a.push(std::move(childa));
  a.push(std::move(childb));
  a.push(std::move(childc));
  ASSERT_EQ(a.head().head(), 2);
  auto b{std::move(a)};
  ASSERT_EQ(b.pop().head(), 2);
  ASSERT_EQ(b.head().head(), 3);
  EXPECT_FALSE(a);
  nct_ncstack<ncstack<int>> c{};
  c = std::move(b);
  ASSERT_EQ(c.pop().head(), 3);
  ASSERT_EQ(c.head().head(), 4);
  EXPECT_FALSE(b);
}

TEST(nct_ncstack, typecheck) {
  ASSERT_THROW(nct_ncstack<int> a{}, std::runtime_error);
  std::cout<<"last - test"<<std::endl;
  auto* lmao1 = new std::pair<int, int>{5, 3};
  delete lmao1;
  std::cout << lmao1->first<<std::endl;
  auto* lmao2 = new std::pair<int, int>{6, 2};
  delete lmao2;
  std::cout << lmao1->first<<std::endl;
  ncstack<int> a{};
  a.push(5);
  a.pop();
  std::cout << lmao2->first;
}

