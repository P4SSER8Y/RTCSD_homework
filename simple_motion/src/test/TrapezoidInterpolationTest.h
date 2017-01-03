//
// Created by troy on 1/3/17.
//


#pragma once

#ifndef SIMPLE_MOTION_TRAPEZOIDINTERPOLATIONTEST_H
#define SIMPLE_MOTION_TRAPEZOIDINTERPOLATIONTEST_H

#include <cppunit/extensions/HelperMacros.h>

class TrapezoidInterpolationTest : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TrapezoidInterpolationTest);
        CPPUNIT_TEST(test_move_forward);
        CPPUNIT_TEST(test_move_backward);
        CPPUNIT_TEST(test_move_nonlinear);
    CPPUNIT_TEST_SUITE_END();

public:
    void test_move_forward();

    void test_move_backward();

    void test_move_nonlinear();

};

#endif //SIMPLE_MOTION_TRAPEZOIDINTERPOLATIONTEST_H
