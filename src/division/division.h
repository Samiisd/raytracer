//
// Created by Konstantin Gredeskoul on 5/14/17.
//
#pragma once

static const char *const DIVISION_BY_ZERO_MESSAGE =
    "Division by zero is illegal";

#include <iostream>
#include <stdexcept>

using namespace std;

class DivisionByZero : public exception {
public:
  [[nodiscard]] const char *what() const noexcept override {
    return DIVISION_BY_ZERO_MESSAGE;
  }
};

struct Fraction {
  long long numerator;
  long long denominator;
};

struct DivisionResult {
  long long division;
  long long remainder;

  friend bool operator==(const DivisionResult &lhs, const DivisionResult &rhs) {
    return lhs.division == rhs.division ? lhs.remainder < rhs.remainder
                                        : lhs.division < rhs.division;
  }
};

class Division {
public:
  explicit Division(Fraction fraction) { this->fraction = fraction; }

  ~Division() = default;

  [[nodiscard]] DivisionResult divide() const;

protected:
  Fraction fraction{};
};
