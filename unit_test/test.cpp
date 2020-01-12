#include "Complex.hpp"
#include "FixedPoint.hpp"

#include <gtest/gtest.h>

template <typename T>
class ComplexTest : public ::testing::Test {
 protected:
  ComplexTest() {}
  ~ComplexTest() {}
};

using FP1 = FixedPoint<uint32_t, 8>;

using MyTypes = ::testing::Types<double, FP1>;

TYPED_TEST_CASE(ComplexTest, MyTypes);

TYPED_TEST(ComplexTest, Ctor_1) {
  Complex<TypeParam> c; 

  ASSERT_EQ(c.re_, TypeParam(0));
  ASSERT_EQ(c.im_, TypeParam(0));
}

TYPED_TEST(ComplexTest, Ctor_2) {
  Complex<TypeParam> c(1, 2); 

  ASSERT_EQ(c.re_, TypeParam(1));
  ASSERT_EQ(c.im_, TypeParam(2));
}

TYPED_TEST(ComplexTest, Add) {
  Complex<TypeParam> a(1.2, 2.3); 
  Complex<TypeParam> b(3.4, 4.5); 

  Complex<TypeParam> sum = a + b;
  ASSERT_EQ(sum.re_, TypeParam(1.2) + TypeParam(3.4));
  ASSERT_EQ(sum.im_, TypeParam(2.3) + TypeParam(4.5));
}

TYPED_TEST(ComplexTest, Sub) {
  Complex<TypeParam> a(1.2, 2.3); 
  Complex<TypeParam> b(3.4, 4.5); 

  Complex<TypeParam> sum = a - b;
  ASSERT_EQ(sum.re_, TypeParam(1.2) - TypeParam(3.4));
  ASSERT_EQ(sum.im_, TypeParam(2.3) - TypeParam(4.5));
}

TYPED_TEST(ComplexTest, Mul) {
  Complex<TypeParam> a(1.2, 2.3); 
  Complex<TypeParam> b(3.4, 4.5); 
  Complex<TypeParam> c = a * b;
  TypeParam re = TypeParam(1.2) * TypeParam(3.4) - TypeParam(2.3) * TypeParam(4.5);
  TypeParam im = TypeParam(1.2) * TypeParam(4.5) + TypeParam(2.3) * TypeParam(3.4);
  ASSERT_EQ(c.re_, re);
  ASSERT_EQ(c.im_, im);
}

TYPED_TEST(ComplexTest, Div) {
  Complex<TypeParam> a(1.2, 2.3); 
  Complex<TypeParam> b(3.4, 4.5); 
  Complex<TypeParam> c = a / b;
  TypeParam denom_cmpx_conj = TypeParam(2.3) * TypeParam(2.3) + TypeParam(4.5) * TypeParam(4.5);
  TypeParam re = (TypeParam(1.2) * TypeParam(3.4) + TypeParam(2.3) * TypeParam(4.5)) / denom_cmpx_conj;
  TypeParam im = (TypeParam(2.3) * TypeParam(3.4) - TypeParam(1.2) * TypeParam(4.5)) / denom_cmpx_conj;
  ASSERT_EQ(c.re_, re);
  ASSERT_EQ(c.im_, im);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
