//
// Created by Konstantin Gredeskoul on 5/16/17.
//
#include "gtest/gtest.h"
#include <division.h>

using namespace std;

#define VI vector<long long>

class DividerTest : public ::testing::Test {

protected:
  VI numerators = {5, 9, 17, 933345453464353416L};
  VI denominators = {2, 3, 19, 978737423423423499L};
  VI divisions = {2, 3, 0, 0};
  VI remainders = {1, 0, 17, 933345453464353416};

  void SetUp() override{};

  void TearDown() override{};

  virtual void verify(int index) {
    auto f = Fraction{numerators.at(index), denominators.at(index)};
    auto expected =
        DivisionResult{divisions.at(index), remainders.at(index)};
    DivisionResult result = Division(f).divide();
    EXPECT_EQ(result.division, expected.division);
    EXPECT_EQ(result.remainder, expected.remainder);
  }
};

TEST_F(DividerTest, 5_DivideBy_2) { verify(0); }

TEST_F(DividerTest, 9_DivideBy_3) { verify(1); }

TEST_F(DividerTest, 17_DivideBy_19) { verify(2); }

TEST_F(DividerTest, Long_DivideBy_Long) { verify(3); }

TEST_F(DividerTest, DivisionByZero) {
  auto d = Division(Fraction{1, 0});
  try {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-result"
    d.divide();
#pragma clang diagnostic pop
    FAIL() << "Expected divide() method to throw DivisionByZeroException";
  } catch (DivisionByZero const &err) {
    EXPECT_STREQ(err.what(), DIVISION_BY_ZERO_MESSAGE);
  } catch (...) {
    FAIL() << "Expected DivisionByZeroException!";
  }
}
