#include "FixedPoint.hpp"
#include <gtest/gtest.h>

TEST(FixedPointTest, CtorDouble_1) {
  FixedPoint<uint8_t, 7> q = 1.5; 
  EXPECT_EQ(q.value_, 0b11000000);
}

TEST(FixedPointTest, CtorDouble_2) {
  FixedPoint<uint8_t, 7> q = 1.5; 
  EXPECT_EQ(q.value_, 0b11000000);
}

TEST(FixedPointTest, CtorDouble_3) {
  FixedPoint<uint8_t, 0> q = 1.4; 
  EXPECT_EQ(q.value_, 0b00000001);
}

TEST(FixedPointTest, CtorDouble_4) {
  FixedPoint<uint8_t, 0> q = 1.5; 
  EXPECT_EQ(q.value_, 0b00000010);
}

TEST(FixedPointTest, CtorDouble_5) {
  FixedPoint<uint8_t, 0> q = -1; 
  EXPECT_EQ(q.value_, 0b11111111);
}

TEST(FixedPointTest, CtorOther_1) {
  FixedPoint<uint8_t, 7> q1; 
  q1.value_ = 0xAB;
  FixedPoint<uint8_t, 7> q2 = q1;
  EXPECT_EQ(q2.value_, q1.value_);
}

TEST(FixedPointTest, CtorOther_2) {
  FixedPoint<uint8_t, 0> q1; 
  q1.value_ = 0xAB;
  FixedPoint<uint16_t, 0> q2 = q1;
  EXPECT_EQ(q2.value_, q1.value_);
}

TEST(FixedPointTest, CtorOther_3) {
  FixedPoint<uint8_t, 4> q1; 
  q1.value_ = 0xAB;
  FixedPoint<uint16_t, 8> q2 = q1;
  EXPECT_EQ(q2.value_, 0x0AB0);
}

TEST(FixedPointTest, CtorOther_rounding_1) {
  FixedPoint<int16_t, 8> q1 = .49;
  FixedPoint<int16_t, 0> q2 = q1;
  EXPECT_EQ(q2.toDouble(), 0.0);
}

TEST(FixedPointTest, CtorOther_rounding_2) {
  FixedPoint<int16_t, 8> q1 = .5;
  FixedPoint<int16_t, 0> q2 = q1;
  EXPECT_EQ(q2.toDouble(), 1.0);
}

TEST(FixedPointTest, toDouble_1) {
  FixedPoint<uint8_t, 0> q = -1; 
  EXPECT_EQ(q.toDouble(), double(0xFF));
}

TEST(FixedPointTest, toDouble_2) {
  FixedPoint<int8_t, 0> q = -1; 
  EXPECT_EQ(q.toDouble(), -1.0);
}

TEST(FixedPointTest, toDouble_3) {
  FixedPoint<int8_t, 4> q = 1.5; 
  EXPECT_EQ(q.toDouble(), 1.5);
}

TEST(FixedPointTest, add_1) {
  FixedPoint<int8_t, 4> q1 = 1.5; 
  FixedPoint<int8_t, 4> q2 = 2; 
  FixedPoint<int8_t, 4> qs = q1 + q2;
  EXPECT_EQ(qs.toDouble(), 3.5);
}

TEST(FixedPointTest, add_2) {
  FixedPoint<int8_t, 4> q1 = 1.5; 
  FixedPoint<int8_t, 4> q2 = -2; 
  FixedPoint<int8_t, 4> qs = q1 + q2;
  EXPECT_EQ(qs.toDouble(), -.5);
}

TEST(FixedPointTest, sub_1) {
  FixedPoint<int8_t, 4> q1 = 3; 
  FixedPoint<int8_t, 4> q2 = 2; 
  FixedPoint<int8_t, 4> qd = q1 - q2;
  EXPECT_EQ(qd.toDouble(), 1);
}

TEST(FixedPointTest, sub_2) {
  FixedPoint<int8_t, 4> q1 = 2; 
  FixedPoint<int8_t, 4> q2 = 2.5; 
  FixedPoint<int8_t, 4> qd = q1 - q2;
  EXPECT_EQ(qd.toDouble(), -.5);
}

TEST(FixedPointTest, mul_1) {
  FixedPoint<int8_t, 4> q1 = 1.5; 
  FixedPoint<int8_t, 4> q2 = 2; 
  FixedPoint<int8_t, 4> qp = q1 * q2;
  EXPECT_EQ(qp.toDouble(), 3.0);
}

TEST(FixedPointTest, mul_2) {
  FixedPoint<int8_t, 1> q1 = 0.5; 
  FixedPoint<int8_t, 0> q2 = 2; 
  FixedPoint<int8_t, 0> qp = q1 * q2;
  EXPECT_EQ(qp.toDouble(), 1.0);
}
