//
// Created by Konstantin Gredeskoul on 5/14/17.
//

#include "division.h"

DivisionResult Division::divide() const {
  if (fraction.denominator == 0L)
    throw DivisionByZero();

  return DivisionResult{fraction.numerator / fraction.denominator,
                        fraction.numerator % fraction.denominator};
}
