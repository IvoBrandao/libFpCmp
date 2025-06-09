// tests/test_fpcomp.cpp

#include "FpCmp.hpp"
#include <gtest/gtest.h>
#include <limits>

template <typename T>
class FloatingPointComparisonTest : public ::testing::Test {};

using FloatingPointTypes = ::testing::Types<float, double>;
TYPED_TEST_SUITE(FloatingPointComparisonTest, FloatingPointTypes);

TYPED_TEST(FloatingPointComparisonTest, IdenticalNumbers) {
    TypeParam a = static_cast<TypeParam>(1.234567);
    EXPECT_TRUE(fpcomp::areEqual(a, a));
}

TYPED_TEST(FloatingPointComparisonTest, SmallNumbers) {
    TypeParam a = static_cast<TypeParam>(1e-5);
    TypeParam b = a + std::numeric_limits<TypeParam>::epsilon();
    EXPECT_TRUE(fpcomp::areEqual(a, b));
}

TYPED_TEST(FloatingPointComparisonTest, NotEqualNumbers) {
    TypeParam a = static_cast<TypeParam>(1.0);
    TypeParam b = static_cast<TypeParam>(1.1);
    EXPECT_FALSE(fpcomp::areEqual(a, b));
}

TYPED_TEST(FloatingPointComparisonTest, NaNAndInfinity) {
    TypeParam inf = std::numeric_limits<TypeParam>::infinity();
    TypeParam nan = std::numeric_limits<TypeParam>::quiet_NaN();
    EXPECT_FALSE(fpcomp::areEqual(inf, inf));
    EXPECT_FALSE(fpcomp::areEqual(nan, nan));
    EXPECT_FALSE(fpcomp::areEqual(inf, nan));
    EXPECT_FALSE(fpcomp::areEqual(static_cast<TypeParam>(1.0), inf));
    EXPECT_FALSE(fpcomp::areEqual(static_cast<TypeParam>(1.0), nan));
}

TYPED_TEST(FloatingPointComparisonTest, ZeroCheck_Default) {
    TypeParam a = static_cast<TypeParam>(0.0);
    TypeParam b = std::numeric_limits<TypeParam>::epsilon() * 2;
    TypeParam c = static_cast<TypeParam>(1e-3);
    EXPECT_TRUE(fpcomp::isZero(a));
    EXPECT_TRUE(fpcomp::isZero(b));
    EXPECT_FALSE(fpcomp::isZero(c));
}

TYPED_TEST(FloatingPointComparisonTest, ZeroCheck_AbsoluteOnly) {
    TypeParam tol = static_cast<TypeParam>(1e-2);
    EXPECT_TRUE(fpcomp::isZero(static_cast<TypeParam>(5e-3), tol, fpcomp::ToleranceType::Absolute));
    EXPECT_FALSE(fpcomp::isZero(static_cast<TypeParam>(2e-2), tol, fpcomp::ToleranceType::Absolute));
}

TYPED_TEST(FloatingPointComparisonTest, ZeroCheck_RelativeOnly) {
    TypeParam tol = static_cast<TypeParam>(0.5);
    // |v| <= rtol * max(|v|,|0|) => |v| <= 0.5 * |v| only true if v == 0
    EXPECT_FALSE(fpcomp::isZero(static_cast<TypeParam>(1e-3), tol, fpcomp::ToleranceType::Relative));
    EXPECT_TRUE(fpcomp::isZero(static_cast<TypeParam>(0.0), tol, fpcomp::ToleranceType::Relative));
}

TYPED_TEST(FloatingPointComparisonTest, CustomToleranceAreEqual) {
    TypeParam a = static_cast<TypeParam>(1.0);
    TypeParam b = static_cast<TypeParam>(1.1);
    EXPECT_FALSE(fpcomp::areEqual(a, b));  // default tol
    EXPECT_TRUE(fpcomp::areEqual(a, b, static_cast<TypeParam>(0.2), fpcomp::ToleranceType::Combined));
}

TYPED_TEST(FloatingPointComparisonTest, IsGreater) {
    TypeParam a = static_cast<TypeParam>(1.0);
    TypeParam b_close = a + std::numeric_limits<TypeParam>::epsilon() * 2;
    TypeParam b_far   = a + std::numeric_limits<TypeParam>::epsilon() * 10;

    EXPECT_FALSE(fpcomp::greaterThan(b_close, a));
    EXPECT_TRUE(fpcomp::greaterThan(b_far, a));
    EXPECT_FALSE(fpcomp::greaterThan(a, a));
}

TYPED_TEST(FloatingPointComparisonTest, IsLess) {
    TypeParam a = static_cast<TypeParam>(1.0);
    TypeParam b_close = a - std::numeric_limits<TypeParam>::epsilon() * 2;
    TypeParam b_far   = a - std::numeric_limits<TypeParam>::epsilon() * 10;

    EXPECT_FALSE(fpcomp::lessThan(b_close, a));
    EXPECT_TRUE(fpcomp::lessThan(b_far, a));
    EXPECT_FALSE(fpcomp::lessThan(a, a));
}

TYPED_TEST(FloatingPointComparisonTest, IsGreaterEqual) {
    TypeParam a = static_cast<TypeParam>(1.0);
    TypeParam b_close = a + std::numeric_limits<TypeParam>::epsilon() * 2;
    TypeParam b_far   = a + std::numeric_limits<TypeParam>::epsilon() * 10;

    EXPECT_TRUE(fpcomp::greaterThanOrEqual(b_close, a));
    EXPECT_TRUE(fpcomp::greaterThanOrEqual(b_far, a));
    EXPECT_TRUE(fpcomp::greaterThanOrEqual(a, a));
    EXPECT_FALSE(fpcomp::greaterThanOrEqual(a, b_far));
}

TYPED_TEST(FloatingPointComparisonTest, IsLessEqual) {
    TypeParam a = static_cast<TypeParam>(1.0);
    TypeParam b_close = a - std::numeric_limits<TypeParam>::epsilon() * 2;
    TypeParam b_far   = a - std::numeric_limits<TypeParam>::epsilon() * 10;

    EXPECT_TRUE(fpcomp::lessThanOrEqual(b_close, a));
    EXPECT_TRUE(fpcomp::lessThanOrEqual(b_far, a));
    EXPECT_TRUE(fpcomp::lessThanOrEqual(a, a));
    EXPECT_FALSE(fpcomp::lessThanOrEqual(a, b_far));
}
