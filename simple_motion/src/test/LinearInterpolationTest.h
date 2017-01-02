//
// Created by troy on 1/2/17.
//


#pragma once

#ifndef SIMPLE_MOTION_LINEARINTERPOLATIONTEST_H
#define SIMPLE_MOTION_LINEARINTERPOLATIONTEST_H

#include <cppunit/extensions/HelperMacros.h>

class LinearInterpolationTest : public CppUnit::TestFixture {

CPPUNIT_TEST_SUITE(LinearInterpolationTest);
        CPPUNIT_TEST(test_normal_1);
        CPPUNIT_TEST(test_normal_2);
        CPPUNIT_TEST(test_normal_3);
        CPPUNIT_TEST(test_normal_4);
    CPPUNIT_TEST_SUITE_END();

public:
    void test_normal_1();

    void test_normal_2();

    void test_normal_3();

    void test_normal_4();
};


#endif //SIMPLE_MOTION_LINEARINTERPOLATIONTEST_H
